ls -l /dev/ttyUSB*
# add user group
sudo usermod -a -G dialout ezhov93
sudo chmod a+rw /dev/ttyUSB0