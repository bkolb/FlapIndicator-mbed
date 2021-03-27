add_mbed_executable(adcprint)

target_sources(adcprint
  PRIVATE
    main.cpp
    
)

target_include_directories(adcprint
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(adcprint lib_common_flap lib_common_flap_mbed)
