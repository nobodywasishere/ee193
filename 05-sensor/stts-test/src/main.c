
#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/i2c.h>

#define TEMP_I2C_ADDR 0x48 // Trial and error, doesn't match documentation

uint32_t cfg = I2C_SPEED_SET(I2C_SPEED_FAST) | I2C_MODE_MASTER;

const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c2));

void main(void)
{
    if (!i2c_dev)
    {
        printk("I2C: Device not found.\n");
        return;
    }

    if (i2c_configure(i2c_dev, cfg) != 0)
    {
        printk("Error on i2c_configure()\n");
        return;
    }
    else
    {
        printk("I2C device configured successfully!\n");
    }

    if (!device_is_ready(i2c_dev))
    {
        printk("I2C: Device is not ready.\n");
        return;
    }

    uint8_t temp = 0;
    uint8_t retn = 0;
    uint8_t address = 0;

    while (true) {
        temp = 255;
        retn = i2c_read(i2c_dev, &temp, sizeof(temp), TEMP_I2C_ADDR);
        if (retn) {
            printk("Failed reading the temp! %d\n", retn);
        } else if (temp != 255) {
            printk("%u*C\n", temp);
        }
        k_sleep(K_MSEC(500));
    }

    // for (address = 1; address < 127; address++)
    // {
    //     temp = 255;
    //     retn = i2c_read(i2c_dev, &temp, sizeof(temp), address);
    //     if (retn)
    //     {
    //         // printk("No device on addr %u\n", address);
    //     }
    //     else
    //     {
    //         printk("Device on addr %u\n", address);
    //     }
    //     // else if (temp != 255) {
    //     //     printk("%u*C\n", temp);
    //     // }
    //     k_sleep(K_MSEC(50));
    // }
    // printk("Done search!\n");

    return;
}
