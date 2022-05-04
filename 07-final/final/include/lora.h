// lora.h

#include <device.h>
#include <drivers/lora.h>
#include <errno.h>
#include <sys/util.h>
#include <zephyr.h>

#pragma once

class Lora {
    private:
        const struct device *lora_dev;
        struct lora_modem_config config;

        int16_t rssi;
        int8_t snr;

    public:
        Lora();
        int initLora();
        int sendMessage(char *msg, int len);
        int recvMessage(char *msg, int len);
};
