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
 * @brief General Purpose IO
 *
 * Gpio is the General Purpose IO interface to libmaa. It's features depends on
 * the board type used, it can use gpiolibs (exported via a kernel module
 * through sysfs), or memory mapped IO via a /dev/uio device or /dev/mem
 * depending again on the board configuratio, or memory mapped IO via a
 * /dev/uio device or /dev/mem depending again on the board configuration
 *
 * @snippet gpio_read6.c Interesting
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SWIGPYTHON
#include <Python.h>
#endif

#include <stdio.h>
#include <pthread.h>

#include "common.h"

/**
 * Opaque pointer definition to the internal struct _gpio
 */
typedef struct _gpio* maa_gpio_context;

/**
 * Gpio Output modes
 */
typedef enum {
    MAA_GPIO_STRONG     = 0, /**< Default. Strong high and low */
    MAA_GPIO_PULLUP     = 1, /**< Resistive High */
    MAA_GPIO_PULLDOWN   = 2, /**< Resistive Low */
    MAA_GPIO_HIZ        = 3  /**< High Z State */
} gpio_mode_t;

/**
 * Gpio Direction options
 */
typedef enum {
    MAA_GPIO_OUT    = 0, /**< Output. A Mode can also be set */
    MAA_GPIO_IN     = 1  /**< Input */
} gpio_dir_t;

/**
 * Gpio Edge types for interupts
 */
typedef enum {
    MAA_GPIO_EDGE_NONE    = 0, /**< No interrupt on Gpio */
    MAA_GPIO_EDGE_BOTH    = 1, /**< Interupt on rising & falling */
    MAA_GPIO_EDGE_RISING  = 2, /**< Interupt on rising only */
    MAA_GPIO_EDGE_FALLING = 3  /**< Interupt on falling only */
} gpio_edge_t;

/**
 * Initialise gpio_context, based on board number
 *
 *  @param pin Pin number read from the board, i.e IO3 is 3
 *  @returns gpio context or NULL
 */
maa_gpio_context maa_gpio_init(int pin);

/**
 * Initialise gpio context without any mapping to a pin
 *
 * @param gpiopin gpio pin as listed in SYSFS
 * @return gpio context or NULL
 */
maa_gpio_context maa_gpio_init_raw(int gpiopin);

/**
 * Set the edge mode on the gpio
 *
 * @param dev The Gpio context
 * @param mode The edge mode to set the gpio into
 * @return Result of operation
 */
maa_result_t maa_gpio_edge_mode(maa_gpio_context dev, gpio_edge_t mode);

/**
 * Set an interupt on pin
 *
 * @param dev The Gpio context
 * @param edge The edge mode to set the gpio into
 * @param fptr Function pointer to function to be called when interupt is
 * triggered
 * @param args Arguments passed to the interrupt handler (fptr)
 * @return Result of operation
 */
maa_result_t maa_gpio_isr(maa_gpio_context dev, gpio_edge_t edge, void (*fptr)(void *), void * args);

/**
 * Stop the current interupt watcher on this Gpio, and set the Gpio edge mode
 * to MAA_GPIO_EDGE_NONE
 *
 * @param dev The Gpio context
 * @return Result of operation
 */
maa_result_t maa_gpio_isr_exit(maa_gpio_context dev);

/**
 * Set Gpio Output Mode,
 *
 * @param dev The Gpio context
 * @param mode The Gpio Output Mode
 * @return Result of operation
 */
maa_result_t maa_gpio_mode(maa_gpio_context dev, gpio_mode_t mode);

/**
 * Set Gpio direction
 *
 * @param dev The Gpio context
 * @param dir The direction of the Gpio
 * @return Result of operation
 */
maa_result_t maa_gpio_dir(maa_gpio_context dev, gpio_dir_t dir);

/**
 * Close the Gpio context
 * - Will free the memory for the context and unexport the Gpio
 *
 * @param dev The Gpio context
 * @return Result of operation
 */
maa_result_t maa_gpio_close(maa_gpio_context dev);

/**
 * Read the Gpio value.
 *
 * @param dev The Gpio context
 * @return Result of operation
 */
int maa_gpio_read(maa_gpio_context dev);

/**
 * Write to the Gpio Value.
 *
 * @param dev The Gpio context
 * @param value Integer value to write
 * @return Result of operation
 */
maa_result_t maa_gpio_write(maa_gpio_context dev, int value);

/**
 * Change ownership of the context.
 *
 * @param dev The Gpio context
 * @param owner Does this context own the pin
 * @return Result of operation
 */
maa_result_t maa_gpio_owner(maa_gpio_context dev, maa_boolean_t owner);

/**
 * Enable using memory mapped io instead of sysfs
 *
 * @param dev The Gpio context
 * @param mmap Use mmap instead of sysfs
 * @return Result of operation
 */
maa_result_t maa_gpio_use_mmaped(maa_gpio_context dev, maa_boolean_t mmap);

#ifdef __cplusplus
}
#endif
