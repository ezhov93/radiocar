## Accessing firmware programmers and USB virtual comm devices
The following rule will allow users in the users group to access the USBtinyISP USB programmer for AVR microcontrollers.
```
/etc/udev/rules.d/50-usbtinyisp.rules
```
``` bash
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1781", ATTRS{idProduct}=="0c9f", GROUP="users", MODE="0660"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="16c0", ATTRS{idProduct}=="0479", GROUP="users", MODE="0660"
```