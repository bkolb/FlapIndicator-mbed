add_mbed_executable(back)

target_sources(back
  PRIVATE
    main.cpp
)

target_include_directories(back
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(back lib_common_flap_mbed)
