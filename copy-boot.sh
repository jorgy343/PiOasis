#!/bin/bash

mount /dev/sdb test
cp source/bin/boot.bin test/armstub8.bin
sync
umount test
