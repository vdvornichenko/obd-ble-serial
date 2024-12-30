**Serial interface for ELMduino using BLE**

ELMduino uses two ways of serial communication with ELM327 dongles - WiFi and Bluetooth classic. 
Modern ESP32 devices do not support Bluetooth Classic, but they do support the BLE, so ESP32-C3, S3, C6 and other ESP32-based devices cannot be used with ELM327 OBD dongles which are compatible with iPhones (BLE 4.0 and up). 

Here's the solution to have an OBD ELM327 dongle which is compatible with iPhone and that still could be used with your ESP32-based screen.

Current project just wraps the Serial communication with OBD dongle via BLE 4.0 protocol, the wrapper inherits and uses all the Serial methods so it could be used in ELMduino instead of BluetoothSerial or WiFi connection.

Usage
Instead of  (for example) using of Bluetooth serial in ELMduino samples

    BluetoothSerial SerialBT;

you can just pass the instance of  BLEClientSerial to myELM327 functions and it will work in the same way.

    #include <BLEClientSerial.h>
    BLEClientSerial BLESerial;
    #define ELM_PORT   BLESerial
    ELM327 myELM327;
    ELM_PORT.begin("OBDLink CX");
    ...
      if (!ELM_PORT.connect())
    ... 
      if (!myELM327.begin(ELM_PORT, true, 2000))
    ... 

If your BLE adaptor does not work, you may check with nRF connect app, what are the characteristics for *Write* and *Notify* and change such UUIDs in BLEClientSerial.cpp,
for OBDLink CX (and a lot of other OBD adaptors from China) there will be the following settings:

    BLEUUID  serviceUUID_FFF0("FFF0");
    BLEUUID  rxUUID("FFF1");//Notify characteristic
    BLEUUID  txUUID("FFF2");//Write characteristic

Some references regarding chars and services of OBD dongles:
https://stackoverflow.com/questions/61090365/what-ble-characteristic-should-i-use-in-a-ble-ios-device-for-obdii
https://stackoverflow.com/questions/52075456/which-gatt-profile-and-services-are-used-by-obd-ble-adapters-like-lelink-automa
