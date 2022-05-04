/*
 * Copyright (c) 2016 Intel Corporation
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

/*
SDA - PA15
SCL - PB15
*/

#include <zephyr.h>
#include <sys/printk.h>

#include <device.h>
#include <drivers/i2c.h>

#define STTS751_I2C_ADDR 0x48
#define TEMP_VAL_HIGH_REG_ADDR 0x00

// #define STTS751_DEVNAME DT_LABEL(DT_INST(0, st_stts751))

#define DEV_OK 0

static void read_temperature(struct device *dev)
{
  uint8_t data;

  data = TEMP_VAL_HIGH_REG_ADDR;
  if (i2c_write(dev, &data, sizeof(data), STTS751_I2C_ADDR) != DEV_OK)
  {
    printk("Error on i2c_write()\n");
    return;
  }

  data = 0;
  if (i2c_read(dev, &data, sizeof(data), STTS751_I2C_ADDR) != DEV_OK)
  {
    printk("Error on i2c_read()\n");
    return;
  }

  printk("Temperature read successfully: %d C\n", data);
}

static void read_temperature_by_transfer(struct device *dev)
{
  struct i2c_msg msg[2];
  uint8_t write_data = TEMP_VAL_HIGH_REG_ADDR;
  uint8_t read_data = 0;

  msg[0].flags = I2C_MSG_WRITE | I2C_MSG_RESTART;
  msg[0].buf = &write_data;
  msg[0].len = sizeof(write_data);

  msg[1].flags = I2C_MSG_READ | I2C_MSG_STOP;
  msg[1].buf = &read_data;
  msg[1].len = sizeof(read_data);

  if (i2c_transfer(dev, msg, 2, STTS751_I2C_ADDR) != DEV_OK)
  {
    printk("Error on i2c_transfer()\n");
    return;
  }

  printk("Temperature read successfully: %d C\n", read_data);
}

uint32_t cfg = I2C_SPEED_SET(I2C_SPEED_STANDARD) | I2C_MODE_MASTER;

void main(void)
{
  struct device *dev;

  printk("Start read temp. sensor app\n");

  // cfg.raw = 0;
  // cfg.bits.use_10_bit_addr = 0;
  // cfg.bits.speed = I2C_SPEED_STANDARD;
  // cfg.bits.is_master_device = 1;

  dev = device_get_binding("STTS751");
//   printk(dev->device_config.name)
  if (!dev)
  {
    printk("I2C: Device not found.\n");
    return;
  }

  if (i2c_configure(dev, cfg) != DEV_OK)
  {
    printk("Error on i2c_configure()\n");
    return;
  }

  read_temperature(dev);
  read_temperature_by_transfer(dev);
}