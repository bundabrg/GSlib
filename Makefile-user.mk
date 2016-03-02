## Local build configuration
## Parameters configured here will override default and ENV values.
## Uncomment and change examples:

 
## ESP_HOME sets the path where ESP tools and SDK are located.
## Windows:
# ESP_HOME = c:/Espressif

## MacOS / Linux:
#ESP_HOME = /opt/esp-open-sdk

## SMING_HOME sets the path where Sming framework is located.
## Windows:
# SMING_HOME = c:/tools/sming/Sming 

# MacOS / Linux
# SMING_HOME = /opt/sming/Sming

## COM port parameter is reqruied to flash firmware correctly.
## Windows: 
# COM_PORT = COM3

# MacOS / Linux:
# COM_PORT = /dev/tty.usbserial

# Com port speed
# COM_SPEED	= 115200

BUILD_NUMBER:=$(shell date +"%s")

# Include folders
EXTRA_INCDIR = include

# User Flags
USER_CFLAGS = -DBRG_DEBUG -DICACHE_FLASH

# Modules to compile
MODULES = app

# Extra Libs
#EXTRA_LIBS = stdc++

# Enable RBoot
RBOOT_ENABLED ?= 1

# RBoot bigflash mode (full 1Mb Rom) - We don't use this
RBOOT_BIG_FLASH ?= 0

# Enable two rom mode (where two roms sit in the same 1Mb block of flash)
RBOOT_TWO_ROMS ?= 1

# Size of the flash chip
SPI_SIZE ?= 4M

# Output file for the first rom
RBOOT_ROM_0 ?= rom0

# input linker file for first rom
RBOOT_LD_0 ?= rom0.ld

# Output file for second rom
RBOOT_ROM_1 ?= rom1
RBOOT_LD_1 ?= rom1.ld

# Size of SPIFFS to create
SPIFF_SIZE ?= 500000
#SPIFF_SIZE ?=  900000

# Flash offsets for spiffs
RBOOT_SPIFFS_0 ?= 0x100000

# Disable creating SPIFFS
#DISABLE_SPIFFS=1

brg_all: timestamp.o all	## Copy to web server
	echo $(BUILD_NUMBER) > out/firmware/gs_version
	echo Copy all files in out/firmware/* to your web server. For example I have:
	echo scp out/firmware/* gs1@172.x.x.x:web/
	

brg_flash: brg_all flash	## Flash using serial, but also copy to web server


.timestamp:	## Create a build time variable
	 echo 'char const GS_BUILD_NUMBER[] = "$(BUILD_NUMBER)";' > app/timestamp.c

timestamp.c: .timestamp
.PHONY: timestamp
