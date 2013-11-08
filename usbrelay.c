/*
 * control USBRelay2 (based on V-USB stack from obdev.at
 *
 * code based on Christian Starkjohann's hidtool, see https://github.com/obdev/v-usb)
 *
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hiddata.h"

#define CMD_ON      0xff
#define CMD_ALL_ON  0xfe
#define CMD_OFF     0xfd
#define CMD_ALL_OFF 0xfc

#define READ_OFFSET    7
#define READ_MASK_1 0x01
#define READ_MASK_2 0x02

/* ------------------------------------------------------------------------- */

static char *usbErrorMessage(int errCode)
{
static char buffer[80];

    switch(errCode){
        case USBOPEN_ERR_ACCESS:      return "Access to device denied";
        case USBOPEN_ERR_NOTFOUND:    return "The specified device was not found";
        case USBOPEN_ERR_IO:          return "Communication error with device";
        default:
            sprintf(buffer, "Unknown USB error %d", errCode);
            return buffer;
    }
    return NULL;    /* not reached */
}

static usbDevice_t  *openDevice(void)
{
usbDevice_t     *dev = NULL;
unsigned char   rawVid[2] = { 0xc0, 0x16 };  /* = 0x16c0 = 5824 = voti.nl */
unsigned char   rawPid[2] = { 0xdf, 0x05 };  /* obdev's shared PID for HIDs */
char            vendorName[] = "www.dcttech.com";
char            productName[] = "USBRelay2";
int             vid = rawVid[0] + 256 * rawVid[1];
int             pid = rawPid[0] + 256 * rawPid[1];
int             err;



    if((err = usbhidOpenDevice(&dev, vid, vendorName, pid, productName, 0)) != 0){
        fprintf(stderr, "error finding %s: %s\n", productName, usbErrorMessage(err));
        return NULL;
    }
    return dev;
}

/* ------------------------------------------------------------------------- */



static void decode(char *buffer, int len)
{
  fprintf(stdout, " 1: %s\n", ((buffer[READ_OFFSET] & READ_MASK_1) > 0) ? "ON" : "OFF");
  fprintf(stdout, " 2: %s\n", ((buffer[READ_OFFSET] & READ_MASK_2) > 0) ? "ON" : "OFF");
}

/* ------------------------------------------------------------------------- */

static void usage(char *myName)
{
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "  %s on [1|2]\n", myName);
    fprintf(stderr, "  %s off [1|2]\n", myName);
    fprintf(stderr, "  %s get\n", myName);
}

int main(int argc, char **argv)
{
usbDevice_t *dev;
char        buffer[129];    /* room for dummy report ID */
int         err;
char        cmd = 0x00;

    memset(buffer, 0, sizeof(buffer));

    if (argc < 2) {
        fprintf(stderr, "too few arguments!\n");
        usage(argv[0]);
        exit(1);
    }

    if ((dev = openDevice()) == NULL) {
        exit(1);
    }
    
    if (strcasecmp(argv[1], "on") == 0) {
        if (argc == 3) {
            cmd = CMD_ON;
        } else {
            cmd = CMD_ALL_ON;
        }
    } else if (strcasecmp(argv[1], "off") == 0) {
        if (argc == 3) {
            cmd = CMD_OFF;
        } else {
            cmd = CMD_ALL_OFF;
        }
    }

    if (strcasecmp(argv[1], "get") == 0){
        int len = sizeof(buffer);
        if ((err = usbhidGetReport(dev, 0, buffer, &len)) != 0){
            fprintf(stderr, "error reading data: %s\n", usbErrorMessage(err));
        } else {
            decode(buffer + 1, sizeof(buffer) - 1);
        }
    } else {
        buffer[0] = 0x00;
        buffer[1] = cmd;
        
        if (argc == 3) {
            buffer[2] = (char)atol(argv[2]);
        }

        if ((err = usbhidSetReport(dev, buffer, sizeof(buffer))) != 0) {   /* add a dummy report ID */
            fprintf(stderr, "error writing data: %s\n", usbErrorMessage(err));
        }
    } 

    usbhidCloseDevice(dev);
    return 0;
}

/* ------------------------------------------------------------------------- */
