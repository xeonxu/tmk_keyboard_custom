#----------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device.
#                Please customize your programmer settings(PROGRAM_CMD)
#
# make teensy = Download the hex file to the device, using teensy_loader_cli.
#               (must have teensy_loader_cli installed).
#
# make dfu = Download the hex file to the device, using dfu-programmer (must
#            have dfu-programmer installed).
#
# make flip = Download the hex file to the device, using Atmel FLIP (must
#             have Atmel FLIP installed).
#
# make dfu-ee = Download the eeprom file to the device, using dfu-programmer
#               (must have dfu-programmer installed).
#
# make flip-ee = Download the eeprom file to the device, using Atmel FLIP
#                (must have Atmel FLIP installed).
#
# make debug = Start either simulavr or avarice as specified for debugging,
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

# Target file name (without extension).
TARGET ?= usb_usb

TMK_DIR ?= ../../tmk_core_custom

# Directory keyboard dependent files exist
TARGET_DIR ?= .

# MCU name
MCU ?= atmega32u4


# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency in Hz. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#
#     This will be an integer division of F_USB below, as it is sourced by
#     F_USB after it has run through any CPU prescalers. Note that this value
#     does not *change* the processor frequency - it should merely be updated to
#     reflect the processor speed set externally so that the code can use accurate
#     software delays.
F_CPU ?= 16000000



#
# LUFA specific
#
# Target architecture (see library "Board Types" documentation).
ARCH = AVR8
# Input clock frequency.
#     This will define a symbol, F_USB, in all source code files equal to the
#     input clock frequency (before any prescaling is performed) in Hz. This value may
#     differ from F_CPU if prescaling is used on the latter, and is required as the
#     raw input clock is fed directly to the PLL sections of the AVR for high speed
#     clock generation for the USB and other AVR subsections. Do NOT tack on a 'UL'
#     at the end, this will be done automatically to create a 32-bit value in your
#     source code.
#
#     If no clock division is performed on the input clock inside the AVR (via the
#     CPU clock adjust registers or the clock division fuses), this will be equal to F_CPU.
F_USB ?= $(F_CPU)
# Interrupt driven control endpoint task
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Build Options
#   comment out to disable the options.
#
LEONARDO_ENABLE = yes   # Use arduino leonardo as main controller
# MOUSEKEY_ENABLE = yes	# Mouse keys
HID_MOUSE_ENABLE = yes # Use mouse via U2U
EXTRAKEY_ENABLE = yes	# Media control and System control
# CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
# KEYMAP_IN_EEPROM_ENABLE = yes	# External keymap in eeprom
# LEDMAP_ENABLE = yes	# Enable LED mapping
# LEDMAP_IN_EEPROM_ENABLE = yes # Read LED mapping from eeprom

# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   BootHID          1024
#   Atmel DFU loader 4096	(TMK Alt Controller)
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=1024

#LDFLAGS += -Wl,--relax

#OPT_DEFS += -DNO_ACTION_TAPPING
#OPT_DEFS += -DNO_ACTION_LAYER
#OPT_DEFS += -DNO_ACTION_MACRO


SRC =  \
       keymap_common.c \
       ledmap.c \
       usb_usb.cpp \
       main.cpp

ifdef KEYMAP
    SRC := keymap_$(KEYMAP).c $(SRC)
else
    SRC := keymap.c $(SRC)
endif

ifeq (yes,$(strip $(LEONARDO_ENABLE)))
OPT_DEFS += -DLEONARDO_ENABLE
OPT_DEFS += -DLEONARDO_LED
else
OPT_DEFS += -DTMK_LED
endif

ifeq (yes,$(strip $(HID_MOUSE_ENABLE)))
OPT_DEFS += -DHID_MOUSE_ENABLE
OPT_DEFS += -DHID_COMPOSITE_ENABLE
ifneq (yes,$(strip $(MOUSEKEY_ENABLE)))
MOUSEKEY_ENABLE = yes	# Mouse keys
endif
endif

ifeq (yes,$(strip $(RN42_ENABLE)))
CONFIG_H ?= config_rn42.h
else
CONFIG_H ?= config.h
endif

ifeq (yes,$(strip $(BTSTORE_ENABLE)))
OPT_DEFS += -DBTSTORE_ENABLE
endif

ifeq (yes,$(strip $(BATTERY_ENABLE)))
OPT_DEFS += -DBATTERY_ENABLE
endif

# Search Path
VPATH += $(TARGET_DIR)
VPATH += $(TMK_DIR)

# program Leonardo
PROGRAM_CMD = @if [ "$(DEV)" != "" ]; then \
    while [ ! -e "$(DEV)" ];do echo -n "Waiting for $(DEV)...\r";sleep 0.1;done; \
    sudo avrdude -p$(MCU) -cavr109 -b57600 -Uflash:w:$(TARGET).hex -P$(DEV); \
    else \
    echo "DEV does not define!"; \
    fi

# PROGRAM_CMD = sudo avrdude -p$(MCU) -cavr109 -b57600 -Uflash:w:$(TARGET).hex -P$(DEV)

ifeq (yes,$(strip $(RN42_ENABLE)))
include rn42.mk
include $(TMK_DIR)/protocol.mk
endif
include $(TMK_DIR)/protocol/usb_hid.mk
include $(TMK_DIR)/protocol/lufa.mk
include $(TMK_DIR)/common.mk
include $(TMK_DIR)/rules.mk

debug-on: MOUSEKEY_ENABLE := NO	# Mouse keys
debug-on: EXTRAFLAGS += -DCONSOLE_ENABLE -DCOMMAND_ENABLE -DDEBUG
debug-on: OPT_DEFS := $(filter-out -DNO_DEBUG,$(OPT_DEFS))
debug-on: OPT_DEFS := $(filter-out -DNO_PRINT,$(OPT_DEFS))
debug-on: OPT_DEFS := $(filter-out -DHID_MOUSE_ENABLE,$(OPT_DEFS))
debug-on: OPT_DEFS := $(filter-out -DHID_COMPOSITE_ENABLE,$(OPT_DEFS))
debug-on: OPT_DEFS := $(filter-out -DMOUSE_ENABLE,$(OPT_DEFS))
debug-on: OPT_DEFS := $(filter-out -DMOUSEKEY_ENABLE,$(OPT_DEFS))
debug-on: all

debug-off: EXTRAFLAGS += -DNO_DEBUG -DNO_PRINT
debug-off: OPT_DEFS := $(filter-out -DCONSOLE_ENABLE,$(OPT_DEFS))
debug-off: all
