#include "BLEScanResultsSet.h"

#include "esp32-hal-log.h"

void BLEScanResultsSet::dump(Print *print) {
    int cnt = getCount();
    if (print == nullptr) {
        log_v(">> Dump scan results : %d", cnt);
        for (int i = 0; i < cnt; i++) {
            BLEAdvertisedDevice *dev = getDevice(i);
            if (dev) {
                log_d("- %d: %s\n", i + 1, dev->toString().c_str());
            } else {
                log_d("- %d is null\n", i + 1);
            }
        }
        log_v("-- dump finished --");
    } else {
        print->printf(">> Dump scan results: %d\n", cnt);
        for (int i = 0; i < cnt; i++) {
            BLEAdvertisedDevice *dev = getDevice(i);
            if (dev) {
                print->printf("- %d: %s\n", i + 1, dev->toString().c_str());
            } else {
                print->printf("- %d is null\n", i + 1);
            }
        }
        print->println("-- Dump finished --");
    }
}

int BLEScanResultsSet::getCount() {
    return m_vectorAdvertisedDevices.size();
}

BLEAdvertisedDevice *BLEScanResultsSet::getDevice(int i) {
    if (i < 0) {
        return nullptr;
    }

    int x = 0;
    BLEAdvertisedDevice *pDev = &m_vectorAdvertisedDevices.begin()->second;
    for (auto it = m_vectorAdvertisedDevices.begin(); it != m_vectorAdvertisedDevices.end(); ++it) {
        pDev = &it->second;
        if (x == i) {
            break;
        }
        x++;
    }
    return x == i ? pDev : nullptr;
}

bool BLEScanResultsSet::add(BLEAdvertisedDevice advertisedDevice, bool unique) {
    std::string key = std::string(advertisedDevice.getAddress().toString().c_str(),
                                  advertisedDevice.getAddress().toString().length());

    if (!unique || m_vectorAdvertisedDevices.count(key) == 0) {
        m_vectorAdvertisedDevices.insert(std::pair<std::string, BLEAdvertisedDevice>(key, advertisedDevice));
        return true;
    }

    return false;
}

void BLEScanResultsSet::clear() {
    m_vectorAdvertisedDevices.clear();
}
