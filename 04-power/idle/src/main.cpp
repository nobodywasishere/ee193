/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <power/power.h>

#include "leds.h"

LEDControl leds;

void main(void)
{
    leds = LEDControl();
    leds.black();
    pm_device_state_set(cons, DEVICE_PM_LOW_POWER_STATE, NULL, NULL);
    // k_msleep(100000);
}
