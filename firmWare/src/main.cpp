#include "exo.h"
#include "GBUS.h"
#include <SoftwareSerial.h>

#define GBUS_PIN 4
#define GBUS_BAUD 9600

SoftwareSerial gbusSerial(GBUS_PIN, GBUS_PIN);
GBUS slave(&gbusSerial, 2, 64);

struct ServoCommand {
  uint8_t lh, lk, rh, rk;
  uint8_t btn;
  uint8_t interval;
};

ServoCommand cmd;

const int lHip = 10;
const int lAncle = 9;
const int rHip = 8;
const int rAncle = 7;

const int UpB = 6;
const int bD = 5;
const int leftb = 11;
const int rightb = 12;

// LiquidCrystal_I2C lcd(0x27, 16, 2);
bool needPrint = false;
exo fexo;
button butD, bup;
int lcmd = 0;

bool handleGBUS() {
  if (slave.gotData()) {
    // 🔹 Исправлено: явное приведение типов
    if (slave.readData(cmd)) {
      // Используем Serial.print вместо printf для совместимости с AVR
      Serial.print("📥 Received: LH="); Serial.print(cmd.lh);
      Serial.print(", LK="); Serial.print(cmd.lk);
      Serial.print(", RH="); Serial.print(cmd.rh);
      Serial.print(", RK="); Serial.println(cmd.rk);
      return true;
    }
  }
  return false;
}

void setup()
{
  Serial.begin(9600);
  pinMode (LED_BUILTIN, OUTPUT);
  fexo.atach(lHip,lAncle,rHip,rAncle,leftb,rightb);
  fexo.sit(true);
  butD.atach(bD);
  bup.atach(UpB);
  gbusSerial.begin(GBUS_BAUD);

  fexo.lcdPrint("load");
  delay(2000);
}

void loop()
{
  // lcd.clear();
  slave.tick();
  if (handleGBUS())
  {
    fexo.servRul(cmd.lh,cmd.lk,cmd.rh,cmd.rk);
  }
  
  if (butD.click())
  {
    if (lcmd != 0) lcmd = lcmd-1;
  }
  if (bup.click())
  {
    if (lcmd != 7) lcmd = lcmd+1;
  }
  switch (lcmd)
  {
    case 0:
    {
      fexo.sit();
      fexo.lcdPrint(fexo.fcmd[lcmd]);
      Serial.println(fexo.fcmd[lcmd]);
      break;
    }
    case 1:
    {
      fexo.stay();
      fexo.lcdPrint(fexo.fcmd[lcmd]);
      Serial.print(fexo.fcmd[lcmd]);
      break;
    }
    case 2:
    {
      fexo.move();
      fexo.lcdPrint(fexo.fcmd[lcmd]);
      Serial.print(fexo.fcmd[lcmd]);
      break;
    }
    case 3:
    {
      fexo.wOtS();
      fexo.lcdPrint(fexo.fcmd[lcmd]);
      Serial.print(fexo.fcmd[lcmd]);
      break;
    }
  case 4:
      {
        fexo.setLHipA();
        fexo.lcdPrint(fexo.fcmd[lcmd]);
        Serial.print(fexo.fcmd[lcmd]);
        break;
      }
  case 5:
      {
        fexo.setLAncleA();
        fexo.lcdPrint(fexo.fcmd[lcmd]);
        Serial.print(fexo.fcmd[lcmd]);
        break;
      }
  case 6:
      {
        fexo.setRHipA();
        fexo.lcdPrint(fexo.fcmd[lcmd]);
        Serial.print(fexo.fcmd[lcmd]);
        break;
      }
  case 7:
      {
        fexo.setRAncleA();
        fexo.lcdPrint(fexo.fcmd[lcmd]);
        Serial.print(fexo.fcmd[lcmd]);
        break;
      }
  }
}