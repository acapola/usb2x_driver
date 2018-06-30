
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "string.h"

#include <libusb-1.0/libusb.h>

/* You may want to change the VENDOR_ID and PRODUCT_ID
 * depending on your device.
 */
#define VENDOR_ID      0x0483 
#define PRODUCT_ID     0x5740

#define ACM_CTRL_DTR   0x01
#define ACM_CTRL_RTS   0x02

/* We use a global variable to keep the device handle
 */
static struct libusb_device_handle *devh = NULL;

/* The Endpoint address are hard coded. You should use lsusb -v to find
 * the values corresponding to your device.
 */
static int ep_in_addr  = 0x81;
static int ep_out_addr = 0x01;

void write_char(unsigned char c)
{
    /* To send a char to the device simply initiate a bulk_transfer to the
     * Endpoint with address ep_out_addr.
     */
    int actual_length;
    if (libusb_bulk_transfer(devh, ep_out_addr, &c, 1,
                             &actual_length, 0) < 0) {
        fprintf(stderr, "Error while sending char\n");
    }
}

void serial_write(uint8_t* buf,uint32_t len)
{
    /* To send a char to the device simply initiate a bulk_transfer to the
     * Endpoint with address ep_out_addr.
     */
    int actual_length;
    if (libusb_bulk_transfer(devh, ep_out_addr, buf, len,
                             &actual_length, 0) < 0) {
        fprintf(stderr, "Error while buf %s\n", buf);
    }
}

int read_chars(unsigned char * data, int size)
{
    /* To receive characters from the device initiate a bulk_transfer to the
     * Endpoint with address ep_in_addr.
     */
    int actual_length;
    int rc = libusb_bulk_transfer(devh, ep_in_addr, data, size, &actual_length,
                                  1000);
    if (rc == LIBUSB_ERROR_TIMEOUT) {
        printf("timeout (%d)\n", actual_length);
        return -1;
    } else if (rc < 0) {
        fprintf(stderr, "Error while waiting for char\n");
        return -1;
    }

    return actual_length;
}


static void print_descriptor_string(libusb_device_handle *dev, const char*before,uint8_t desc_index, const char*after){
    unsigned char buf[1024];
    int status = libusb_get_string_descriptor_ascii ( dev,desc_index,buf,sizeof(buf));
    if(status<0){
        snprintf((char*)buf,sizeof(buf),"<error:%d, %s>",status,libusb_strerror(status) );
    }
    printf("%s%s%s",before,buf,after);
}


static int check_descriptor_string(libusb_device_handle *dev, const char*expected,uint8_t desc_index){
    char buf[1024];
    int status = libusb_get_string_descriptor_ascii ( dev,desc_index,(uint8_t*)buf,sizeof(buf));
    if(status<0){
        return 0;
    }
    return 0==strcmp(expected,buf);
}

static int is_nimp_usb2x_device_handle(libusb_device_handle *handle){
    int match=0;
    struct libusb_device_descriptor desc;
    libusb_device *device = libusb_get_device(handle);
    int status = libusb_get_device_descriptor (device,&desc);
    if(status) return 0;
    match = check_descriptor_string(handle,"nimp",desc.iManufacturer);
    match &= check_descriptor_string(handle,"usb2x",desc.iProduct);
    return match;
}

static libusb_device_handle *get_nimp_usb2x(void){
    libusb_device **list;
    struct libusb_context *context;
	if (libusb_init(&context)){
		printf("libusb cound not be initialised.\n");
        exit(-1);
	}
    ssize_t cnt = libusb_get_device_list(NULL, &list);
    ssize_t i = 0;
    int match=0;
    libusb_device_handle *handle;
    for (i = 0; i < cnt; i++) {
        libusb_device *device = list[i];
        
        int err = libusb_open(device, &handle);
        if (0==err) {
            match = is_nimp_usb2x_device_handle(handle);
            if(match) break;//keep the handle
            libusb_close(handle);
        }
    }
    libusb_free_device_list(list, 1);
    if(0==match) return NULL;
    return handle;
}

int test3(void){
    int rc;

    /* Initialize libusb
     */
    rc = libusb_init(NULL);
    if (rc < 0) {
        fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(rc));
        exit(1);
    }

    /* Set debugging output to max level.
     */
    libusb_set_debug(NULL, 3);

    /* Look for a specific device and open it.
     */
    //devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    devh = get_nimp_usb2x();
    if (!devh) {
        fprintf(stderr, "Error finding USB device\n");
        goto out;
    }
    
    print_descriptor_string(devh,"\tManufacturer: ",1,"\n");
    print_descriptor_string(devh,"\tProduct:      ",2,"\n");
    print_descriptor_string(devh,"\tSerialNumber: ",3,"\n");
    libusb_reset_device(devh);
    /* As we are dealing with a CDC-ACM device, it's highly probable that
     * Linux already attached the cdc-acm driver to this device.
     * We need to detach the drivers from all the USB interfaces. The CDC-ACM
     * Class defines two interfaces: the Control interface and the
     * Data interface.
     */
    for (int if_num = 0; if_num < 2; if_num++) {
        if (libusb_kernel_driver_active(devh, if_num)) {
            libusb_detach_kernel_driver(devh, if_num);
        }
        rc = libusb_claim_interface(devh, if_num);
        if (rc < 0) {
            fprintf(stderr, "Error claiming interface: %s\n",
                    libusb_error_name(rc));
            goto out;
        }
    }
    write_char('t');
    char* magic = "Nimp USB to x bridge host app";
    serial_write((uint8_t*)magic,strlen(magic));
    goto out;

    /* Start configuring the device:
     * - set line state
     */
    rc = libusb_control_transfer(devh, 0x21, 0x22, ACM_CTRL_DTR | ACM_CTRL_RTS,
                                0, NULL, 0, 0);
    if (rc < 0) {
        fprintf(stderr, "Error during control transfer: %s\n",
                libusb_error_name(rc));
    }

    /* - set line encoding: here 9600 8N1
     * 9600 = 0x2580 ~> 0x80, 0x25 in little endian
     */
    unsigned char encoding[] = { 0x80, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08 };
    rc = libusb_control_transfer(devh, 0x21, 0x20, 0, 0, encoding,
                                sizeof(encoding), 0);
    if (rc < 0) {
        fprintf(stderr, "Error during control transfer: %s\n",
                libusb_error_name(rc));
    }

    /* We can now start sending or receiving data to the device
     */
    unsigned char buf[65];
    int len;
    
    while(1) {
        write_char('t');
        len = read_chars(buf, 64);
        buf[len] = 0;
        fprintf(stdout, "Received: \"%s\"\n", buf);
        sleep(1);
    }

    libusb_release_interface(devh, 0);

out:
    if (devh)
            libusb_close(devh);
    libusb_exit(NULL);
    return rc;
}