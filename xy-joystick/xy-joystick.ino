#include <Lora32WifiBleV2.h>
#include <JoystickXY.h>

JoystickXY joystick;
Lora32WifiBleV2 lora32;

void setup() {
  Serial.begin(1000000, SERIAL_8N1, 3, 1);

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

  // Building the querystring
  String dataToSend = "/drive?x=" + String(rawXValue) + "&y=" + String(rawYValue);
  // Sending via serial RX TX
  Serial.println(dataToSend);

  lora32.sendStringPacket(dataToSend);
  // Wait for a second before sending another packet
  delay(15);
}
