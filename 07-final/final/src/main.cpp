
#include <zephyr.h>
#include <sys/printk.h>
#include <errno.h>
#include <sys/util.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>

#include "lora.h"
#include "sensor.h"
#include "sleep.h"
#include "leds.h"

Sensor sensor;
LEDControl leds;
Lora lora;

void main(void) {
    // int retn;
    sensor = Sensor();
    leds = LEDControl();
    lora = Lora();

    int len = 1;
    char msg[len] = {'0'};
    uint8_t temp = 0;
    
    if(sensor.deviceIsReady()) {
        while(true) {

            leds.black();
            
            temp = sensor.getTemperature() >> 8;
            printk("Locl T = %dºC\n", temp);

            leds.red();
            
            msg[0] = temp;
            lora.sendMessage(msg, len);

            leds.black();
            
            k_sleep(K_MSEC(1000));

            leds.blue();
            
            lora.recvMessage(msg, len);
            printk("Recv T = %dºC\n", msg[0]);
            
            leds.black();
            
            k_sleep(K_MSEC(1000));
        }
    }
}