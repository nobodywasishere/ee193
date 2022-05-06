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
// main.cpp
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
    sensor.configureDevice();
    leds = LEDControl();
    lora = Lora();

    int len = 1;
    char msg[len] = {'0'};
    uint8_t temp = 0;
    
    if(sensor.deviceIsReady()) {
        while(true) {

            leds.black();
            
            temp = sensor.getTemperature() >> 8;
            printk("0 %d\n", temp);

            leds.red();
            
            msg[0] = temp;
            lora.sendMessage(msg, len);

            leds.black();
            
            k_sleep(K_MSEC(1000));

            leds.blue();
            
            lora.recvMessage(msg, len);
            // printk("Recv T = %dºC\n", msg[0]);
            
            leds.black();
            
            k_sleep(K_MSEC(1000));
        }
    }
}