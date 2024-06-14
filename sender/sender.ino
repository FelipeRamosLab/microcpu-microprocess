// ------------------------------
// SENDER
// --------------------------------

#include <SPI.h>
#include <LoRa.h>

#define VRX_PIN 36  // Define the pin for the VRX (X-axis)
#define VRY_PIN 37  // Define the pin for the VRY (Y-axis)
#define SW_PIN 25   // Define the pin for the SW (button)

// Pin configuration for LoRa32 WiFi BLE V2
const int csPin = 18;    // LoRa radio chip select
const int resetPin = 14; // LoRa radio reset
const int irqPin = 26;   // LoRa radio IRQ

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");

  // Set LoRa module pins
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(915E6)) { // Set frequency to 915MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");

  pinMode(VRX_PIN, INPUT); // Set the VRX pin as an input
  pinMode(VRY_PIN, INPUT); // Set the VRY pin as an input
  pinMode(SW_PIN, INPUT_PULLUP); // Set the SW pin as an input with a pull-up resistor
}

void loop() {
  int rawXValue = analogRead(VRX_PIN); // Read the raw X-axis value
  int rawYValue = analogRead(VRY_PIN); // Read the raw Y-axis value
  int buttonState = digitalRead(SW_PIN); // Read the button state

  // // Send a packet
  LoRa.beginPacket();
  LoRa.print("X:");
  LoRa.print(rawXValue);
  LoRa.print("Y:");
  LoRa.print(rawYValue);
  LoRa.endPacket();

  Serial.print("X: ");
  Serial.print(rawXValue);
  Serial.print(" | Y: ");
  Serial.print(rawYValue);
  Serial.print(" | Button: ");
  Serial.println(buttonState == LOW ? "Pressed" : "Released");

  // Wait for a second before sending another packet
  delay(10);
}
