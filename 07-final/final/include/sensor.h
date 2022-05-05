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
// sensor.h
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