# pws
Plant Watering System

prepare device
1. https://archlinuxarm.org/platforms/armv6/raspberry-pi
2. in /boot/config.txt dtparam=i2c_arm=on
3. in /etc/modules-load.d/raspberrypi.conf add i2c-bcm2708 and i2c-dev

compile the project
1. git clone https://github.com/last-xelnaga/pws.git
2. cd pws
3. ./setup.sh
