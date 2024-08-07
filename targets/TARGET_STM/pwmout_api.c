/* mbed Microcontroller Library
 *******************************************************************************
 * Copyright (c) 2015, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#include "pwmout_api.h"

#if DEVICE_PWMOUT

#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"
#include "PeripheralPins.h"
#include "pwmout_device.h"

#include <math.h>

static TIM_HandleTypeDef TimHandle;

// Maximum counts per timer cycle.
// Note: Hardware can do 65536, but I don't believe you can have 100% duty cycle with 65536 counts/cycle.
#define MAX_COUNTS_PER_CYCLE 65535

// Maximum prescaler division possible
#define MAX_PRESCALER 65536 

// Change to 1 to enable debug prints of what's being calculated.
// Must comment out the critical section calls in PwmOut to use.
#define STM_PWMOUT_DEBUG 0

#if STM_PWMOUT_DEBUG
#include <stdio.h>
#include <inttypes.h>
#endif

/* Convert STM32 Cube HAL channel to LL channel */
uint32_t TIM_ChannelConvert_HAL2LL(uint32_t channel, pwmout_t *obj)
{
#if !defined(PWMOUT_INVERTED_NOT_SUPPORTED)
    if (obj->inverted) {
        switch (channel) {
            case TIM_CHANNEL_1  :
                return LL_TIM_CHANNEL_CH1N;
            case TIM_CHANNEL_2  :
                return LL_TIM_CHANNEL_CH2N;
            case TIM_CHANNEL_3  :
                return LL_TIM_CHANNEL_CH3N;
#if defined(LL_TIM_CHANNEL_CH4N)
            case TIM_CHANNEL_4  :
                return LL_TIM_CHANNEL_CH4N;
#endif
            default : /* Optional */
                return 0;
        }
    } else
#endif
    {
        switch (channel) {
            case TIM_CHANNEL_1  :
                return LL_TIM_CHANNEL_CH1;
            case TIM_CHANNEL_2  :
                return LL_TIM_CHANNEL_CH2;
            case TIM_CHANNEL_3  :
                return LL_TIM_CHANNEL_CH3;
            case TIM_CHANNEL_4  :
                return LL_TIM_CHANNEL_CH4;
            default : /* Optional */
                return 0;
        }
    }
}

#if STATIC_PINMAP_READY
#define PWM_INIT_DIRECT pwmout_init_direct
void pwmout_init_direct(pwmout_t *obj, const PinMap *pinmap)
#else
#define PWM_INIT_DIRECT _pwmout_init_direct
static void _pwmout_init_direct(pwmout_t *obj, const PinMap *pinmap)
#endif
{
    // Get the peripheral name from the pin and assign it to the object
    obj->pwm = (PWMName)pinmap->peripheral;
    MBED_ASSERT(obj->pwm != (PWMName)NC);

    // Get the functions (timer channel, (non)inverted) from the pin and assign it to the object
    uint32_t function = (uint32_t)pinmap->function;
    MBED_ASSERT(function != (uint32_t)NC);
    obj->channel = STM_PIN_CHANNEL(function);
    obj->inverted = STM_PIN_INVERTED(function);

    // Enable TIM clock
#if defined(TIM1_BASE)
    if (obj->pwm == PWM_1) {
        __HAL_RCC_TIM1_CLK_ENABLE();
    }
#endif
#if defined(TIM2_BASE)
    if (obj->pwm == PWM_2) {
        __HAL_RCC_TIM2_CLK_ENABLE();
    }
#endif
#if defined(TIM3_BASE)
    if (obj->pwm == PWM_3) {
        __HAL_RCC_TIM3_CLK_ENABLE();
    }
#endif
#if defined(TIM4_BASE)
    if (obj->pwm == PWM_4) {
        __HAL_RCC_TIM4_CLK_ENABLE();
    }
#endif
#if defined(TIM5_BASE)
    if (obj->pwm == PWM_5) {
        __HAL_RCC_TIM5_CLK_ENABLE();
    }
#endif
#if defined(TIM8_BASE)
    if (obj->pwm == PWM_8) {
        __HAL_RCC_TIM8_CLK_ENABLE();
    }
#endif
#if defined(TIM9_BASE)
    if (obj->pwm == PWM_9) {
        __HAL_RCC_TIM9_CLK_ENABLE();
    }
#endif
#if defined(TIM10_BASE)
    if (obj->pwm == PWM_10) {
        __HAL_RCC_TIM10_CLK_ENABLE();
    }
#endif
#if defined(TIM11_BASE)
    if (obj->pwm == PWM_11) {
        __HAL_RCC_TIM11_CLK_ENABLE();
    }
#endif
#if defined(TIM12_BASE)
    if (obj->pwm == PWM_12) {
        __HAL_RCC_TIM12_CLK_ENABLE();
    }
#endif
#if defined(TIM13_BASE)
    if (obj->pwm == PWM_13) {
        __HAL_RCC_TIM13_CLK_ENABLE();
    }
#endif
#if defined(TIM14_BASE)
    if (obj->pwm == PWM_14) {
        __HAL_RCC_TIM14_CLK_ENABLE();
    }
#endif
#if defined(TIM15_BASE)
    if (obj->pwm == PWM_15) {
        __HAL_RCC_TIM15_CLK_ENABLE();
    }
#endif
#if defined(TIM16_BASE)
    if (obj->pwm == PWM_16) {
        __HAL_RCC_TIM16_CLK_ENABLE();
    }
#endif
#if defined(TIM17_BASE)
    if (obj->pwm == PWM_17) {
        __HAL_RCC_TIM17_CLK_ENABLE();
    }
#endif
#if defined(TIM18_BASE)
    if (obj->pwm == PWM_18) {
        __HAL_RCC_TIM18_CLK_ENABLE();
    }
#endif
#if defined(TIM19_BASE)
    if (obj->pwm == PWM_19) {
        __HAL_RCC_TIM19_CLK_ENABLE();
    }
#endif
#if defined(TIM20_BASE)
    if (obj->pwm == PWM_20) {
        __HAL_RCC_TIM20_CLK_ENABLE();
    }
#endif
#if defined(TIM21_BASE)
    if (obj->pwm == PWM_21) {
        __HAL_RCC_TIM21_CLK_ENABLE();
    }
#endif
#if defined(TIM22_BASE)
    if (obj->pwm == PWM_22) {
        __HAL_RCC_TIM22_CLK_ENABLE();
    }
#endif
    // Configure GPIO
    pin_function(pinmap->pin, pinmap->function);

    obj->pin = pinmap->pin;
    obj->period = 0;
    obj->compare_value = 0;
    obj->top_count = 1;

    pwmout_period_us(obj, 20000); // 20 ms per default
}

