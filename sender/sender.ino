#include <Lora32WifiBleV2.h>

Lora32WifiBleV2 loraBase;

void setup() {
  loraBase.init();
}

void loop() {
  // Send a packet
  String toSend = "Hello, LoRa!";
  loraBase.sendStringPacket(toSend);
 
  // Printing to display
  loraBase.displayStartString("This is the first.");
  loraBase.displayBreakLine("This is the second.");
  loraBase.displayBreakLine("And sending:");
  loraBase.displayBreakLine(toSend);
  loraBase.displayEndString();

  // Wait for a second before sending another packet
  delay(1000);
}
