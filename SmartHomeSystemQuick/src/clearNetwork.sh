#!/bin/bash
echo "Clear Network"
head -n -5 /etc/wpa_supplicant/wpa_supplicant.conf > tmp.txt &&mv tmp.txt /etc/wpa_supplicant/wpa_supplicant.conf
exit 0