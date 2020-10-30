CC=i686-elf-gcc
OBJCOPY=i686-elf-objcopy

# OS-specific directory deletion command
ifeq ($(OS),Windows_NT)
	RMDIR=rd /s /q
else
	RMDIR=rm -rf
endif

BUILD_DIR=build
PLAT_DIR=plat
PORT_UTIL_DIR=utils

X86_OBJECTS =  c_traps.o gdt.o main.o
PLAT_OBJECTS = irq_handlers.o pic.o pit.o terminal.o 
ASM_OBJECTS =   boot.o traps.o
UTIL_OBJECTS = string.o printf.o

# Collection of built objects (excluding test applications)
ALL_OBJECTS = $(PLAT_OBJECTS) $(X86_OBJECTS) $(ASM_OBJECTS) $(UTIL_OBJECTS) 
BUILT_OBJECTS = $(patsubst %,$(BUILD_DIR)/%,$(ALL_OBJECTS))

# Search build/output directory for dependencies
vpath %.o ./$(BUILD_DIR)

# GCC flags
CFLAGS=-c -s -ffreestanding -std=gnu99 -Wall -Wextra -Werror \
       -Wno-unused-parameter \
       -Wno-unused-but-set-variable \
       -Wno-unused-variable \
       -Wno-sign-compare
       #-O2 

AFLAGS=$(CFLAGS) -x assembler-with-cpp
LFLAGS=-Tlinker.ld -Wall -ffreestanding -nostdlib 

#################
# Build targets #
#################

main: $(BUILD_DIR) $(ALL_OBJECTS)
	$(CC) $(LFLAGS) $(BUILT_OBJECTS) --output $(BUILD_DIR)/$@.bin

# Make build/output directory
$(BUILD_DIR):
	mkdir $(BUILD_DIR)
	
# Platform C objects builder
$(PLAT_OBJECTS): %.o: $(PLAT_DIR)/%.c
	$(CC) -c $(CFLAGS) -I.  -I$(PORT_UTIL_DIR)  $< -o $(BUILD_DIR)/$(notdir $@)

# Port C objects builder
$(X86_OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) -I. -Imachine/ -I$(PORT_UTIL_DIR)  $< -o $(BUILD_DIR)/$(notdir $@)

# Port asm objects builder
$(ASM_OBJECTS): %.o: %.s
	$(CC) -c $(AFLAGS) -I. $< -o $(BUILD_DIR)/$(notdir $@)

# Port C objects builder
$(UTIL_OBJECTS): %.o: $(PORT_UTIL_DIR)/%.c
	$(CC) -c $(CFLAGS) -I. -I$(PORT_UTIL_DIR) $< -o $(BUILD_DIR)/$(notdir $@)

# Clean
clean:
	$(RMDIR) build/*
