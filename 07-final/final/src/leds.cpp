#include "leds.h"

LEDControl::LEDControl() {
    dev_a = device_get_binding(GPIO_A);
    dev_b = device_get_binding(GPIO_B);
    int ret = 0;
    ret += gpio_pin_configure(dev_a, LED_GPIO_RED, GPIO_OUTPUT_HIGH);
    ret += gpio_pin_configure(dev_b, LED_GPIO_GREEN, GPIO_OUTPUT_HIGH);
    ret += gpio_pin_configure(dev_b, LED_GPIO_BLUE, GPIO_OUTPUT_HIGH);
    ret += gpio_pin_configure(dev_b, LED_GPIO_STATUS, GPIO_OUTPUT_HIGH);
    if(ret) printk("An error occured while attempting to initialize LEDs\n");
}

void LEDControl::setLEDValues(bool red, bool green, bool blue, bool status) {
    setLEDColors(red,green,blue);
    setLEDStatus(status);
}

void LEDControl::setLEDColors(bool red, bool green, bool blue)
{
    writeLEDGPIO(dev_a, LED_GPIO_RED, red);
    writeLEDGPIO(dev_b, LED_GPIO_GREEN, green);
    writeLEDGPIO(dev_b, LED_GPIO_BLUE, blue);
}

void LEDControl::setLEDStatus(bool value)
{
    writeLEDGPIO(dev_b, LED_GPIO_STATUS, value);
}

void LEDControl::writeLEDGPIO(const device* dev, int pinNumber, bool value) {
    if(value) gpio_pin_set(dev, pinNumber, 0);
    else      gpio_pin_set(dev, pinNumber, 1);
}

void LEDControl::debugColors() {
    red();
    printk("color red\n");
    k_sleep(K_MSEC(1000));
    green();
    printk("color green\n");
    k_sleep(K_MSEC(1000));
    blue();
    printk("color blue\n");
    k_sleep(K_MSEC(1000));
    cyan();
    printk("color cyan\n");
    k_sleep(K_MSEC(1000));
    yellow();
    printk("color yellow\n");
    k_sleep(K_MSEC(1000));
    magenta();
    printk("color magenta\n");
    k_sleep(K_MSEC(1000));
    white();
    printk("color white\n");
    k_sleep(K_MSEC(1000));
    black();
    printk("color black\n");
    k_sleep(K_MSEC(1000));
}