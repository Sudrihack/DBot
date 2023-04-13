#include <Arduino.h>

class Light
{
private:
public:
    Light();
    void blink();
};

Light::Light()
{
}

void Light::blink()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    // avoid usage of delays fonctions ...
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
}
