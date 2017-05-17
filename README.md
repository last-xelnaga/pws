# pws
Plant Watering System


compile the project
1. git clone https://github.com/last-xelnaga/pws.git
2. cd pws
3. ./setup.sh


prepare the device
1. setup new raspberry-pi zero w device
        https://archlinuxarm.org/platforms/armv6/raspberry-pi

2. edit /boot/config.txt
        nano /boot/config.txt

        dtparam=spi=on


enable wifi
1. shutdown wlan
        ifconfig wlan0 down

2. create wifi profile
        cd /etc/netctl/
        install -m640 examples/wireless-wpa mywifi

3. edit new profile and assign static IP
        nano /etc/netctl/mywifi

        IP=static
        Address=('192.168.1.45/24')
        Gateway=('192.168.1.1')
        DNS=('192.168.1.1')

4. start newly created profile
        netctl start mywifi

5. make it default
        netctl enable mywifi
