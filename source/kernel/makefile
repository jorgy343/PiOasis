CC=../../compilers/aarch64-none-elf/bin/aarch64-none-elf-gcc
LD=../../compilers/aarch64-none-elf/bin/aarch64-none-elf-ld
OBJCOPY=../../compilers/aarch64-none-elf/bin/aarch64-none-elf-objcopy
OBJDUMP=../../compilers/aarch64-none-elf/bin/aarch64-none-elf-objdump

kernel.bin: obj/kernel.elf
	$(OBJCOPY) obj/kernel.elf -O binary bin/kernel.bin
