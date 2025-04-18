# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

target_include_directories(mbed-wifi
    PUBLIC
        .
        mx_wifi
        mx_wifi/core
)

target_sources(mbed-wifi
    PRIVATE
        EMW3080BInterface.cpp
        EMW3080B_EMAC.cpp
        EMW3080B_UART.cpp
        EMW3080B_SPI.cpp
        mx_wifi_mbed_os.cpp
        mx_wifi/mx_wifi.c
        mx_wifi/core/checksumutils.c
        mx_wifi/core/mx_wifi_hci.c
        mx_wifi/core/mx_wifi_ipc.c
        mx_wifi/core/mx_wifi_slip.c
)

# This driver needs utility functions from LwIP
target_link_libraries(mbed-wifi
    PRIVATE
        mbed-lwipstack
)

# Link override object file coming from static library anyway
#
# NOTE: This linker option is to pretend undefined symbol and won't cause
#       undefined symbol error even though the override object file actually
#       doesn't provide such symbol definition.
if(${MBED_TOOLCHAIN} STREQUAL "GCC_ARM")
    target_link_options(mbed-wifi
        INTERFACE
            LINKER:--undefined=LINK_EMW3080BINTERFACE_CPP
    )
endif()
