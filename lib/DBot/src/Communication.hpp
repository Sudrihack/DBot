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

class Communication
{
private:
    String deviceName = "DBot";
    String devicePin = "";
    WiFiManager wifiManager;
    AsyncUDP udp;
    UDPPacket lastUDPPacket;
    BluetoothSerial bluetooth;

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
    int getID();
    void setName(String name);
    void setPin(String pin);
};

Communication::Communication()
{
    setName("DBot-" + (String)getID());
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

void Communication::startBluetooth()
{
    bluetooth.begin(deviceName);
    if (devicePin.length() > 0)
    {
        bluetooth.setPin(devicePin.c_str());
    }
    Serial.printf("Bluetooth started with name:  \"%s\"", deviceName.c_str());
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