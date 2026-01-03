#include <Arduino.h>
#include "command_sender.h"

CommandSender sender;

// Use Serial2 for communication with robot on ESP32
// TX = GPIO17, RX = GPIO16 (default Serial2 pins)
HardwareSerial RobotSerial(2);

void setup() {
  // USB Serial for debugging
  Serial.begin(115200);
  Serial.println("Controller starting...");

  // Initialize communication with robot
  sender.begin(&RobotSerial, 9600);

  delay(2000);  // Wait for robot to initialize

  // Test communication
  Serial.println("Testing connection...");
  String status = sender.getStatus();
  Serial.println("Robot status: " + status);
}

void loop() {
  // Example: Remote control via USB Serial
  // Send commands from Serial Monitor to control the robot
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() > 0) {
      Serial.println("Sending: " + input);
      sender.sendCommand(input);

      // Wait for response
      String response = sender.waitForResponse();
      Serial.println("Response: " + response);
    }
  }

  // Check for any incoming responses from robot
  if (sender.hasResponse()) {
    String response = sender.readResponse();
    Serial.println("Robot: " + response);
  }
}