#include <DBot.hpp>

DBot *robot;

void setup()
{
  robot = new DBot();
  robot->communication->setPin("0001");
  robot->communication->startBluetooth();
  // robot->communication->startWifiManager();
  // robot->communication->startUDPServer(80);
  robot->light->blink(12, 200);
  robot->log("Robot initialise");
}

void loop()
{
  if (robot->communication->bluetoothAvailable())
  {
    robot->light->up(12, 50);
    robot->log("New message via Bluetooth");
    robot->communication->bluetoothSend("Message recu 5 sur 5 mon géneral!");
  }
}
