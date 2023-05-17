#include <DBot.hpp>

DBot *robot;

void setup()
{
  robot = new DBot();
  robot->light->blink(4, 2000);
  robot->log("Robot initialise");
  robot->log("UID: ");
  robot->log(robot->communication->getID());
  robot->communication->setPin("azertyuiop");
  robot->communication->setName("DBot");
  robot->communication->startBluetooth();
  robot->communication->startWifiManager();
  robot->communication->startUDPServer(80);
}

void loop()
{
  if (robot->communication->bluetoothAvailable())
  {
    robot->log("New message via Bluetooth");
    robot->log("Data: ");
    robot->log(robot->communication->getBluetoothData());
  }
  
  if (robot->communication->UDPAvailable())
  {
    robot->log("New message via UDP");
    robot->log("Data: ");
    robot->log(robot->communication->getLastUDPPacket().data);
    robot->log("From IP: ");
    robot->log(robot->communication->getLastUDPPacket().fromIP);
  }
}
