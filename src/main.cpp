#include <Doggy.hpp>

Doggy *robot;

void setup()
{
  robot = new Doggy();
  robot->communication->startWiFiConfig();
  // robot->communication->startWiFiAP();
  robot->communication->startServer();
  robot->log("Robot initialise");
}

void loop()
{
  // robot->light->blink();
}