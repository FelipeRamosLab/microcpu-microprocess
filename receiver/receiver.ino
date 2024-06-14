// ------------------------------
// RECEIVER
// --------------------------------

#include <SPI.h>
#include <LoRa.h>

// Pin configuration for LoRa32 WiFi BLE V2
const int csPin = 18;    // LoRa radio chip select
const int resetPin = 14; // LoRa radio reset
const int irqPin = 26;   // LoRa radio IRQ

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  // Set LoRa module pins
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(915E6)) { // Set frequency to 915MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // Try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Received a packet
    Serial.print("Received packet: ");

    // Read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    Serial.println("");
  }

  delay(10);
}
