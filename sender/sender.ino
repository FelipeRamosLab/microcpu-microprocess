// ------------------------------
// SENDER
// --------------------------------

#include <SPI.h> // Serial communication
#include <LoRa.h>
#include <SSD1306.h>
#include <Wire.h>  // Communication i2c

#define BAND 915E6 // Radio frequency, also can be: 433E6, 868E6, 915E6
#define PABOOST true

// Display Pins (Communication i2c)
const int DISPLAY_ADDRESS_PIN = 0x3c;
const int DISPLAY_SDA_PIN = 4;
const int DISPLAY_SCL_PIN = 15;
const int DISPLAY_RST_PIN = 16;

// Pin configuration for LoRa32 WiFi BLE V2
const int CS_PIN = 18;    // LoRa radio chip select
const int RESET_PIN = 14; // LoRa radio reset
const int IRQ_PIN = 26;   // LoRa radio IRQ

// Display font pixels screen height
const int fontHeight = 10;

// Object of the display
SSD1306 display(DISPLAY_ADDRESS_PIN, DISPLAY_SDA_PIN, DISPLAY_SCL_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");

  // Set LoRa module pins
  LoRa.setPins(CS_PIN, RESET_PIN, IRQ_PIN);
  if (!LoRa.begin(BAND)) { // Set frequency to 915MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");

  // Intializing the display
  if(!displayBegin()) {
    Serial.println("Display failed!");
    while(1);
  }

  // Configuring the display
  displayConfiguration();

  display.drawString(10, 10, "Device Started!");
  display.display();
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

bool displayBegin() {
  // Reiniciamos o display
  pinMode(DISPLAY_RST_PIN, OUTPUT);
  digitalWrite(DISPLAY_RST_PIN, LOW);
  delay(1);
  digitalWrite(DISPLAY_RST_PIN, HIGH);
  delay(1);

  return display.init(); 
}

void displayConfiguration() {
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 10, "Starting...");
  display.display();
}
