#include <LoRa.h> // LoRa library
#include <SSD1306.h> // Display library
// #include <SPI.h>  // Responsible for the ser
#include <Wire.h>  //responsável pela comunicação i2c
#include <HardwareSerial.h> // Responsible for the TXRX serial communication

#define BAND 915E6 // Radio frequency, we also can use: 433E6, 868E6, 915E6
#define PABOOST true

const int RX_PIN = 3;
const int TX_PIN = 1;
int counter = 0;

// Display Pins (i2c)
const int DISPLAY_ADDRESS_PIN = 0x3c;
const int DISPLAY_SDA_PIN = 4;
const int DISPLAY_SCL_PIN = 15;
const int DISPLAY_RST_PIN = 16;

// LoRa Pins (spi)
const int LORA_SCK_PIN = 5;
const int LORA_MISO_PIN = 19;
const int LORA_MOSI_PIN = 27;
const int LORA_SS_PIN = 18;
const int LORA_RST_PIN = 15;
const int LORA_DI00_PIN = 26;

// Display Font Size
const int fontHeight = 10;

// The display object
SSD1306 display(DISPLAY_ADDRESS_PIN, DISPLAY_SDA_PIN, DISPLAY_SCL_PIN);
// Define your serial TXRX port instance
HardwareSerial RaspPi(1); // Use UART1

// Function to initialize the display
bool displayBegin() {
  // Reiniciamos o display
  pinMode(DISPLAY_RST_PIN, OUTPUT);
  digitalWrite(DISPLAY_RST_PIN, LOW);
  delay(1);
  digitalWrite(DISPLAY_RST_PIN, HIGH);
  delay(1);

  return display.init(); 
}

// Function to configure the display
void displayConfiguration() {
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 10, "Starting...");
  display.display();
}

// Starts the LoRa
bool startLora() {
  LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DI00_PIN);
  return LoRa.begin(BAND);
}

void displayClean() {
  display.clear();
  display.display();
}

void drawString(const char* toSend, int x = 10, int y = 10) {
  display.drawString(x, y, toSend);
}

void displayDrawString(const char* toSend, int x = 10, int y = 10) {
  drawString(toSend, x, y);
  display.display();
}

void startingRxTx() {
  // Initialize the custom serial port
  RaspPi.begin(9600, SERIAL_8N1, TX_PIN, RX_PIN); // Replace TX_PIN and RX_PIN with the actual pin numbers
}

void sendTX(const char* toSend) {
  RaspPi.println(toSend);
}

void getRX() {
  if (RaspPi.available()) {
    const String received = RaspPi.readStringUntil('\n'); // Read the incoming data until a newline character
    drawString("Received: ");
    displayDrawString(received.c_str());
  }
}

void setup() {
  // Starting serial monitor with 9600 (FOR DEVELOPMENT)
  Serial.begin(9600);
  // Testing serial monitor by printing "Starting..."
  Serial.println("Starting...");

  // Intializing the LoRa, if failed it will print on the serial monitor.
  if(!startLora()) {
    Serial.println("LoRa initialization failed!");
    while(1);
  }

  // Intializing the display, if failed, it will print to the monitor.
  if(!displayBegin()) {
    Serial.println("Display failed!");
    while(1);
  }

  // Configuring the display
  displayConfiguration();

  // Starting RX/TX
  startingRxTx();

  delay(2000);
}

void loop() {
  displayClean();
  
  // Listening for data coming on RX port
  getRX();

  counter++;
  sendTX("Testing");

  delay(100);
}
