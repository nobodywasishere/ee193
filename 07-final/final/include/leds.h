//
// Tufts University - EE193 Embedded Systems
// Spring 2022
//
// @@@@@@@@@%  @@@@@              Adorable Aye-Ayes           *@@@@@  &@@@@@@@@@
// @@           @@@@  @@@                                 @@@  @@@@           @@
// @@                @@@ @@@                           @@@ @@@                @@
// @@                   @@ /@@       @@@@@@@         @@  @@                   @@
//  @@                    @@ @@@@@@@@@@@@@     @@@@@@@ @@                    @@
//   @@                    @@        @@   @           @@                    @@
//    @@                              @@                                  .@&
//      @@                                                              ,@@
//        @@@               @@@@@@@@           @@@@@@@@@              @@#
//           @@@@         @@@@@@@@@@@@        @@@@@@@@@@@         @@@
//                @@      @@@@@@@@@@/@       @@@@@@@@@@@@@     @@
//                 @@     @@@@@@@@@@@@        @@@@@@@@@@@     @@
//                  @@      @@@@@@@@            @@@@@@@@     @@
//                   @@               @@@@/@@@              @@
//                    @@/                @/               ,@@
//                      @@%             @@@             @@@
//                        .@@                         @@
//                            @@@                 @@@
//                                &@@@@@   @@@@@%
//
// leds.h
// May 4, 2022
//
// ©2022 Margret Riegert, Zev Pogrebin, Caleb Weinstein-Zenner, Lili Mooney
//
// Licensed under the Apache License, Version 2.0(the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

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