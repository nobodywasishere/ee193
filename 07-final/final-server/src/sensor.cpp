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
// seonsor.cpp
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

#include "sensor.h"

Sensor::Sensor() {
    initDevice();
}

// Builds the Sensor 
int Sensor::initDevice() {
    i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c2));
    return 0;
}

// Configures the Temperature Sensor Device
// Output: int, 0 if no error, 1 if error occured
int Sensor::configureDevice() {
    int deviceErr = 0;
    cfg = I2C_SPEED_SET(I2C_SPEED_FAST) | I2C_MODE_MASTER;
    if(!i2c_dev) deviceErr += 1; // no device found
    else if(i2c_configure(i2c_dev, cfg) != 0) deviceErr += 2; // can't config device
    // else if(sendOpcode(0,0,1)) deviceErr += 4;
    if (deviceErr==0) {
        printk("Sensor Initialized!\n");
        if(deviceIsReady()) printk("Sensor Ready!\n");
    } else {
        printk("Sensor Error %d!\n", deviceErr);
    }
    return 0;

}

// Gets temperature from the sensor
// Output: uint8_t temperature from sensor, 255 if error occured in temperature reading
uint16_t Sensor::getTemperature(int resolution) {
    sendOpcode(1,resolution,1);
    k_sleep(K_MSEC(100));
    uint8_t retn = 0;
    uint8_t temp[2] = {255, 255}; // 255 means error
    uint8_t tp = 255;
    uint8_t wr = TEMP_PTR;
    // retn += i2c_write(i2c_dev, &tp, sizeof(tp), TEMP_SENSE_ADDRESS);
    // retn += i2c_read(i2c_dev, temp, sizeof(temp), TEMP_SENSE_ADDRESS);
    retn += i2c_write_read(
        i2c_dev, TEMP_SENSE_ADDRESS, 
        &wr, sizeof(wr), 
        temp, sizeof(temp));
    if (retn || temp[0] == 255 || temp[1] == 255) return 255;
    return (temp[0] << 8) | temp[1];
}

int Sensor::sendOpcode(uint8_t opcode) {
    int retn = 0;
    uint8_t conf[2] = {CONF_PTR, opcode};
    retn += i2c_write(i2c_dev, conf, sizeof(conf), TEMP_SENSE_ADDRESS);
    // i2c_write_read
    // retn += i2c_write(i2c_dev, &opcode, sizeof(opcode), TEMP_SENSE_ADDRESS);
    if (retn) {
        printk("Temp read err: %d\n", retn);
    }
    // uint8_t tp = TEMP_PTR;
    // retn += i2c_write(i2c_dev, &tp, sizeof(tp), TEMP_SENSE_ADDRESS);
    return retn;
}

int Sensor::sendOpcode(int oneShot, int resolution, int shutdown) {
    uint8_t data = oneShot << 7 | resolution << 5 | shutdown;
    return sendOpcode(data);
}