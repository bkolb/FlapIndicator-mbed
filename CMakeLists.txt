# Mbed CMake Template
# Copyright 2020 Ladislas de Toldi (ladislas [at] detoldi.me)
# SPDX-License-Identifier: Apache-2.0

# mbed-cmake requires at least CMake 3.18
cmake_minimum_required(VERSION 3.19)

# Activate ccache
find_program(CCACHE "ccache")
if(CCACHE)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()

# ⚠️ Before all, include mbed-cmake.cmake
include(./mbed-cmake.cmake)

# Then configure name of the project
project("Mbed CMake Template" LANGUAGES C CXX ASM)

# For convenience you can define useful variables
set(SRC_DIR ${ROOT_DIR}/src)
set(SPIKES_DIR ${ROOT_DIR}/spikes)
set(TARGETS_DIR ${ROOT_DIR}/targets)

# Add custom target subdirectory
add_target_board_subdirectory("${TARGET_BOARD}")

# Add libraries
add_subdirectory(${SRC_DIR}/Common)
add_subdirectory(${SRC_DIR}/CommonMbed)
add_subdirectory(${SRC_DIR}/FrontSeat)
add_subdirectory(${SRC_DIR}/BackSeat)
add_subdirectory(${SRC_DIR}/ADCPrint)

# If you use spikes to test features, you can add them here
# add_subdirectory(${SPIKES_DIR}/blinky)

# Add the main source files of the project from ./src
#add_subdirectory(${ROOT_DIR}/src)

# Finally print the mbed-cmake build report
mbed_cmake_print_build_report()
