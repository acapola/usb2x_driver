
#include <stdio.h>
#include <string.h>
#include <usb.h>

#define NONE    0x00
#define BLUE    0x04
#define RED     0x02
#define GREEN   0x01


#define LED_VENDOR_ID   0x0fc5
#define LED_PRODUCT_ID  0x1223

static void change_color
        (struct usb_dev_handle *handle,
         unsigned char color)
{
    char *dummy;

    usb_control_msg(handle,
                    0x000000c8,
                    0x00000012,
                    (0x02 * 0x100) + 0x0a,
                    0xff & (~color),
                    dummy,
                    0x00000008,
                    5000);
}

static struct usb_device *device_init(void)
{
    struct usb_bus *usb_bus;
    struct usb_device *dev;

    usb_init();
    usb_find_busses();
    usb_find_devices();

    for (usb_bus = usb_busses;
         usb_bus;
         usb_bus = usb_bus->next) {
        for (dev = usb_bus->devices;
             dev;
             dev = dev->next) {
            printf("Device: %04X:%04X\n",dev->descriptor.idVendor,dev->descriptor.idProduct);
            printf("\tManufacturer: %x\n",dev->descriptor.iManufacturer);
            printf("\tProduct:      %x\n",dev->descriptor.iProduct);
            printf("\tSerialNumber: %x\n",dev->descriptor.iSerialNumber);
            if ((dev->descriptor.idVendor
                  == LED_VENDOR_ID) &&
                (dev->descriptor.idProduct
                  == LED_PRODUCT_ID))
                return dev;
        }
    }
    return NULL;
}

void test1(void){
    struct usb_device *usb_dev;
    struct usb_dev_handle *usb_handle;
    int retval = 1;
    int i;
    unsigned char color = NONE;

    usb_dev = device_init();
    if (usb_dev == NULL) {
        fprintf(stderr, "Device not foundn\n");
        goto exit;
    }

    usb_handle = usb_open(usb_dev);
    if (usb_handle == NULL) {
        fprintf(stderr,
             "Not able to claim the USB device\n");
        goto exit;
    }

    
    change_color(usb_handle, color);
    retval = 0;

exit:
    usb_close(usb_handle);
    return retval;
}