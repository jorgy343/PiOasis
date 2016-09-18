CC = aarch64-none-elf-gcc
LD = aarch64-none-elf-ld
AS = aarch64-none-elf-as
OBJCOPY = aarch64-none-elf-objcopy
OBJDUMP = aarch64-none-elf-objdump
OBJ = obj
BIN = bin

LDFILE = linker.ld

CFLAGS = -Wall -ffreestanding -nostartfiles

SRCFILES = start.S kernel.c mini-uart.c gpio.c heap.c
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
	mkdir obj
	mkdir bin

clean:
	rm -rf bin
	rm -rf obj
