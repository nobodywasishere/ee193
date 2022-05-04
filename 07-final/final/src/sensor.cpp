#include "sensor.h"

Sensor::Sensor() {
    initDevice();
}

// Builds the Sensor 
int Sensor::initDevice() {
    i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c2));
    int deviceErr = configureDevice();
    if (deviceErr==0) {
        printk("Sensor Initialized!\n");
        if(deviceIsReady()) printk("Sensor Ready!\n");
    } else {
        printk("Sensor Error %d!\n", deviceErr);
    }
    return 0;
}

// Configures the Temperature Sensor Device
// Output: int, 0 if no error, 1 if error occured
int Sensor::configureDevice() {
    cfg = I2C_SPEED_SET(I2C_SPEED_FAST) | I2C_MODE_MASTER;
    if(!i2c_dev) return 1; // no device found
    if(i2c_configure(i2c_dev, cfg) != 0) return 2; // can't config device
    return 0;
}

// Gets temperature from the sensor
// Output: uint8_t temperature from sensor, 255 if error occured in temperature reading
uint16_t Sensor::getTemperature() {
    uint8_t retn;
    uint8_t temph = 255; // 255 means error
    uint8_t templ = 255; // 255 means error
    retn = i2c_read(i2c_dev, &temph, sizeof(temph), TEMP_SENSE_ADDRESS);
    if (retn || temph == 255) return 255;
    retn = i2c_read(i2c_dev, &templ, sizeof(templ), TEMP_SENSE_ADDRESS);
    if (retn || templ == 255) return 255;
    return (temph << 8) | templ ;
}