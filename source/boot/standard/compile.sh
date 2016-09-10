#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

export PATH=/opt/gnuarm64/bin:$PATH

mkdir -p obj
mkdir -p bin

rm -f obj/*

aarch64-none-elf-gcc -nostdlib -nostartfiles -c boot.S -o obj/boot.o
aarch64-none-elf-ld --section-start=.text=0 obj/boot.o -o obj/boot.elf
aarch64-none-elf-objcopy obj/boot.elf -O binary obj/boot.tmp

dd ibs=256 count=1 conv=sync if=obj/boot.tmp of=bin/boot.bin
