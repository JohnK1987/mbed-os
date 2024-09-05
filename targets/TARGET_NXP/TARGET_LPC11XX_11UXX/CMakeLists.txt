# Copyright (c) 2020-2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0


set(STARTUP_FILE device/TOOLCHAIN_GCC_ARM/startup_LPC11xx.S)
set(LINKER_FILE device/TOOLCHAIN_GCC_ARM/LPC11U24.ld)


add_subdirectory(TARGET_LPC11U24_301 EXCLUDE_FROM_ALL)
add_subdirectory(TARGET_LPC11U24_401 EXCLUDE_FROM_ALL)

add_library(mbed-lpc11u24 INTERFACE)

target_include_directories(mbed-lpc11u24
    INTERFACE
        .
        device
)

target_sources(mbed-lpc11u24
    INTERFACE
        analogin_api.c
        gpio_api.c
        gpio_irq_api.c
        i2c_api.c
        pinmap.c
        port_api.c
        pwmout_api.c
        serial_api.c
        sleep.c
        spi_api.c
        us_ticker.c
        device/cmsis_nvic.c
        ${STARTUP_FILE}
)
mbed_set_linker_script(mbed-lpc11u24 ${CMAKE_CURRENT_SOURCE_DIR}/${LINKER_FILE})
target_link_libraries(mbed-lpc11u24 INTERFACE mbed-nxp)