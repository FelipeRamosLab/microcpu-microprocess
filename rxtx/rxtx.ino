#define TX_PIN 17
#define RX_PIN 16

void setup() {
  Serial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN); // Start UART communication with LoRa32 module (hardware UART)
}

void loop() {
  // Example data to transmit
  String dataToSend = "Hello, Raspberry Pi!";

  // Transmit data over UART to Raspberry Pi via LoRa32's TX pin (usually connected to Raspberry Pi's RX GPIO pin)
  Serial.println(dataToSend);

  // Receiving data
  String received = Serial.readString();

  delay(1000); // Adjust delay based on your application
}
