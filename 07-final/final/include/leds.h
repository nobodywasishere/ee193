#include <device.h>
#include <errno.h>
#include <sys/util.h>
#include <zephyr.h>
#include <drivers/gpio.h>

#define GPIO_A              "GPIOA"
#define GPIO_B              "GPIOB"
#define LED_GPIO_RED        10
#define LED_GPIO_GREEN      14
#define LED_GPIO_BLUE       9
#define LED_GPIO_STATUS     5

class LEDControl {

    public:
        LEDControl();
        void setLEDValues(bool red, bool green, bool blue, bool status);
        void setLEDColors(bool red, bool green, bool blue);
        void setLEDStatus(bool value);
        inline void turnLEDsOff() {setLEDValues(false,false,false,false);}
        inline void red()       {setLEDColors( true,false,false);}
        inline void green()     {setLEDColors(false, true,false);}
        inline void blue()      {setLEDColors(false,false, true);}
        inline void yellow()    {setLEDColors( true, true,false);}
        inline void magenta()   {setLEDColors( true,false, true);}
        inline void cyan()      {setLEDColors(false, true, true);}
        inline void white()     {setLEDColors( true, true, true);}
        inline void black()     {setLEDColors(false,false,false);}
        void debugColors();
    private:
        void writeLEDGPIO(const device* dev, int pinNumber, bool value);
        const device* dev_a;
        const device* dev_b;
};

// Aye Aye Sez Hi