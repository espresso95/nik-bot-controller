#ifndef COMMAND_SENDER_H
#define COMMAND_SENDER_H

#include <Arduino.h>
#include <HardwareSerial.h>

class CommandSender {
private:
  HardwareSerial* serialPort;
  String responseBuffer;
  static const int BUFFER_SIZE = 64;
  static const unsigned long DEFAULT_TIMEOUT = 1000;

public:
  void begin(HardwareSerial* serial, long baudRate = 9600);
  void sendCommand(const String& command);
  bool hasResponse();
  String readResponse();
  String waitForResponse(unsigned long timeout = DEFAULT_TIMEOUT);

  // Movement commands
  void moveForward(int speed);
  void moveReverse(int speed);
  void stop();
  void turnLeft();
  void turnRight();

  // LED commands
  void setLedRed();
  void setLedGreen();
  void setLedBlue();
  void ledOff();

  // Sensor commands
  float getDistance();
  String getStatus();
};

#endif
