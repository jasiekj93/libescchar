# ------------------------------------------------
# @author Adrian Szczepanski
# @date 06-03-2023
# ------------------------------------------------

# This file is only a template and should be included 
# in other Makefile

# Debug
DEBUG ?= 1
GEN_LST ?= 0
OPT ?= -O0

### GCC flags ###
CFLAGS = $(MCU) $(cxx_defs) $(cxx_includes) $(OPT)

ifneq ($(PLATFORM), Pc32)
CFLAGS += -fdata-sections -ffunction-sections 
CXXFLAGS += -ffreestanding -fno-exceptions -fno-rtti 
endif

# Add debug flags
ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information as 'make' rules
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" 

# Generate assembly output into build directory
ifeq ($(GEN_LST), 1)
CFLAGS += -Wa,-a,-ad,-alms=$(build_dir)/$(notdir $(<:.cpp=.lst))
endif

#G++ specyfic flags
CXXFLAGS += $(CFLAGS) -std=c++17 

#Assembler flags
ASFLAGS += $(MCU) $(asm_defs) $(asm_includes) $(OPT) -Wall -fdata-sections -ffunction-sections -ffreestanding -fno-exceptions 

#Linker flags and directories
#Libraries are stored in variable LDLIBS
LDFLAGS += $(MCU) -L$(lib_dir) -Wl,-Map=$(build_dir)/$(target).map,--cref -Wl,--gc-sections

ifeq ($(PLATFORM), ARM)
LDFLAGS += -specs=nano.specs -specs=nosys.specs
endif