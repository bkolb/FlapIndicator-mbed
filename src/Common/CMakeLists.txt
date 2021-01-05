# Mbed CMake Template
# Copyright 2020 Ladislas de Toldi (ladislas [at] detoldi.me)
# SPDX-License-Identifier: Apache-2.0

add_library(lib_common_flap STATIC)

target_sources(lib_common_flap
  PRIVATE
    AbstractFlapPosReader.cpp
    AbstractStateExchange.cpp
    cmd/AbstractCmd.cpp
    cmd/LedCmd.cpp
    cmd/VarioCmd.cpp
)

target_include_directories(lib_common_flap
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(lib_common_flap)