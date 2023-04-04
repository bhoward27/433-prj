#!/bin/sh
echo 0 > "/sys/bus/iio/devices/iio:device0/buffer/enable"
echo 0 > "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage4_en"
