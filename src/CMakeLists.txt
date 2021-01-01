# Mbed CMake Template
# Copyright 2020 Ladislas de Toldi (ladislas [at] detoldi.me)
# SPDX-License-Identifier: Apache-2.0

add_mbed_executable(main_project)

target_sources(main_project
  PRIVATE
    main.cpp
)

target_include_directories(main_project
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(main_project lib_hello_world)
