#include <BluetoothSerial.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include <AsyncUDP.h>

struct UDPPacket
{
    uint fromIP;
    uint fromPort;
    uint toIP;
    uint toPort;
    uint length;
    bool isBroadcast;
    bool isMulticast;
    String data;
};

struct BluetoothPacket
{
    uint length;
    String data;
};

class Communication
{
private:
    String deviceName;
    String devicePin;
    WiFiManager wifiManager;
    AsyncUDP udp;
    UDPPacket lastUDPPacket;
    BluetoothPacket lastBluetoothPacket;
    BluetoothSerial bluetooth;
    void onBluetoothDataReceived();

public:
    Communication();
    void startBluetooth();
    void startWifiManager();
    void startUDPServer(int port);
    int UDPAvailable();
    UDPPacket getLastUDPPacket();
    int bluetoothAvailable();
    void bluetoothSend(String message);
    String getBluetoothData();
    String getLastBluetoothPacket();
    int getID();
    void setName(String name);
    void setPin(String pin);
};

Communication::Communication()
{
    setName("DBot-" + (String)getID());
    setName("password" + (String)getID());
}

void Communication::setName(String name)
{
    this->deviceName = name;
}

void Communication::setPin(String pin)
{
    this->devicePin = pin;
}

int Communication::getID()
{
    return (uint16_t)ESP.getEfuseMac();
}

void Communication::onBluetoothDataReceived()
{
    String stringData = bluetooth.readString();
    lastBluetoothPacket = {
        stringData.length(),
        stringData};
}

void Communication::startBluetooth()
{
    bluetooth.begin(deviceName);
    if (devicePin.length() > 0)
    {
        bluetooth.setPin(devicePin.c_str());
    }
    Serial.printf("Bluetooth started with name:  \"%s\"", deviceName.c_str());
    // bluetooth.register_callback(onBluetoothDataReceived);
    bluetooth.onData(onBluetoothDataReceived);
}

String Communication::getBluetoothData()
{
    return bluetooth.readString();
}

void Communication::startWifiManager()
{
    wifiManager.setConfigPortalTimeout(180);
    if (devicePin.length() > 0)
    {
        wifiManager.autoConnect((const char *)deviceName.c_str(), (const char *)devicePin.c_str());
    }
    else
    {
        wifiManager.autoConnect((const char *)deviceName.c_str());
    }
}

void Communication::startUDPServer(int port)
{
    if (udp.listen(port))
    {
        udp.onPacket([&](AsyncUDPPacket packet)
                     {
            String stringData = (char *)packet.data();
            lastUDPPacket = {
                packet.remoteIP(),
                packet.remotePort(),
                packet.localIP(),
                packet.localPort(),
                packet.length(),
                packet.isBroadcast(),
                packet.isMulticast(),
                stringData
            }; });
    }
}

int Communication::UDPAvailable()
{
    return lastUDPPacket.length > 0;
}

UDPPacket Communication::getLastUDPPacket()
{
    UDPPacket packet = lastUDPPacket;
    lastUDPPacket.length = 0;
    return packet;
}

int Communication::bluetoothAvailable()
{
    return bluetooth.available();
}

void Communication::bluetoothSend(String message)
{
    bluetooth.print(message);
}