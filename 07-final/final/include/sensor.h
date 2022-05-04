#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/i2c.h>

#pragma once

#define TEMP_SENSE_ADDRESS 0x48

class Sensor {

    private:
        uint32_t cfg;
        const struct device *i2c_dev;
        
    public:
        Sensor();
        int initDevice();
        int configureDevice();
        inline bool deviceIsReady() {return device_is_ready(i2c_dev);}
        uint16_t getTemperature();
};