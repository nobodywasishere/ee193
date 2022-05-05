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
// lora.cpp
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

#include "lora.h"

#define DEFAULT_RADIO_NODE DT_ALIAS(lora0)
BUILD_ASSERT(DT_NODE_HAS_STATUS(DEFAULT_RADIO_NODE, okay),
             "No default LoRa radio specified in DT");

Lora::Lora() {
    Lora::lora_dev = DEVICE_DT_GET(DEFAULT_RADIO_NODE);

    if (!device_is_ready(lora_dev)) {
        printk("%s Device not ready", lora_dev->name);
        return;
    }

    initLora();
}

int Lora::initLora() {
    Lora::config.frequency = 865100000;
    Lora::config.bandwidth = BW_125_KHZ;
    Lora::config.datarate = SF_10;
    Lora::config.preamble_len = 8;
    Lora::config.coding_rate = CR_4_5;
    Lora::config.tx_power = 4;
    Lora::config.tx = true;
    // return 0;
    return lora_config(lora_dev, &config);
}

int Lora::sendMessage(char *msg, int len) {
    return lora_send(lora_dev, (uint8_t *) msg, len);
}

int Lora::recvMessage(char *msg, int len) {
    return lora_recv(lora_dev, (uint8_t *)msg, len, K_FOREVER,
                     &rssi, &snr);
}