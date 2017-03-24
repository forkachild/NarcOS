TARGET = NarcOS

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=Cortex-A53 -ffreestanding -fpic -O2 -lgcc -c -Wall -Wextra -std=gnu99
ASFLAGS = -mcpu=Cortex-A53 -ffreestanding -fpic -c
LDFLAGS = -ffreestanding -O2 -nostdlib

SRCDIR = src
OBJDIR = obj
BINDIR = bin
LDDIR = linker

CSRCDIR = $(SRCDIR)/c
CINCDIR = $(SRCDIR)/c/include
ASMSRCDIR = $(SRCDIR)/asm

COBJDIR = $(OBJDIR)/c
ASMOBJDIR = $(OBJDIR)/asm

COBJS = $(patsubst $(CSRCDIR)/%.c, $(COBJDIR)/%.o, $(wildcard $(CSRCDIR)/*.c))
ASMOBJS = $(patsubst $(ASMSRCDIR)/%.s, $(ASMOBJDIR)/%.o, $(wildcard $(ASMSRCDIR)/*.s))

OUTPUT_ELF = kernel.elf
OUTPUT_IMG = kernel.img

$(COBJDIR)/%.o : $(CSRCDIR)/%.c
	@echo "Compiling C code"
	@$(CC) $(CFLAGS) -I$(CINCDIR) -o $@ $^

$(ASMOBJDIR)/%.o : $(ASMSRCDIR)/%.s
	@echo "Assembling ASM code"
	@$(CC) $(ASFLAGS) -o $@ $^

$(TARGET): $(COBJS) $(ASMOBJS)
	@echo "Building binary"
	@$(CC) $(LDFLAGS) -T $(LDDIR)/linker.ld -o $(BINDIR)/$(OUTPUT_ELF) $^
	@echo "Generated kernel.elf"
	@$(OBJCOPY) $(BINDIR)/$(OUTPUT_ELF) -O binary $(BINDIR)/$(OUTPUT_IMG)
	@echo "Generated kernel.img"

all: $(TARGET)

clean:
	@echo "Cleaning directories"
	@rm -f $(COBJDIR)/*.o $(ASMOBJDIR)/*.o $(BINDIR)/$(OUTPUT_ELF) $(BINDIR)/$(OUTPUT_IMG)

emulate: all
	@echo "Starting emulation"
	@qemu-system-arm -kernel $(BINDIR)/$(OUTPUT_ELF) -m 256 -M raspi2 -serial stdio