
#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class button {
    public:
      button(){};
      
      void atach(byte pin) {
        _pin = pin;
        pinMode(_pin, INPUT_PULLUP);
      }
      
      bool click() {
        bool btnState = digitalRead(_pin);
        
        // Первый клик (фиксируем нажатие)
        if (!btnState && !_flag && millis() - _tmr >= 100) {
          _flag = true;
          _tmr = millis();
          return true;
        }
        
        // Автоповтор при удержании кнопки (каждые 500 мс)
        if (!btnState && _flag && millis() - _tmr >= 500) {
          _tmr = millis();
          return true;
        }
        
        // Отпускание кнопки (сброс флага)
        if (btnState && _flag) {
          _flag = false;
          _tmr = millis();
        }
        
        return false;
      }
      
    private:
      byte _pin = 0;
      uint32_t _tmr = 0;
      bool _flag = false;
  };

#endif