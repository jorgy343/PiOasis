#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

export PATH=$DIR/../../compilers/aarch64-linux-elf/bin:$PATH

mkdir -p obj
mkdir -p bin

rm -f obj/*

aarch64-linux-elf-gcc -c start.s -o obj/start.o
aarch64-linux-elf-gcc -fpic -ffreestanding -c kernel.c -o obj/kernel.o
aarch64-linux-elf-ld -T linker.lds -o obj/kernel.elf obj/start.o obj/kernel.o
aarch64-linux-elf-objcopy obj/kernel.elf -O binary bin/kernel.bin
