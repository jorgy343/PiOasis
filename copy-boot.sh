#!/bin/bash

mkdir temp
mount /dev/sdb temp
cp source/bin/boot.bin temp/armstub8.bin
sync
umount temp
rm -rfd temp
