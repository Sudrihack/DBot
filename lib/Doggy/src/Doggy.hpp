#include <Arduino.h>
#include <Move.hpp>
#include <Communication.hpp>
#include <Light.hpp>

class Doggy
{
private:
public:
    Doggy();
    Light *light;
    Move *move;
    Communication *communication;
    void log(char *message);
};

Doggy::Doggy()
{
    Serial.begin(9600);
}

void Doggy::log(char *message)
{
    Serial.println(message);
}