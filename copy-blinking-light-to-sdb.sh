#!/bin/bash

mkdir temp
mount /dev/sdb temp

rm -frd temp/*

cp -rf pi-oasis-image-base/* temp/
cp -rf source/boot/blinking-light/bin/boot.bin temp/armstub8.bin

sync

umount temp
rm -rfd temp
