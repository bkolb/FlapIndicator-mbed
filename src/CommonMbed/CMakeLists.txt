# Mbed CMake Template
# Copyright 2020 Ladislas de Toldi (ladislas [at] detoldi.me)
# SPDX-License-Identifier: Apache-2.0

add_library(lib_common_flap_mbed STATIC)

target_sources(lib_common_flap_mbed
  PRIVATE
    ADCFlapPosReader.cpp
    DIOFlapIndicator.cpp
    UARTStateExchange.cpp
)

target_include_directories(lib_common_flap_mbed
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(lib_common_flap_mbed lib_common_flap mbed-os)