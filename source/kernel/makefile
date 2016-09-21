CC = aarch64-none-elf-gcc
LD = aarch64-none-elf-ld
AS = aarch64-none-elf-as
OBJCOPY = aarch64-none-elf-objcopy
OBJDUMP = aarch64-none-elf-objdump

CFLAGS = -O0 -Wall -ffreestanding -nostartfiles -nostdlib -I ../../newlib/newlib-source/newlib/libc/include
LDFILE = linker.ld

OBJ = obj
BIN = bin

SRCFILES = start.S exception-table-el2.S kernel.c mini-uart.c gpio.c heap.c newlib-system-calls.c
OBJFILES = $(addprefix $(OBJ)/, $(patsubst %.c,%.o,$(SRCFILES:.S=.o)))

all: dirs $(BIN)/kernel.bin

$(BIN)/kernel.bin: $(OBJ)/kernel.elf
	$(OBJCOPY) $< -O binary $@

$(OBJ)/kernel.elf: $(OBJFILES)
	$(CC) $(CFLAGS) -T $(LDFILE) -o $@ $^ ../../newlib/aarch64-none-elf/newlib/libc.a -lgcc

$(OBJ)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

dirs:
	mkdir -p obj
	mkdir -p bin

clean:
	rm -rf bin
	rm -rf obj
