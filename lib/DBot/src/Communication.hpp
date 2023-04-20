#include <BluetoothSerial.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include "AsyncUDP.h"
#include <string>
#include <vector>

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
// class pour 
class Communication
{
private:
    String deviceName = "DBot";
    String devicePin = "";
    WiFiManager wifiManager;
    AsyncUDP udp;
    UDPPacket lastUDPPacket;
    String lastUDPPacketData;

public:
    BluetoothSerial bluetooth;
    Communication();
    void startBluetooth();
    void startWifiManager();
    void startUDPServer(int port, void (*callback)(AsyncUDPPacket packet));
    void startUDPServer(int port);
    void setLastUDPPacket(AsyncUDPPacket packet);
    UDPPacket getLastUDPPacket();
    int getID();
    void setName(String name);
    void setPin(String pin);
    int bluetoothAvailable();
    void bluetoothSend(String message);
};

Communication::Communication()
{
    setName("DBot-" + getID());
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
    uint32_t id = 0;
    for (int i = 0; i < 17; i = i + 8)
    {
        id |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    return id;
}

void Communication::startBluetooth()
{
    bluetooth.begin(deviceName);
    if (devicePin.length() > 0)
    {
        bluetooth.setPin(devicePin.c_str());
    }
    Serial.printf("The device with name \"%s\" is started.\n", deviceName.c_str());
}

void Communication::startWifiManager()
{
    wifiManager.setConfigPortalTimeout(180);
    wifiManager.autoConnect(deviceName.c_str(), devicePin.c_str());
}

void Communication::startUDPServer(int port, void (*callback)(AsyncUDPPacket packet))
{
    udp.listen(port);
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
}

void Communication::startUDPServer(int port)
{
    if (udp.listen(port))
    {
        udp.onPacket([&](AsyncUDPPacket packet)
                     {
            Serial.print("Data: ");
            Serial.write(packet.data(), packet.length());
            setLastUDPPacket(packet);
            Serial.println(); });
    }
}

void Communication::setLastUDPPacket(AsyncUDPPacket packet)
{
    String stringData = (const char *)packet.data();
    lastUDPPacket = {
        packet.remoteIP(),
        packet.remotePort(),
        packet.localIP(),
        packet.localPort(),
        packet.length(),
        packet.isBroadcast(),
        packet.isMulticast(),
        stringData};
}

UDPPacket Communication::getLastUDPPacket()
{
    return lastUDPPacket;
}

int Communication::bluetoothAvailable()
{
    return bluetooth.available();
}

void Communication::bluetoothSend(String message)
{
    bluetooth.print(message);
}