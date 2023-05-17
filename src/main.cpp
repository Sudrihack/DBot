#include <DBot.hpp>

DBot *robot;

void setup()
{
  robot = new DBot();
  robot->light->blink(4, 2000);
  robot->log("Robot initialise");
  robot->log("UID: ");
  robot->log(robot->communication->getID());
  robot->communication->setPin("0001");
  robot->communication->setName("DBot");
  // robot->communication->startBluetooth();
  robot->communication->startWifiManager();
  robot->communication->startUDPServer(80);
}

void loop()
{
  if (robot->communication->bluetoothAvailable())
  {
    robot->log("New message via Bluetooth");
    robot->log(robot->communication->getBluetoothData());
    robot->communication->bluetoothSend("Message recu 5 sur 5 mon géneral!");
  }
}
