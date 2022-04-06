/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1

/* The devicetree node identifier for the "led0" alias. */
// #define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
// static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);


void main(void)
{
	const struct device *dev = device_get_binding("GPIOA");
	int ret = gpio_pin_configure(dev, 9, GPIO_OUTPUT);

	if (ret < 0) {
		return;
	}

	while (1) {
		ret = gpio_pin_toggle(dev, 9);
		if (ret < 0)
		{
			return;
		}
		k_msleep(SLEEP_TIME_MS);
	}
}
