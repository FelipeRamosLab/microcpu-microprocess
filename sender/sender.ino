#include <Lora32WifiBleV2.h>

Lora32WifiBleV2 loraBase;

void setup() {
  loraBase.init();
}

void loop() {
  Serial.println("Sending packet...");

  String toSend = "Hello, LoRa! Hello, LoRa!";
  // Send a packet
  LoRa.beginPacket();
  LoRa.print(toSend);
  LoRa.endPacket();

  Serial.println("Packet sent: " + toSend);

  loraBase.displayClear();
  loraBase.displayPrintString(toSend, 2, 2);
  loraBase.displayPrintString(toSend, 2, 14);
  loraBase.displayPrintString(toSend, 2, 26);
  loraBase.displayPrintString(toSend, 2, 38);
  loraBase.displayPrintString(toSend, 2, 50);
  loraBase.displayView();

  // Wait for a second before sending another packet
  delay(1000);
}
