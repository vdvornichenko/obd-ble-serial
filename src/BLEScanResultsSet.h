#ifndef BLESCANRESULTSSET_H
#define BLESCANRESULTSSET_H

#include "sdkconfig.h"
#if defined(CONFIG_BLUEDROID_ENABLED)

#include "Stream.h"
#include <BLEAdvertisedDevice.h>

class BLEScanResultsSet {
    std::map<std::string, BLEAdvertisedDevice> m_vectorAdvertisedDevices;

public:
    void dump(Print *print = nullptr);

    int getCount();

    BLEAdvertisedDevice *getDevice(int i);

    bool add(BLEAdvertisedDevice advertisedDevice, bool unique = true);

    void clear();
};

#endif
#endif
