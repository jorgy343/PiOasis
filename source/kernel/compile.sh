#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

export PATH=$DIR/../../compilers/aarch64-none-elf/bin:$PATH

mkdir -p obj
mkdir -p bin

rm -f obj/*

aarch64-none-elf-gcc -c start.s -o obj/start.o
aarch64-none-elf-gcc -fpic -ffreestanding -c kernel.c -o obj/kernel.o
aarch64-none-elf-gcc -fpic -ffreestanding -c mini-uart.c -o obj/mini-uart.o
aarch64-none-elf-gcc -fpic -ffreestanding -c gpio.c -o obj/gpio.o
aarch64-none-elf-ld -T linker.lds -o obj/kernel.elf obj/start.o obj/kernel.o obj/mini-uart.o obj/gpio.o
aarch64-none-elf-objcopy obj/kernel.elf -O binary bin/kernel.bin
