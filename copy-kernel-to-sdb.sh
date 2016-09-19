#!/bin/bash

mkdir temp
mount /dev/sdb temp

rm -frd temp/*

cp -rf pi-oasis-image-base/* temp/
cp -rf source/kernel/bin/kernel.bin temp/kernel8.img

sync

umount temp
rm -rfd temp
