#!/bin/sh
sudo chmod 0666 "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage4_en"
echo 1 > "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage4_en"
sudo chmod 0666 "/sys/bus/iio/devices/iio:device0/buffer/length"
echo 8000 > "/sys/bus/iio/devices/iio:device0/buffer/length"
sudo chmod 0666 "/sys/bus/iio/devices/iio:device0/buffer/enable"
echo 1 > "/sys/bus/iio/devices/iio:device0/buffer/enable"
sudo chmod 0666 /dev/iio:device0
