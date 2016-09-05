#!/bin/bash

rm -f pi-oasis-image-base.img
touch pi-oasis-image-base.img
dd bs=1M count=64 if=/dev/zero of=pi-oasis-image-base.img

losetup /dev/loop0 pi-oasis-image-base.img
mkdosfs -F 32 -I /dev/loop0

mkdir loop0
mount /dev/loop0 loop0

cp -r pi-oasis-image-base/* loop0/

umount loop0
losetup -d /dev/loop0
rm -frd loop0
