# Mbed CMake Template
# Copyright 2020 Ladislas de Toldi (ladislas [at] detoldi.me)
# SPDX-License-Identifier: Apache-2.0

#
# MARK: - Constants
#

OPENOCD_SCRIPT_DIR ?= /usr/local/Cellar/open-ocd/HEAD-6405d35/share/openocd/scripts

ROOT_DIR    := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
CMAKE_DIR   := $(ROOT_DIR)/cmake
BUILD_DIR   := $(ROOT_DIR)/build
MBED_OS_DIR := $(ROOT_DIR)/extern/mbed-os

#
# MARK:- Arguments
#

PORT         ?= /dev/tty.usbmodem212403
BRANCH       ?= mbed-os-6.15.1
TARGET       ?=
VERSION      ?= mbed-os-6.15.0
BAUDRATE     ?= 9600
BIN_PATH_FRONT     ?= $(BUILD_DIR)/src/FrontSeat/front.bin
BIN_PATH_BACK     ?= $(BUILD_DIR)/src/BackSeat/back.bin
BIN_PATH_ADCPRINT     ?= $(BUILD_DIR)/src/ADCPrint/adcprint.bin
BUILD_TYPE   ?= Release
TARGET_BOARD ?= NUCLEO_L432KC

#
# MARK:- Build targets
#

all:
	@echo ""
	@echo "🏗️  Building application 🚧"
	cmake --build build

#
# MARK:- Config targets
#

config:
	@$(MAKE) clean
	@echo ""
	@$(MAKE) config_target
	@echo ""
	@$(MAKE) config_cmake

config_target:
	@echo ""
	@echo "🏃 Running target configuration script 📝"
	python3 $(CMAKE_DIR)/scripts/configure_cmake_for_target.py $(TARGET_BOARD) -p $(CMAKE_DIR)/config -a $(ROOT_DIR)/mbed_app.json

config_cmake:
	@echo ""
	@echo "🏃 Running cmake configuration script 📝"
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR); cmake -GNinja -DTARGET_BOARD="$(TARGET_BOARD)" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ..

#
# MARK:- Tools targets
#

clang_format:
	@echo ""
	@echo "🕵️ Running clang-format 🔍"
	python3 tools/run-clang-format.py -r --extension=h,c,cpp --color=always --style=file ./src ./drivers ./libs ./spikes ./tests

clang_format_fix:
	@echo ""
	@echo "🕵️ Running clang-format & fixing files ♻️"
	python3 tools/run-clang-format.py -r -i --extension=h,c,cpp --color=always --style=file ./src ./drivers ./libs ./spikes ./tests

#
# MARK:- Mbed targets
#

clone_mbed:
	@echo ""
	@echo "🧬 Cloning Mbed OS ⚗️"
	@rm -rf $(MBED_OS_DIR)
	git clone --depth=1 --branch=$(BRANCH) https://github.com/ARMmbed/mbed-os $(MBED_OS_DIR)
	@echo ""
	@echo "🔗 Symlinking templates to Mbed OS directory 🗂️"
	ln -sf $(CMAKE_DIR)/templates/Template_MbedOS_CMakelists.txt $(MBED_OS_DIR)/CMakeLists.txt
	ln -sf $(CMAKE_DIR)/templates/Template_MbedOS_mbedignore.txt $(MBED_OS_DIR)/.mbedignore

curl_mbed:
	@echo ""
	@echo "🧬 Curling Mbed OS ⚗️"
	@rm -rf $(MBED_OS_DIR)
	@mkdir -p $(MBED_OS_DIR)
	curl -O -L https://github.com/ARMmbed/mbed-os/archive/$(VERSION).tar.gz
	tar -xzf $(VERSION).tar.gz --strip-components=1 -C extern/mbed-os
	rm -rf $(VERSION).tar.gz
	@echo ""
	@echo "🔗 Symlinking templates to Mbed OS directory 🗂️"
	ln -sf $(CMAKE_DIR)/templates/Template_MbedOS_CMakelists.txt $(MBED_OS_DIR)/CMakeLists.txt
	ln -sf $(CMAKE_DIR)/templates/Template_MbedOS_mbedignore.txt $(MBED_OS_DIR)/.mbedignore

#
# MARK:- Utils targets
#

clean:
	@echo ""
	@echo "⚠️  Cleaning up build & cmake/config directories 🧹"
	rm -rf $(BUILD_DIR)
	rm -rf $(CMAKE_DIR)/config

flashFront: all
	openocd -f openocd.cfg -c 'program $(BIN_PATH_FRONT) 0x08000000' -c 'sleep 200' -c 'reset run' -c 'exit'

flashBack: all
	openocd -f openocd.cfg -c 'program $(BIN_PATH_BACK) 0x08000000' -c 'sleep 200' -c 'reset run' -c 'exit'

flashADCPrint: all
	openocd -f openocd.cfg -c 'program $(BIN_PATH_ADCPRINT) 0x08000000' -c 'sleep 200' -c 'reset run' -c 'exit'

term:
	mbed sterm -b $(BAUDRATE) -p $(PORT)
