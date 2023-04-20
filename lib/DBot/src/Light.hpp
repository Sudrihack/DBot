#include <Arduino.h>

class Light
{
private:
public:
    void blink(int pin, int time);
    void up(int pin);
    void up(int pin, int percentage);
    void down(int pin);
};

void Light::blink(int pin, int time)
{

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    digitalWrite(pin, HIGH);
    // avoid usage of delays fonctions ...
    delay(time);
    digitalWrite(pin, LOW);
}

void Light::up(int pin, int percentage)
{
    int value = map(percentage, 0, 100, 0, 255);
    pinMode(pin, OUTPUT);
    analogWrite(pin, value);
}

void Light::up(int pin)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
}

void Light::down(int pin)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}