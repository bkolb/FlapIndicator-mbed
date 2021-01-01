add_mbed_executable(front)

target_sources(front
  PRIVATE
    main.cpp
)

target_include_directories(front
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(front lib_common_flap)
