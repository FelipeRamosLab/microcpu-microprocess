// ------------------------------
// SENDER
// --------------------------------

#include <SPI.h>
#include <LoRa.h>

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
}

void loop() {
  Serial.println("Sending packet...");

  // Send a packet
  LoRa.beginPacket();
  LoRa.print("Hello, LoRa!");
  LoRa.endPacket();

  Serial.println("Packet sent!");

  // Wait for a second before sending another packet
  delay(1000);
}