void pwmout_init(pwmout_t *obj, PinName pin)
{
    int peripheral = (int)pinmap_peripheral(pin, PinMap_PWM);
    int function = (int)pinmap_find_function(pin, PinMap_PWM);

    const PinMap static_pinmap = {pin, peripheral, function};

    PWM_INIT_DIRECT(obj, &static_pinmap);
}

void pwmout_free(pwmout_t *obj)
{
    // Configure GPIO back to reset value
    pin_function(obj->pin, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0));
}

void pwmout_write(pwmout_t *obj, float value)
{
    TIM_OC_InitTypeDef sConfig;
    int channel = 0;

    TimHandle.Instance = (TIM_TypeDef *)(obj->pwm);

    if (value < (float)0.0) {
        value = 0.0;
    } else if (value > (float)1.0) {
        value = 1.0;
    }

    // Calculate the correct compare value.  The PWM output changes to 0 once the counter becomes
    // >= the compare value.
    // Examples:
    // - if value is .999 and counts is 3, we want to write 3 so the PWM is on all the time
    // - if value is .33 and counts is 3, we want to write 1 so that we turn off after the counter becomes 1.
    // - if value is .1 and counts is 3, that rounds to 0 so we want to write 0 so that the PWM is off all the time

    obj->compare_value = lroundf((float)obj->top_count * value);

#if STM_PWMOUT_DEBUG
    printf("Setting compare value to %" PRIu32 "\n", obj->compare_value);
#endif

    // Configure channels
    sConfig.OCMode       = TIM_OCMODE_PWM1;
    sConfig.Pulse        = obj->compare_value;
    sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
    sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
#if defined(TIM_OCIDLESTATE_RESET)
    sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;
#endif
#if defined(TIM_OCNIDLESTATE_RESET)
    sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
    sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
#endif

    switch (obj->channel) {
        case 1:
            channel = TIM_CHANNEL_1;
            break;
        case 2:
            channel = TIM_CHANNEL_2;
            break;
        case 3:
            channel = TIM_CHANNEL_3;
            break;
        case 4:
            channel = TIM_CHANNEL_4;
            break;
        default:
            return;
    }

    if (LL_TIM_CC_IsEnabledChannel(TimHandle.Instance, TIM_ChannelConvert_HAL2LL(channel, obj)) == 0) {
        // If channel is not enabled, proceed to channel configuration
        if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, channel) != HAL_OK) {
            error("Cannot initialize PWM\n");
        }
    } else {
        // If channel already enabled, only update compare value to avoid glitch
        __HAL_TIM_SET_COMPARE(&TimHandle, channel, sConfig.Pulse);
        return;
    }

#if !defined(PWMOUT_INVERTED_NOT_SUPPORTED)
    if (obj->inverted) {
        HAL_TIMEx_PWMN_Start(&TimHandle, channel);
    } else
#endif
    {
        HAL_TIM_PWM_Start(&TimHandle, channel);
    }
}

