#!/bin/bash
my_newtwork_ssid=$1
my_newtwork_pwd=$2

echo "Clear Network"
head -n -5 /etc/wpa_supplicant/wpa_supplicant.conf > tmp.txt &&mv tmp.txt /etc/wpa_supplicant/wpa_supplicant.conf

echo "ADD: ssid: $my_newtwork_ssid, pwd: $my_newtwork_pwd"
echo -e "network={\n\tssid=\"${my_newtwork_ssid}\"\n\tpsk=\"${my_newtwork_pwd}\"\n}\n"  >>  /etc/wpa_supplicant/wpa_supplicant.conf

wpa_cli -i wlan0 reconfigure

exit 0