CC = aarch64-none-elf-gcc
LD = aarch64-none-elf-ld
AS = aarch64-none-elf-as
OBJCOPY = aarch64-none-elf-objcopy
OBJDUMP = aarch64-none-elf-objdump

CFLAGS = -Wall -ffreestanding -nostartfiles -nostdlib
LDFILE = linker.ld

OBJ = obj
BIN = bin

SRCFILES = start.S exception-table-el2.S kernel.c mini-uart.c gpio.c heap.c
OBJFILES = $(addprefix $(OBJ)/, $(patsubst %.c,%.o,$(SRCFILES:.S=.o)))

all: dirs $(BIN)/kernel.bin

$(BIN)/kernel.bin: $(OBJ)/kernel.elf
	$(OBJCOPY) $< -O binary $@

$(OBJ)/kernel.elf: $(OBJFILES)
	$(LD) -T $(LDFILE) -o $@ $^

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
