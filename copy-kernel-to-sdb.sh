#!/bin/bash

mkdir temp
mount /dev/sdb temp

rm -frd temp/*

cp -rf pi-oasis-image-base/* temp/
cp -rf source/boot/standard/bin/boot.bin temp/armstub8.bin
cp -rf source/kernel/bin/kernel.bin temp/kernel8.img

sync

umount temp
rm -rfd temp
