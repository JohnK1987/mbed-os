# Copyright (c) 2023 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_subdirectory(STM32Cube_FW EXCLUDE_FROM_ALL)
add_subdirectory(TARGET_STM32U083xC EXCLUDE_FROM_ALL)

add_library(mbed-stm32u0 INTERFACE)

target_sources(mbed-stm32u0
    INTERFACE
    clock_cfg/system_clock.c
    analogin_device.c
    analogout_device.c
    gpio_irq_device.c
    pwmout_device.c
    serial_device.c
)

target_include_directories(mbed-stm32u0
    INTERFACE
        .
)

target_link_libraries(mbed-stm32u0 INTERFACE mbed-stm mbed-stm32u0cube-fw)
