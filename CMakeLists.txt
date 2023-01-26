cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(jester)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

set(PICO_CXX_ENABLE_RTTI 1)
# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

include("PicoLED/PicoLed.cmake")

add_executable(jester jester.cpp)

target_link_libraries(jester pico_stdlib PicoLed)

pico_enable_stdio_uart(jester 0)
pico_enable_stdio_usb(jester 1)


pico_add_extra_outputs(jester)
