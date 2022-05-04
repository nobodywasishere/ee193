
#include <zephyr.h>
#include <sys/printk.h>
#include <errno.h>
#include <sys/util.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>

#include "lora.h"
#include "sensor.h"
#include "sleep.h"

Sensor sensor;
Lora lora;

void main(void) {
    // int retn;
    sensor = Sensor();
    lora = Lora();

    int len = 1;
    char msg[len] = {'0'};
    uint8_t temp = 0;
    
    if(sensor.deviceIsReady()) {
        while(true) {
            temp = sensor.getTemperature() >> 8;
            printk("Locl T = %dºC\n", temp);
            msg[0] = temp;
            lora.sendMessage(msg, len);
            k_sleep(K_MSEC(1000));
            lora.recvMessage(msg, len);
            printk("Recv T = %dºC\n", msg[0]);
            k_sleep(K_MSEC(1000));
        }
    }
}