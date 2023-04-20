#include <Arduino.h>
#include <Move.hpp>
#include <Communication.hpp>
#include <Light.hpp>

class DBot
{
private:
public:
    DBot();
    Light *light;
    Move *move;
    Communication *communication;
    void log(String message);
};

DBot::DBot()
{
    Serial.begin(9600);
}

void DBot::log(String message)
{
    Serial.println(message);
}