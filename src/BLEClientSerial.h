#ifndef _BLE_CLIENT_SERIAL_H_
#define _BLE_CLIENT_SERIAL_H_
#include "sdkconfig.h"
#if defined(CONFIG_BLUEDROID_ENABLED)

#include "Arduino.h"
#include "Stream.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEAdvertisedDevice.h>
#include "BLEScanResultsSet.h"

typedef std::function<void(BLERemoteCharacteristic *pBLERemoteCharacteristic, const uint8_t *buffer, size_t size)>
BLESerialDataCb;
typedef std::function<void()> BLEConnectCb;
typedef std::function<void()> BLEDisconnectCb;
typedef std::function<void(BLEAdvertisedDevice *pAdvertisedDevice)> BLEAdvertisedDeviceCb;

/**
 * BLE Serial Client
 */
class BLEClientSerial : public Stream {
    String local_name;

    std::string buffer;

    BLEUUID serviceUUID;
    BLEUUID rxUUID;
    BLEUUID txUUID;

    BLEClient *pClient = nullptr;
    BLERemoteCharacteristic *pTxCharacteristic = nullptr;
    BLERemoteCharacteristic *pRxCharacteristic = nullptr;

    BLESerialDataCb pDataCb;
    BLEConnectCb pConnectCb;
    BLEDisconnectCb pDisconnectCb;

    void notifyCallback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length,
                        bool isNotify);

    friend class AdvertisedDeviceCallbacks;
    friend class ClientCallbacks;

public:
    BLEClientSerial();

    ~BLEClientSerial();

    explicit operator bool() const;

    bool begin(const String &localName = String(), const std::string &serviceUUID = "FFF0", const std::string &rxUUID = "FFF1",
               const std::string &txUUID = "FFF2");

    bool begin(unsigned long baud) {
        //compatibility
        return begin();
    }

    bool setPin(int pin);

    void registerSecurityCallbacks(BLESecurityCallbacks *cb);

    bool connect(const String &remoteName);

    bool connect(uint8_t remoteAddress[]);

    bool connect(BLEAddress &remoteAddress) {
        return connect(reinterpret_cast<uint8_t *>(remoteAddress.getNative()));
    }

    bool connected() const;

    bool disconnect();

    bool isClosed() const;

    int available();

    int peek();

    int read();

    size_t write(uint8_t c);

    size_t write(const uint8_t *buffer, size_t size);

    void flush();

    void end();

    void onData(const BLESerialDataCb &cb);

    void onConnect(const BLEConnectCb &cb);

    void onDisconnect(const BLEDisconnectCb &cb);

    BLEScanResultsSet *discover(int timeout = 30000);

    bool discoverAsync(const BLEAdvertisedDeviceCb &cb, int timeout = 30000);

    void discoverAsyncStop();

    void discoverClear();

    BLEScanResultsSet *getScanResults();

    const int INQ_TIME = 1349;
};

#endif
#endif
