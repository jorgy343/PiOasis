#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

export PATH=$DIR/../../../compilers/aarch64-linux-gnu/bin:$PATH

mkdir -p obj
mkdir -p bin

rm -f obj/*

aarch64-linux-gnu-as -c boot.s -o obj/boot.o
aarch64-linux-gnu-ld --section-start=.text=0 obj/boot.o -o obj/boot.elf
aarch64-linux-gnu-objcopy obj/boot.elf -O binary obj/boot.tmp

dd ibs=256 count=1 conv=sync if=obj/boot.tmp of=bin/boot.bin
