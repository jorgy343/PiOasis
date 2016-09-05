#!/bin/bash

rm -f pi-oasis-image.img
touch pi-oasis-image.img
dd bs=1M count=64 if=/dev/zero of=pi-oasis-image.img

losetup /dev/loop0 pi-oasis-image.img
mkdosfs -F 32 -I /dev/loop0

mkdir loop0
mount /dev/loop0 loop0

cp -r pi-oasis-image/* loop0/
cp source/bin/boot.bin loop0/armstub8.bin

umount loop0
losetup -d /dev/loop0
rm -frd loop0
