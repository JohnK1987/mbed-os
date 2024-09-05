# Copyright (c) 2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

include(mbed_set_post_build_nxp)

add_library(mbed-lpc11u24-301 INTERFACE)

target_include_directories(mbed-lpc11u24-301
    INTERFACE
        .
)

target_sources(mbed-lpc11u24-301
    INTERFACE
    PeripheralPins.c
)

target_link_libraries(mbed-lpc11u24-301 INTERFACE mbed-lpc11u24)
