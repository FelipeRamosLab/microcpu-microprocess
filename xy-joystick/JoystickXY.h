class JoystickXYResponse {
  public:
    int x = 0;
    int y = 0;
    int buttonState = 0;
};

class JoystickXY {
  public:
    int _xAxisPin;
    int _yAxisPin;
    int _pressBtnPin;

    JoystickXY(int xAxisPin = 36, int yAxisPin = 37, int pressBtnPin = 25) {
      this->_xAxisPin = xAxisPin;
      this->_yAxisPin = yAxisPin;
      this->_pressBtnPin = pressBtnPin;
    }

    void init() {
      pinMode(this->_xAxisPin, INPUT); // Set the VRX pin as an input
      pinMode(this->_yAxisPin, INPUT); // Set the VRY pin as an input
      pinMode(this->_pressBtnPin, INPUT_PULLUP); // Set the SW pin as an input with a pull-up resistor
    }

    JoystickXYResponse read() {
      JoystickXYResponse response;

      response.x = analogRead(this->_xAxisPin); // Read the raw X-axis value
      response.y = analogRead(this->_yAxisPin); // Read the raw Y-axis value
      response.buttonState = digitalRead(this->_pressBtnPin); // Read the button state

      return response;
    }
};
