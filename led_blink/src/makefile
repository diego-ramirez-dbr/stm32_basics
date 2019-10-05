## USER DEFINED VARIABLES ##
PROJ_NAME = main
SRCS = main.c ../device/system_stm32l1xx.c


## COMPILER VARIABLES ##
CC_PREFIX = arm-none-eabi-
CC        = $(CC_PREFIX)gcc
OBJCOPY   = $(CC_PREFIX)objcopy
STARTUP   = ../device/startup_stm32l152xc.s
CFLAGS    = -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd -msoft-float -O -g
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

program: $(PROJ_NAME).hex
	openocd -f board/$(OOCD_BOARD) \
					-c "init" -c "targets" -c "halt" \
					-c "flash write_image erase $(PROJ_NAME).hex" \
					-c "verify_image $(PROJ_NAME).hex" \
					-c "reset run" \
					-c "shutdown"

clean:
	@rm -f *.elf
	@rm -f *.hex

# Create a raw binary file from the ELF version
%.hex: %.elf
	$(Q)$(OBJCOPY) -Oihex $^ $@

# Create the ELF version by mixing together the startup file,
# application, and linker file
%.elf: $(STARTUP) $(SRCS)
	$(CC) -o $@ $(CFLAGS) --specs=nosys.specs -D $(DEVICE) -I $(DEVICE_DIR) -I $(CMSIS_DIR) -I $(PROJ_HEADERS) -Wl,-T $(DEVICE_DIR)/STM32L152RCTx_FLASH.ld $^

.PHONY: all clean program
