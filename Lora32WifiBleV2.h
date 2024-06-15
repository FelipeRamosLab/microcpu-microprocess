// Lora32WifiBleV2.h
#ifndef LORA32WIFIBLEV2_H
#define LORA32WIFIBLEV2_H

#include <SPI.h> // Serial communication
#include <LoRa.h>
#include <SSD1306.h>
#include <Wire.h> // Communication i2c
#include <string>

/**
 * @brief Class representing the Lora32 WiFi BLE V2 module with display functionality.
 */
class Lora32WifiBleV2 {
  public:
    int BAND = 915E6; ///< Radio frequency, also can be: 433E6, 868E6, 915E6;
    int PABOOST = true;
    int DISPLAY_ADDRESS_PIN = 0x3c;
    int DISPLAY_SDA_PIN = 4;
    int DISPLAY_SCL_PIN = 15;
    int DISPLAY_RST_PIN = 16;
    int CS_PIN = 18;
    int RESET_PIN = 14;
    int IRQ_PIN = 26;
    SSD1306 display;

    /**
     * @brief Constructor to initialize the display with specified I2C pins.
     */
    Lora32WifiBleV2() : display(this->DISPLAY_ADDRESS_PIN, this->DISPLAY_SDA_PIN, this->DISPLAY_SCL_PIN) {}

    /**
     * @brief Initializes the module, setting up Serial, LoRa radio, and display.
     */
    void init() {
      Serial.begin(115200);
      while (!Serial);

      // Starting LoRa radio
      this->startLora();

      // Initializing the display
      if (!this->displayBegin()) {
        Serial.println("Display failed!");
        while (1);
      }

      // Configuring the display
      this->displayConfiguration();
    }

    /**
     * @brief Initializes the LoRa module with the specified pins and frequency.
     */
    void startLora() {
      // Set LoRa module pins
      LoRa.setPins(this->CS_PIN, this->RESET_PIN, this->IRQ_PIN);
      if (!LoRa.begin(this->BAND)) { // Set frequency to 915MHz
        Serial.println("Starting LoRa failed!");
        while (1);
      }

      Serial.println("LoRa Initializing OK!");
    }

    /**
     * @brief Initializes the display and resets it.
     * @return True if initialization is successful, false otherwise.
     */
    bool displayBegin() {
      // Restart the display
      pinMode(this->DISPLAY_RST_PIN, OUTPUT);
      digitalWrite(this->DISPLAY_RST_PIN, LOW);
      delay(1);
      digitalWrite(this->DISPLAY_RST_PIN, HIGH);
      delay(1);

      return this->display.init(); 
    }

    /**
     * @brief Configures the display settings and prints the initial text.
     * @param startText The initial text to be displayed. Default is "Starting...".
     */
    void displayConfiguration(String startText = "Starting...") {
      this->display.flipScreenVertically();
      this->display.setFont(ArialMT_Plain_10);
      this->display.setTextAlignment(TEXT_ALIGN_LEFT);

      this->displayPrintString(startText);
    }

    /**
     * @brief Clears the display.
     */
    void displayClear() {
      this->display.clear();
    }

    /**
     * @brief Refreshes the display to show the current buffer content.
     */
    void displayView() {
      this->display.display();
    }

    /**
     * @brief Prints a string at the specified coordinates on the display.
     * @param text The text to be printed.
     * @param x The x-coordinate for the text. Default is 5.
     * @param y The y-coordinate for the text. Default is 5.
     */
    void displayPrintString(String text, int x = 5, int y = 5) {
      this->display.drawString(x, y, text);
    }

    /**
     * @brief Clears the display, prints a string, and refreshes the display.
     * @param text The text to be printed.
     * @param x The x-coordinate for the text. Default is 5.
     * @param y The y-coordinate for the text. Default is 5.
     */
    void displayView(String text, int x = 5, int y = 5) {
      this->display.clear();
      this->displayPrintString(text, x, y);
      this->display.display();
    }
};

#endif // LORA32WIFIBLEV2_H
