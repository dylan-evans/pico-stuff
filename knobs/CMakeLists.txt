cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_knob C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(knob knob.c)

pico_enable_stdio_usb(knob 1)
pico_enable_stdio_uart(knob 1)

pico_add_extra_outputs(knob)

target_link_libraries(knob pico_stdlib pico_multicore hardware_adc pico_double)

