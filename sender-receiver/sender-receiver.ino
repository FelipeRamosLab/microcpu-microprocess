#include <Lora32WifiBleV2.h>

Lora32WifiBleV2 lora32;

const String INSTANCE_TYPE = "RECEIVER";
int counter = 0;

void setup() {
  lora32.init();
}

void loop() {
  if (INSTANCE_TYPE == "RECEIVER") {
    String received = lora32.readString();
    if (received != "") {
      // Printing to display
      lora32.displayStartString(INSTANCE_TYPE + ":");
      lora32.displayBreakLine("We received:");
      lora32.displayBreakLine(received);
      lora32.displayEndString();
    }
  }
  
  if (INSTANCE_TYPE == "SENDER") {
    // Send a packet
    String toSend = "Hi, I'm " + INSTANCE_TYPE + " " + String(counter);
    lora32.sendStringPacket(toSend);

    lora32.displayStartString(INSTANCE_TYPE + ":");
    lora32.displayBreakLine("We are sending:");
    lora32.displayBreakLine(toSend);
    lora32.displayEndString();

    counter++;
  }

  // Wait for a second before sending another packet
  delay(10);
}
