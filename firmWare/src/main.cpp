#include "exo.h"

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

void lcdPrint(String str)
{
  if (fexo.needClear) return;
  fexo.lcd.clear();
  fexo.lcd.setCursor(1, 0);
  fexo.lcd.print(str);
}

void lcdPrint(int str)
{
  fexo.lcd.clear();
  fexo.lcd.setCursor(1, 0);
  fexo.lcd.print(str);
}

void setup()
{
  Serial.begin(9600);
  pinMode (LED_BUILTIN, OUTPUT);
  fexo.atach(lHip,lAncle,rHip,rAncle,leftb,rightb);
  fexo.sit(true);
  butD.atach(bD);
  bup.atach(UpB);

  fexo.lcd.setCursor(1, 0);
  fexo.lcd.print("load");
}

void loop()
{
  // lcd.clear();
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
      lcdPrint(fexo.fcmd[lcmd]);
      Serial.println(fexo.fcmd[lcmd]);
      break;
    }
    case 1:
    {
      fexo.stay();
      lcdPrint(fexo.fcmd[lcmd]);
      Serial.print(fexo.fcmd[lcmd]);
      break;
    }
    case 2:
    {
      fexo.move();
        fexo.needClear = true;
      lcdPrint(fexo.fcmd[lcmd]);
      Serial.print(fexo.fcmd[lcmd]);
      break;
    }
    case 3:
    {
      fexo.wOtS();
      lcdPrint(fexo.fcmd[lcmd]);
      Serial.print(fexo.fcmd[lcmd]);
      break;
    }
  case 4:
      {
        fexo.setLHipA();
        fexo.needClear = true;
        lcdPrint(fexo.fcmd[lcmd]);
        Serial.print(fexo.fcmd[lcmd]);
        break;
      }
  case 5:
      {
        fexo.setLAncleA();
        fexo.needClear = true;
        lcdPrint(fexo.fcmd[lcmd]);
        Serial.print(fexo.fcmd[lcmd]);
        break;
      }
  case 6:
      {
        fexo.setRHipA();
        fexo.needClear = true;
        lcdPrint(fexo.fcmd[lcmd]);
        Serial.print(fexo.fcmd[lcmd]);
        break;
      }
  case 7:
      {
        fexo.setRAncleA();
        fexo.needClear = true;
        lcdPrint(fexo.fcmd[lcmd]);
        Serial.print(fexo.fcmd[lcmd]);
        break;
      }
  }
}