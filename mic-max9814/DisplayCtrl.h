// DisplayCtrl.h
#ifndef DISPLAYCTRL_H
#define DISPLAYCTRL_H

#include <LoRa.h>
#include <SSD1306.h> // Display library
#include <string>
using namespace std;

// Display Pins (i2c)
int DISPLAY_ADDRESS_PIN = 0x3c;
int DISPLAY_SDA_PIN = 4;
int DISPLAY_SCL_PIN = 15;
int DISPLAY_RST_PIN = 16;

// The display object
SSD1306 display(DISPLAY_ADDRESS_PIN, DISPLAY_SDA_PIN, DISPLAY_SCL_PIN);

class DisplayCtrl {
  public:
    DisplayCtrl(int fontSize):
    fontSize(fontSize) { }

    int fontSize;

    void init() {
      this->displayBegin();
      this->displayConfiguration();
    }

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
    
    void displayClean() {
      display.clear();
      display.display();
    }

    void drawString(char* toSend, int x = 10, int y = 10) {
      display.drawString(x, y, toSend);
    }

    void drawAndDisplayString(char* toSend, int x = 10, int y = 10) {
      this->drawString(toSend, x, y);
      display.display();
    }

    void printDrawString(char* toSend, int x = 10, int y = 10) {
      this->displayClean();
      this->drawString(toSend, x, y);
      display.display();
    }
};

#endif // DISPLAYCTRL_H