float pwmout_read(pwmout_t *obj)
{
    float value = 0;
    if (obj->period > 0) {
        value = (float)(obj->compare_value) / (float)(obj->top_count);
    }
    return ((value > (float)1.0) ? (float)(1.0) : (value));
}

void pwmout_period(pwmout_t *obj, float seconds)
{
    pwmout_period_us(obj, seconds * 1000000.0f);
}

void pwmout_period_ms(pwmout_t *obj, int ms)
{
    pwmout_period_us(obj, ms * 1000);
}

void pwmout_period_us(pwmout_t *obj, int us)
{
    TimHandle.Instance = (TIM_TypeDef *)(obj->pwm);
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    uint32_t PclkFreq = 0;
    uint32_t APBxCLKDivider = RCC_HCLK_DIV1;
    float dc = pwmout_read(obj);
    uint8_t i = 0;

    __HAL_TIM_DISABLE(&TimHandle);

    // Get clock configuration
    // Note: PclkFreq contains here the Latency (not used after)
    HAL_RCC_GetClockConfig(&RCC_ClkInitStruct, &PclkFreq);

    /*  Parse the pwm / apb mapping table to find the right entry */
    while (pwm_apb_map_table[i].pwm != obj->pwm) {
        i++;
    }

    if (pwm_apb_map_table[i].pwm == 0) {
        error("Unknown PWM instance");
    }

    if (pwm_apb_map_table[i].pwmoutApb == PWMOUT_ON_APB1) {
        PclkFreq = HAL_RCC_GetPCLK1Freq();
        APBxCLKDivider = RCC_ClkInitStruct.APB1CLKDivider;
    } else {
#if !defined(PWMOUT_APB2_NOT_SUPPORTED)
        PclkFreq = HAL_RCC_GetPCLK2Freq();
        APBxCLKDivider = RCC_ClkInitStruct.APB2CLKDivider;
#endif
    }

    // TIMxCLK = PCLKx when the APB prescaler = 1 else TIMxCLK = 2 * PCLKx
    uint32_t timxClk;
    if (APBxCLKDivider == RCC_HCLK_DIV1) {
        timxClk = PclkFreq;
    } else {
        timxClk = PclkFreq * 2;
    }

    // To generate the desired frequency, we have 2 knobs to play with: the reload value and the
    // duty cycle.  We generally want to have the reload value as high as possible since that will
    // give the best duty cycle resolution at high frequencies.

    // Step 1: Calculate the smallest prescaler that will allow the desired period to be achieved by
    // tuning the reload value.
    // (prescaler * reloadValue) / (timxClk) = period
    // prescaler = (period * timxClk) / reloadValue
    // minimum needed prescaler (floating point) = (period * timxClk) / 65536

    const float periodSeconds = us * 1e-6f;
    const uint32_t prescaler = ceilf(periodSeconds * timxClk / MAX_COUNTS_PER_CYCLE);
    MBED_ASSERT(prescaler <= MAX_PRESCALER);

    // Step 2: Calculate top count based on determined prescaler
    // reloadValue = period * timxClk / prescaler
    uint32_t topCount = lroundf(periodSeconds * timxClk / prescaler);
    MBED_ASSERT(topCount <= MAX_COUNTS_PER_CYCLE);

#if STM_PWMOUT_DEBUG
    printf("Setting prescaler to %" PRIu32 " and top count to %" PRIu32 "\n", prescaler, topCount);
#endif

    TimHandle.Init.Prescaler = prescaler - 1; // value of 0 means divide by 1
    TimHandle.Init.Period = topCount - 1; // value of 0 means count once

    TimHandle.Init.ClockDivision = 0; // Dead time generators and digital filters use CK_INT directly
    TimHandle.Init.CounterMode   = TIM_COUNTERMODE_UP;

    if (HAL_TIM_PWM_Init(&TimHandle) != HAL_OK) {
        error("Cannot initialize PWM\n");
    }

    // Save for future use
    obj->period = us;
    obj->top_count = topCount;

    // Set duty cycle again
    pwmout_write(obj, dc);

    __HAL_TIM_ENABLE(&TimHandle);
}

int pwmout_read_period_us(pwmout_t *obj)
{
    return obj->period;
}

void pwmout_pulsewidth(pwmout_t *obj, float seconds)
{
    pwmout_pulsewidth_us(obj, seconds * 1000000.0f);
}

void pwmout_pulsewidth_ms(pwmout_t *obj, int ms)
{
    pwmout_pulsewidth_us(obj, ms * 1000);
}

void pwmout_pulsewidth_us(pwmout_t *obj, int us)
{
    float value = (float)us / (float)obj->period;
    pwmout_write(obj, value);
}

int pwmout_read_pulsewidth_us(pwmout_t *obj)
{
    float pwm_duty_cycle = pwmout_read(obj);
    return lroundf(pwm_duty_cycle * (float)obj->period);
}

const PinMap *pwmout_pinmap()
{
    return PinMap_PWM;
}

#endif
