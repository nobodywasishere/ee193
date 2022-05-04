#include <device.h>
#include <errno.h>
#include <sys/util.h>
#include <zephyr.h>
#include <drivers/gpio.h>

#define LED_GPIO_RED        
#define LED_GPIO_GREEN      
#define LED_GPIO_BLUE       
#define LED_GPIO_STATUS   

class LEDControl {

    public:
        void setLEDValues(bool red, bool green, bool blue, bool status);
        void setLEDColors(bool red, bool green, bool blue);
        void setLEDStatus(bool value);
        inline void turnLEDsOff() {setLEDValues(false,false,false,false);}
        inline void red()       {setLEDColors(true,false,false);}
        inline void green()     {setLEDColors(false,true,false);}
        inline void blue()      {setLEDColors(false,false,true);}
        inline void yellow()    {setLEDColors(true,true,false);}
        inline void magenta()   {setLEDColors(true,false,true);}
        inline void cyan()      {setLEDColors(true,true,false);}
        inline void white()     {setLEDColors(true,true,true);}
        inline void black()     {setLEDColors(false,false,false);}
    private:
};