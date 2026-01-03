#include "command_sender.h"

void CommandSender::begin(HardwareSerial* serial, long baudRate) {
  serialPort = serial;
  serialPort->begin(baudRate);
  responseBuffer.reserve(BUFFER_SIZE);
}

void CommandSender::sendCommand(const String& command) {
  serialPort->println(command);
}

bool CommandSender::hasResponse() {
  while (serialPort->available() > 0) {
    char c = serialPort->read();
    if (c == '\n') {
      return true;
    }
    if (c != '\r') {
      responseBuffer += c;
    }
  }
  return false;
}

String CommandSender::readResponse() {
  String response = responseBuffer;
  responseBuffer = "";
  return response;
}

String CommandSender::waitForResponse(unsigned long timeout) {
  unsigned long startTime = millis();
  while (millis() - startTime < timeout) {
    if (hasResponse()) {
      return readResponse();
    }
  }
  return "ERR:TIMEOUT";
}

// Movement commands
void CommandSender::moveForward(int speed) {
  sendCommand("MOVE:" + String(speed));
}

void CommandSender::moveReverse(int speed) {
  sendCommand("REVERSE:" + String(speed));
}

void CommandSender::stop() {
  sendCommand("STOP");
}

void CommandSender::turnLeft() {
  sendCommand("LEFT");
}

void CommandSender::turnRight() {
  sendCommand("RIGHT");
}

// LED commands
void CommandSender::setLedRed() {
  sendCommand("LED:RED");
}

void CommandSender::setLedGreen() {
  sendCommand("LED:GREEN");
}

void CommandSender::setLedBlue() {
  sendCommand("LED:BLUE");
}

void CommandSender::ledOff() {
  sendCommand("LED:OFF");
}

// Sensor commands
float CommandSender::getDistance() {
  sendCommand("DISTANCE");
  String response = waitForResponse();
  if (response.startsWith("DISTANCE:")) {
    return response.substring(9).toFloat();
  }
  return -1.0;  // Error or timeout
}

String CommandSender::getStatus() {
  sendCommand("STATUS");
  return waitForResponse();
}
