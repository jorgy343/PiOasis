#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

export PATH=$DIR/../../compilers/aarch64-none-elf/bin:$PATH

mkdir -p obj
mkdir -p bin

rm -f obj/*

aarch64-none-elf-gcc -Wall -c start.S -o obj/start.o
aarch64-none-elf-gcc -Wall -fpic -ffreestanding -c kernel.c -o obj/kernel.o
aarch64-none-elf-gcc -Wall -fpic -ffreestanding -c mini-uart.c -o obj/mini-uart.o
aarch64-none-elf-gcc -Wall -fpic -ffreestanding -c gpio.c -o obj/gpio.o
aarch64-none-elf-gcc -Wall -fpic -ffreestanding -c heap.c -o obj/heap.o
aarch64-none-elf-ld -T linker.ld -o obj/kernel.elf obj/start.o obj/kernel.o obj/mini-uart.o obj/gpio.o obj/heap.o
aarch64-none-elf-objcopy obj/kernel.elf -O binary bin/kernel.bin
