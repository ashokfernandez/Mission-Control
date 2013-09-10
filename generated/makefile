#
#             LUFA Library
#     Copyright (C) Dean Camera, 2013.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.
HAL_DIR   	 = ../HAL 
HAL_INCLUDE_DIR = ../HAL/include
HAL_AVR_DIR  = ../HAL/src/AVR8
RECIPES_DIR  = ../recipes

MCU          = atmega32u4
ARCH         = AVR8
BOARD        = OLIMEX32U4
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = AVR_Demo
SRC          = demoMain.c Descriptors.c Digital_AVR8.c Analogue_AVR8.c USBMIDI_AVR8.c $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH    = ../HAL/src/AVR8/LUFA-130303/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/ -I$(HAL_INCLUDE_DIR) -I$(RECIPES_DIR) -I$(HAL_AVR_DIR)
LD_FLAGS     =

include ./generated_source.mk

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
# include $(LUFA_PATH)/Build/lufa_cppcheck.mk
# include $(LUFA_PATH)/Build/lufa_doxygen.mk
# include $(LUFA_PATH)/Build/lufa_dfu.mk
# include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
# include $(LUFA_PATH)/Build/lufa_atprogram.mk
