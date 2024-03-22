#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# Make file for Week 2 Application Assigment in the Coursera course The introduce
# to Embedded System Software and Development Environments
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#      all: compiles all object files without linking
#      build : builds and links all source files
#      clean : remove all generated files
#      [file].o : build object file
#      [file].asm : build assembly file
#      [file].i : build preprocessed file
#      [file].d : build dependecy file
#
# Platform Overrides:
#      HOST
#      MSP432
#
#------------------------------------------------------------------------------
include sources.mk

# Platform Overrides
ifndef PLATFORM
PLATFORM = HOST
endif 


# Compiler Flags and Defines
BASENAME = course1
SRC_DIR = src
BUILD_DIR = build

TARGET = $(BUILD_DIR)/$(BASENAME).out
MAP = $(BUILD_DIR)/$(BASENAME).map
# OBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SOURCES))
OBJECTS = $(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(SOURCES)))

CC = gcc
# OBJ = objdump
SIZE = size
LDFLAGS = -Wl,-Map=$(MAP)
CFLAGS = -DCOURSE1 \
	 -Wall \
	 -Werror \
	 -g \
	 -O0 \
	 -std=c99 \
	 -MMD \
	 -D$(PLATFORM)

IFLAGS = $(addprefix -I, $(INCLUDES))

ifeq ($(PLATFORM), MSP432)

LINKER_FILE = msp432p401r.lds
CPU = cortex-m4
ARCH = armv7e-m
SPECS = nosys.specs

CC = arm-none-eabi-gcc
# OBJ = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
CFLAGS += -mcpu=$(CPU) \
	  -march=$(ARCH) \
	  -mthumb\
	  -mfloat-abi=hard \
	  -mfpu=fpv4-sp-d16 \
	  --specs=$(SPECS)

LDFLAGS += -T $(LINKER_FILE)

endif


ifeq ($(DEBUG),1)
	CFLAGS += -DVERBOSE
endif

.PHONY: build compile-all clean dir

build: $(TARGET)

compile-all: $(OBJECTS) | dir

$(TARGET): $(OBJECTS) | dir
	@echo "Compiling the main target."
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) $(IFLAGS) -o $@
	@echo "\nSize of target ${TARGET} ="
	@$(SIZE) $(TARGET)
	@echo "\n"

$(BUILD_DIR)/%.i: $(SRC_DIR)/%.c | dir
	$(CC) -E $^ $(CFLAGS) $(IFLAGS) -o $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c | dir
	$(CC) -c $^ $(CFLAGS) $(IFLAGS) -o $@

$(BUILD_DIR)/%.asm : $(SRC_DIR)/%.c | dir
	$(CC) -S $< -o $@ $(CFLAGS)

-include $(BUILD_DIR)/*.d

dir:
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaning completed."
