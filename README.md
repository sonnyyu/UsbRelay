UsbRelay
========

![ScreenShot](https://raw.githubusercontent.com/sonnyyu/UsbRelay/master/usbrelay.png)

A tool to control a USBRelay2 board.
These boards are based on the V-USB stack from http://www.obdev.at.

Notes:

If you get a message usb.h file missing, you have to install this library:

	sudo apt-get install libusb-dev

If you get following message:

./usbrelay get

Warning: cannot query manufacturer for device: error sending control message: Operation not permitted
error finding USBRelay2: Communication error with device

Then you had to add sudo in front of the command:

sudo ./usbrelay get

 1: ON

 2: ON
 
 
