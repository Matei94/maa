/*
 * Author: Thomas Ingleby <thomas.c.ingleby@intel.com>
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

/**
 * @file
 * @brief Pulse Width Modulation module
 *
 * PWM is the Pulse Width Modulation interface to libmaa. It allows the
 * generation of a signal on a pin. Some boards may have higher or lower levels
 * of resolution so make sure you check the board & pin you are using before
 * hand.
 *
 * @snippet cycle-pwm3.c Interesting
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <fcntl.h>

#include "common.h"

typedef struct _pwm* maa_pwm_context;

/**
 * Initialise pwm_context, uses board mapping
 *
 * @param pin The PWM PIN
 * @return pwm context or NULL
 */
maa_pwm_context maa_pwm_init(int pin);

/**
 * Initialise pwm_context, raw mode
 *
 * @param chipid The chip inwhich the PWM is under in SYSFS
 * @param pin The PWM PIN.
 * @return pwm context or NULL
 */
maa_pwm_context maa_pwm_init_raw(int chipid, int pin);

/**
 * Set the ouput duty-cycle percentage, as a float
 *
 * @param dev The Pwm context to use
 * @param percentage A floating-point value representing percentage of output.
 *    The value should lie between 0.0f (representing on 0%) and 1.0f
 *    Values above or below this range will be set at either 0.0f or 1.0f
 * @return Result of operation
 */
maa_result_t maa_pwm_write(maa_pwm_context dev, float percentage);

/**
 * Read the ouput duty-cycle percentage, as a float
 *
 * @param dev The Pwm context to use
 * @return percentage A floating-point value representing percentage of output.
 *    The value should lie between 0.0f (representing on 0%) and 1.0f
 *    Values above or below this range will be set at either 0.0f or 1.0f
 */
float maa_pwm_read(maa_pwm_context dev);

/**
 * Set the PWM period as seconds represented in a float
 *
 * @param dev The Pwm context to use
 * @param seconds Period represented as a float in seconds
 * @return Result of operation
 */
maa_result_t maa_pwm_period(maa_pwm_context dev, float seconds);

/**
 * Set period, milliseconds.
 *
 * @param dev The Pwm context to use
 * @param ms Milliseconds for period
 * @return Result of operation
 */
maa_result_t maa_pwm_period_ms(maa_pwm_context dev, int ms);

/**
 * Set period, microseconds
 *
 * @param dev The Pwm context to use
 * @param us Microseconds as period
 * @return Result of operation
 */
maa_result_t maa_pwm_period_us(maa_pwm_context dev, int us);

/**
 * Set pulsewidth, As represnted by seconds in a (float)
 *
 * @param dev The Pwm context to use
 * @param seconds The duration of a pulse
 * @return Result of operation
 */
maa_result_t maa_pwm_pulsewidth(maa_pwm_context dev, float seconds);

/**
 * Set pulsewidth, milliseconds
 *
 * @param dev The Pwm context to use
 * @param ms Milliseconds for pulsewidth
 * @return Result of operation
 */
maa_result_t maa_pwm_pulsewidth_ms(maa_pwm_context dev, int ms);

/**
 * Set pulsewidth, microseconds
 *
 * @param dev The Pwm context to use
 * @param us Microseconds for pulsewidth
 * @return Result of operation
 */
maa_result_t maa_pwm_pulsewidth_us(maa_pwm_context dev, int us);

/**
 * Set the enable status of the PWM pin. None zero will assume on with output being driven.
 *   and 0 will disable the output.
 *
 * @param dev The pwm context to use
 * @param enable Toggle status of pin
 * @return Result of operation.
 */
maa_result_t maa_pwm_enable(maa_pwm_context dev, int enable);

/**
 * Change ownership of context
 *
 * @param dev the context
 * @param owner Ownership boolean
 * @return Result of operation
 */
maa_result_t maa_pwm_owner(maa_pwm_context dev, maa_boolean_t owner);

/**
 * Close and unexport the PWM pin
 *
 * @param dev The pwm context to use
 * @return Result of operation
 */
maa_result_t maa_pwm_close(maa_pwm_context dev);

#ifdef __cplusplus
}
#endif
