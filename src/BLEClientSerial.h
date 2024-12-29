#ifndef _BLE_CLIENT_SERIAL_H_
#define _BLE_CLIENT_SERIAL_H_

#include "Arduino.h"
#include "Stream.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

class BLEClientSerial: public Stream
{
    public:

        BLEClientSerial(void);
        ~BLEClientSerial(void);

        bool begin(char* localName);
        int available(void);
        int peek(void);
        bool connected(void);
        bool connect(void);
        int read(void);
        size_t write(uint8_t c);
        size_t write(const uint8_t *buffer, size_t size);
        void flush();
        void end(void);

    private:
        BLERemoteCharacteristic* pTxCharacteristic;
        BLERemoteCharacteristic* pRxCharacteristic;
        String targetDeviceName;

        friend class MyClientCallback;
        friend class MySecurity;
        friend class MyAdvertisedDeviceCallbacks;

};

#endif