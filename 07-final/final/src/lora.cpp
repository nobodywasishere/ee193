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