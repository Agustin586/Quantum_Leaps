# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

# Pull in FreeRTOS
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_LIST_DIR}/freertos)
include(FreeRTOS_Kernel_import.cmake)

# Project name
project(pico-freertos)

pico_sdk_init()

# Configuration projects
add_executable(pico-freertos
    qpc/qm/main.c
)

target_include_directories(pico-freertos PRIVATE
    include/
    ${PROJECT_SOURCE_DIR}/qpc/include
    ${PROJECT_SOURCE_DIR}/qpc/ports
    ${PROJECT_SOURCE_DIR}/qpc/qm
)

target_link_libraries(pico-freertos PRIVATE
    pico_stdlib
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4
)

target_compile_options(pico-freertos PRIVATE -Wall)

# Run the entire project in SRAM
# pico_set_binary_type(pico-freertos copy_to_ram)

pico_add_extra_outputs(pico-freertos)

# Agregar archivos fuente de QPC
file(GLOB_RECURSE QPC_SOURCES 
    "${PROJECT_SOURCE_DIR}/qpc/src/qf/*.c"
    "${PROJECT_SOURCE_DIR}/qpc/qm/*.c"
    "${PROJECT_SOURCE_DIR}/qpc/ports/*.c"
)

# Agregar los archivos fuente de QPC al ejecutable
target_sources(pico-freertos PRIVATE ${QPC_SOURCES})

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pico-freertos 0)
pico_enable_stdio_usb(pico-freertos 1)
