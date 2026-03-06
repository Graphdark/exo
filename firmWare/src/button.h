#include <Arduino.h>

class button {
    public:
      button(){};
      void atach (byte pin) {
        _pin = pin;
        pinMode(_pin, INPUT_PULLUP);
      }
      bool click() {
        bool btnState = digitalRead(_pin);
        if (!btnState && !_flag && millis() - _tmr >= 100) {
          _flag = true;
          _tmr = millis();
          return true;
        }
        if (!btnState && _flag && millis() - _tmr >= 500) {
          _tmr = millis ();
          return true;
        }
        if (btnState && _flag) {
          _flag = false;
          _tmr = millis();
        }
        return false;
      }
    private:
      byte _pin;
      uint32_t _tmr;
      bool _flag;
  };