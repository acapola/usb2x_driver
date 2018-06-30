#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>
#include <stdlib.h>

static void error(void){
    printf("error\n");
    exit(-1);
}

static void print_descriptor_string(libusb_device_handle *dev, const char*before,uint8_t desc_index, const char*after){
    char buf[1024];
    int status = libusb_get_string_descriptor_ascii ( dev,desc_index,(uint8_t*)buf,sizeof(buf));
    if(status<0){
        snprintf(buf,sizeof(buf),"<error:%d, %s>",status,libusb_strerror(status) );
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


static int is_nimp_usb2x_device(libusb_device *device){
    int match=0;
    struct libusb_device_descriptor desc;
    int status = libusb_get_device_descriptor (device,&desc);
    if(0==status){
        libusb_device_handle *handle;
        int err = libusb_open(device, &handle);
        if (0==err) {
            match = is_nimp_usb2x_device_handle(handle);
            libusb_close(handle);
        }
    }
    return match;
}

void test2(void){
    // discover devices
    libusb_device **list;
    //libusb_device *found = NULL;
    struct libusb_context *context;
	if (libusb_init(&context)){
		printf("libusb not initialised.\n");
        error();
	}
    ssize_t cnt = libusb_get_device_list(NULL, &list);
    ssize_t i = 0;
    int err = 0;
    if (cnt < 0)
        error();
    for (i = 0; i < cnt; i++) {
        libusb_device *device = list[i];
        struct libusb_device_descriptor desc;
        int status = libusb_get_device_descriptor (device,&desc);
        if(0==status){
            printf("Device: %04X:%04X\n",desc.idVendor,desc.idProduct);
            libusb_device_handle *handle;
            err = libusb_open(device, &handle);
            if (0==err) {
                //libusb_reset_device(handle);
                print_descriptor_string(handle,"\tManufacturer:",desc.iManufacturer,"\n");
                print_descriptor_string(handle,"\tProduct:     ",desc.iProduct,"\n");
                print_descriptor_string(handle,"\tSerialNumber:",desc.iSerialNumber,"\n");
                libusb_close(handle);
            }
        }
        if(is_nimp_usb2x_device(device)){
            printf("---------is nimp usb2x----------\n");
        }
        /*if (is_interesting(device)) {
            found = device;
            break;
        }*/
    }
    /*if (found) {
        libusb_device_handle *handle;
        err = libusb_open(found, &handle);
        if (err)
            error();
        // etc
    }*/
    libusb_free_device_list(list, 1);
}