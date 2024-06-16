#include <Lora32WifiBleV2.h>
#include <JoystickXY.h>
#include <SPI.h>
#include <LoRa.h>

// Pin configuration for LoRa32 WiFi BLE V2
const int csPin = 18;    // LoRa radio chip select
const int resetPin = 14; // LoRa radio reset
const int irqPin = 26;   // LoRa radio IRQ

JoystickXY joystick;
Lora32WifiBleV2 lora32;

void setup() {
  lora32.init();
  joystick.init();
}

void loop() {
  JoystickXYResponse data = joystick.read();
  int rawXValue = data.x;
  int rawYValue = data.y;
  int buttonState = data.buttonState;

  lora32.displayStartString("Analog Joystick:");
  lora32.displayBreakLine("X: " + String(rawXValue));
  lora32.displayBreakLine("Y: " + String(rawYValue));
  lora32.displayBreakLine("Button: " + String(buttonState == LOW ? "Pressed" : "Released"));
  lora32.displayEndString();

  lora32.sendStringPacket("X: " + String(rawXValue) + " | " + "Y: " + String(rawYValue));
  // Wait for a second before sending another packet
  delay(10);
}
