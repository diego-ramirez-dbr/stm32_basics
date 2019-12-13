## USER DEFINED VARIABLES ##
PROJ_NAME = main
SRCS = main.c system_stm32l1xx.c stm32_timers.c


## COMPILER VARIABLES ##
CC_PREFIX = arm-none-eabi-
CC        = $(CC_PREFIX)gcc
OBJCOPY   = $(CC_PREFIX)objcopy
STARTUP   = ../device/startup_stm32l152xc.s
CFLAGS    = -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd -msoft-float -O -g --specs=nosys.specs
DEVICE    = STM32L152xC

## DIRECTORIES ##
DEVICE_DIR = ../device
CMSIS_DIR  = ../libraries/CMSIS/Include
PROJ_HEADERS = ../include

## OPENOCD VARIABLES  ##
OOCD_BOARD = stm32ldiscovery.cfg


## TARGETS ##
# List of all binaries to build
all: program

program: $(PROJ_NAME).elf
			openocd -f board/$(OOCD_BOARD) \
					-c "init" -c "targets" -c "halt" \
					-c "flash write_image erase $(PROJ_NAME).elf" \
					-c "verify_image $(PROJ_NAME).elf" \
					-c "reset run" \
					-c "shutdown"

clean:
	@rm -f *.elf
	@rm -f *.hex

# Create a raw hex file from the ELF version
%.hex: %.elf
	$(Q)$(OBJCOPY) -Oihex $^ $@

# Create the ELF version by mixing together the startup file,
# application, and linker file
%.elf: $(STARTUP) $(SRCS)
	$(CC) -o $@ $(CFLAGS) -D $(DEVICE) -I $(DEVICE_DIR) -I $(CMSIS_DIR) -I $(PROJ_HEADERS) -Wl,-T $(DEVICE_DIR)/stm32l152rctx_flash.ld $^

.PHONY: all clean program
