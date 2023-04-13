#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

class Communication
{
private:
    WiFiManager wifimanager;
    UDP udp;
public:
    Communication();
    void startWiFiConfig();
    void startWiFiAP();
    void startServer();
    int isMessage();
    ESP8266WebServer server;
};

Communication::Communication()
{
}

void Communication::startWiFiAP()
{
    Serial.println();
    Serial.print("Configuring access point...");
    WiFi.softAP("Doggy", "Doggy");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
}

void Communication::startWiFiConfig()
{
    wifimanager.autoConnect("Doggy");
}

void Communication::startServer()
{
    // server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started");
}

int Communication::isMessage(){
if(udp.available()){
    return true;
}
}