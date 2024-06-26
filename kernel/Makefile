
OSNAME = BASOS

GNUEFI = ../gnu-efi
OVMFDIR = ../OVMFbin
LDS = kernel.ld
CC = gcc
ASMC = nasm
LD = ld

CFLAGS = -ffreestanding -fshort-wchar -mno-red-zone -fno-exceptions
ASMFLAGS = 
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib

SRCDIR := src
OBJDIR := lib
BUILDDIR = bin
BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi
DSRCDIR := ../desktop
DOBJDIR := lib/desktop
GNUDIR := ../gnu-efi

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)  
ASMSRC = $(call rwildcard,$(SRCDIR),*.asm)  
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
OBJS += $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%_asm.o, $(ASMSRC))
DIRS = $(wildcard $(SRCDIR)/*)

DSRC = $(call rwildcard,$(DSRCDIR),*.cpp)  
DASMSRC = $(call rwildcard,$(DSRCDIR),*.asm)  
DOBJS = $(patsubst $(DSRCDIR)/%.cpp, $(DOBJDIR)/%.o, $(DSRC))
DOBJS += $(patsubst $(DSRCDIR)/%.asm, $(DOBJDIR)/%_asm.o, $(DASMSRC))
DIRS += $(wildcard $(DSRCDIR)/*)

kernel: $(OBJS) $(DOBJS) link

$(OBJDIR)/interrupts/interrupts.o: $(SRCDIR)/interrupts/interrupts.cpp
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(CC) -mno-red-zone -mgeneral-regs-only -ffreestanding -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(SRCDIR) -I$(SRCDIR)/gdt -I$(SRCDIR)/interrupts -I$(SRCDIR)/paging -I$(SRCDIR)/userinput -I$(SRCDIR)/BSL -I$(DSRCDIR) -I$(SRCDIR)/AHCI -I$(SRCDIR)/memory -I$(SRCDIR)/time -c $^ -o $@
	
$(OBJDIR)/%_asm.o: $(SRCDIR)/%.asm
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(ASMC) $(ASMFLAGS) $^ -f elf64 -o $@

$(DOBJDIR)/%.o: $(DSRCDIR)/%.cpp
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(SRCDIR) -I$(SRCDIR)/gdt -I$(SRCDIR)/interrupts -I$(SRCDIR)/paging -I$(SRCDIR)/userinput -I$(SRCDIR)/BSL -I$(DSRCDIR) -I$(SRCDIR)/AHCI -I$(SRCDIR)/memory -I$(SRCDIR)/time -c $^ -o $@
	
$(DOBJDIR)/%_asm.o: $(DSRCDIR)/%.asm
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(ASMC) $(ASMFLAGS) $^ -f elf64 -o $@
	 
link:
	@ echo !==== LINKING
	@ echo $(DOBJS)
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS) $(DOBJS)

setup:
	@mkdir $(BUILDDIR)
	@mkdir $(SRCDIR)
	@mkdir $(OBJDIR)

	@mkdir $(DSRCDIR)
	@mkdir $(DOBJDIR)

buildimg:
	dd if=/dev/zero of=$(BUILDDIR)/$(OSNAME).img bs=512 count=93750
	mformat -i $(BUILDDIR)/$(OSNAME).img ::
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/font.psf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img test.txt ::/EFI/

run:
	qemu-system-x86_64 -machine q35 -drive file=$(BUILDDIR)/$(OSNAME).img -m 512M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$(OVMFDIR)/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="$(OVMFDIR)/OVMF_VARS-pure-efi.fd" -net none
