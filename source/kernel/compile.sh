#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

export PATH=$DIR/../../compilers/aarch64-linux-gnu/bin:$PATH

mkdir -p obj
mkdir -p bin

rm -f obj/*

aarch64-linux-gnu-gcc -c start.s -o obj/start.o
aarch64-linux-gnu-gcc -fpic -ffreestanding -c kernel.c -o obj/kernel.o
aarch64-linux-gnu-ld -T linker.lds -o obj/kernel.elf obj/start.o obj/kernel.o
aarch64-linux-gnu-objcopy obj/boot.elf -O binary bin/kernel.bin
