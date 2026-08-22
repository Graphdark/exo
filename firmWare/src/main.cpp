#include "exo.h"
#include "GBUS.h"
#include <SoftwareSerial.h>

#define GBUS_PIN 2
#define GBUS_BAUD 9600

SoftwareSerial gbusSerial(GBUS_PIN, GBUS_PIN);
GBUS slave(&gbusSerial, 2, 64);

struct ServoCommand {
  uint8_t lh, lk, rh, rk;
  uint8_t btn;
  uint8_t interval;
};

ServoCommand cmd;
int prev_lcmd = -1; // -1 гарантирует, что первая команда выведется при старте

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
  fexo.smoothSit();
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

  if (butD.click())
  {
    if (lcmd != 0) lcmd = lcmd-1;
  }
  if (bup.click())
  {
    if (lcmd != 3) lcmd = lcmd+1;
  }

  if (lcmd != prev_lcmd) {
        fexo.lcdPrint(fexo.fcmd[lcmd]);       // Вывод на LCD (только при изменении)
        Serial.println(fexo.fcmd[lcmd]);      // Вывод в Serial с новой строкой
        
        prev_lcmd = lcmd;                     // Запоминаем новое состояние как "предыдущее"
    }
  // if (fexo.bl.click())  //Если нажата левая лампочка горит.
  // {
  //   digitalWrite(LED_BUILTIN,HIGH);
  // }
  //   if (fexo.br.click())//Если нажата правая лампочка гаснет.
  // {
  //   digitalWrite(LED_BUILTIN,LOW);
  // }
  
  switch (lcmd)
  {
    case 0:
    {
      fexo.sit();
      break;
    }
    case 1:
    {
      fexo.stay();
      break;
    }
    case 2:
    {
      fexo.move();
      break;
    }
    case 3:
    {
      fexo.wOtS();
      break;
    }
  }

  if (handleGBUS())
  {
    fexo.servRul(cmd.lh,cmd.lk,cmd.rh,cmd.rk);
  }
  delay(10);
}