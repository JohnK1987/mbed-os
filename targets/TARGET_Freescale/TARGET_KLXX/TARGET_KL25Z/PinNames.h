/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* MBED TARGET LIST: KL25Z */

#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

#define PORT_SHIFT  12

typedef enum {
    PTA0 = 0x0,
    PTA1 = 0x4,
    PTA2 = 0x8,
    PTA3 = 0xc,
    PTA4 = 0x10,
    PTA5 = 0x14,
    PTA6 = 0x18,
    PTA7 = 0x1c,
    PTA8 = 0x20,
    PTA9 = 0x24,
    PTA10 = 0x28,
    PTA11 = 0x2c,
    PTA12 = 0x30,
    PTA13 = 0x34,
    PTA14 = 0x38,
    PTA15 = 0x3c,
    PTA16 = 0x40,
    PTA17 = 0x44,
    PTA18 = 0x48,
    PTA19 = 0x4c,
    PTA20 = 0x50,
    PTA21 = 0x54,
    PTA22 = 0x58,
    PTA23 = 0x5c,
    PTA24 = 0x60,
    PTA25 = 0x64,
    PTA26 = 0x68,
    PTA27 = 0x6c,
    PTA28 = 0x70,
    PTA29 = 0x74,
    PTA30 = 0x78,
    PTA31 = 0x7c,
    PTB0 = 0x1000,
    PTB1 = 0x1004,
    PTB2 = 0x1008,
    PTB3 = 0x100c,
    PTB4 = 0x1010,
    PTB5 = 0x1014,
    PTB6 = 0x1018,
    PTB7 = 0x101c,
    PTB8 = 0x1020,
    PTB9 = 0x1024,
    PTB10 = 0x1028,
    PTB11 = 0x102c,
    PTB12 = 0x1030,
    PTB13 = 0x1034,
    PTB14 = 0x1038,
    PTB15 = 0x103c,
    PTB16 = 0x1040,
    PTB17 = 0x1044,
    PTB18 = 0x1048,
    PTB19 = 0x104c,
    PTB20 = 0x1050,
    PTB21 = 0x1054,
    PTB22 = 0x1058,
    PTB23 = 0x105c,
    PTB24 = 0x1060,
    PTB25 = 0x1064,
    PTB26 = 0x1068,
    PTB27 = 0x106c,
    PTB28 = 0x1070,
    PTB29 = 0x1074,
    PTB30 = 0x1078,
    PTB31 = 0x107c,
    PTC0 = 0x2000,
    PTC1 = 0x2004,
    PTC2 = 0x2008,
    PTC3 = 0x200c,
    PTC4 = 0x2010,
    PTC5 = 0x2014,
    PTC6 = 0x2018,
    PTC7 = 0x201c,
    PTC8 = 0x2020,
    PTC9 = 0x2024,
    PTC10 = 0x2028,
    PTC11 = 0x202c,
    PTC12 = 0x2030,
    PTC13 = 0x2034,
    PTC14 = 0x2038,
    PTC15 = 0x203c,
    PTC16 = 0x2040,
    PTC17 = 0x2044,
    PTC18 = 0x2048,
    PTC19 = 0x204c,
    PTC20 = 0x2050,
    PTC21 = 0x2054,
    PTC22 = 0x2058,
    PTC23 = 0x205c,
    PTC24 = 0x2060,
    PTC25 = 0x2064,
    PTC26 = 0x2068,
    PTC27 = 0x206c,
    PTC28 = 0x2070,
    PTC29 = 0x2074,
    PTC30 = 0x2078,
    PTC31 = 0x207c,
    PTD0 = 0x3000,
    PTD1 = 0x3004,
    PTD2 = 0x3008,
    PTD3 = 0x300c,
    PTD4 = 0x3010,
    PTD5 = 0x3014,
    PTD6 = 0x3018,
    PTD7 = 0x301c,
    PTD8 = 0x3020,
    PTD9 = 0x3024,
    PTD10 = 0x3028,
    PTD11 = 0x302c,
    PTD12 = 0x3030,
    PTD13 = 0x3034,
    PTD14 = 0x3038,
    PTD15 = 0x303c,
    PTD16 = 0x3040,
    PTD17 = 0x3044,
    PTD18 = 0x3048,
    PTD19 = 0x304c,
    PTD20 = 0x3050,
    PTD21 = 0x3054,
    PTD22 = 0x3058,
    PTD23 = 0x305c,
    PTD24 = 0x3060,
    PTD25 = 0x3064,
    PTD26 = 0x3068,
    PTD27 = 0x306c,
    PTD28 = 0x3070,
    PTD29 = 0x3074,
    PTD30 = 0x3078,
    PTD31 = 0x307c,
    PTE0 = 0x4000,
    PTE1 = 0x4004,
    PTE2 = 0x4008,
    PTE3 = 0x400c,
    PTE4 = 0x4010,
    PTE5 = 0x4014,
    PTE6 = 0x4018,
    PTE7 = 0x401c,
    PTE8 = 0x4020,
    PTE9 = 0x4024,
    PTE10 = 0x4028,
    PTE11 = 0x402c,
    PTE12 = 0x4030,
    PTE13 = 0x4034,
    PTE14 = 0x4038,
    PTE15 = 0x403c,
    PTE16 = 0x4040,
    PTE17 = 0x4044,
    PTE18 = 0x4048,
    PTE19 = 0x404c,
    PTE20 = 0x4050,
    PTE21 = 0x4054,
    PTE22 = 0x4058,
    PTE23 = 0x405c,
    PTE24 = 0x4060,
    PTE25 = 0x4064,
    PTE26 = 0x4068,
    PTE27 = 0x406c,
    PTE28 = 0x4070,
    PTE29 = 0x4074,
    PTE30 = 0x4078,
    PTE31 = 0x407c,

    // USB Pins
    CONSOLE_TX = PTA2,
    CONSOLE_RX = PTA1,

#ifdef TARGET_FF_ARDUINO_UNO
    // Arduino Headers
    ARDUINO_UNO_D0 = PTA1,
    ARDUINO_UNO_D1 = PTA2,
    ARDUINO_UNO_D2 = PTD4,
    ARDUINO_UNO_D3 = PTA12,
    ARDUINO_UNO_D4 = PTA4,
    ARDUINO_UNO_D5 = PTA5,
    ARDUINO_UNO_D6 = PTC8,
    ARDUINO_UNO_D7 = PTC9,
    ARDUINO_UNO_D8 = PTA13,
    ARDUINO_UNO_D9 = PTD5,
    ARDUINO_UNO_D10 = PTD0,
    ARDUINO_UNO_D11 = PTD2,
    ARDUINO_UNO_D12 = PTD3,
    ARDUINO_UNO_D13 = PTD1,
    ARDUINO_UNO_D14 = PTE0,
    ARDUINO_UNO_D15 = PTE1,

    ARDUINO_UNO_A0 = PTB0,
    ARDUINO_UNO_A1 = PTB1,
    ARDUINO_UNO_A2 = PTB2,
    ARDUINO_UNO_A3 = PTB3,
    ARDUINO_UNO_A4 = PTC2,
    ARDUINO_UNO_A5 = PTC1,
#endif

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

// LEDs -------------------------------
#define LED1 PTB18 // LED_RED
#define LED2 PTB19 // LED_BLUE
#define LED3 PTD1 // LED_GREEN

// Touch Sensor Pins ------------------
#define TSI_ELEC0 PTB16
#define TSI_ELEC1 PTB17

/* PullDown not available for KL25 */
typedef enum {
    PullNone = 0,
    PullUp = 2,
    PullDefault = PullUp
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
