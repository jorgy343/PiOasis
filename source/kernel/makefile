CC = ../../compilers/aarch64-none-elf/bin/aarch64-none-elf-gcc
LD = ../../compilers/aarch64-none-elf/bin/aarch64-none-elf-ld
OBJCOPY = ../../compilers/aarch64-none-elf/bin/aarch64-none-elf-objcopy
OBJDUMP = ../../compilers/aarch64-none-elf/bin/aarch64-none-elf-objdump

CFLAGS = -Wall -ffreestanding -nostartfiles
OBJ = obj/start.o obj/kernel.o obj/mini-uart.o obj/gpio.o obj/heap.o

all: bin/kernel.bin

%.o: %.S %.o
	$(CC) $(CFLAGS) -c -o $@ $<

obj/kernel.elf: $(OBJ)
	$(LD) -T linker.ld -o $@ $^

bin/kernel.bin: obj/kernel.elf
	$(OBJCOPY) $< -O binary $@
