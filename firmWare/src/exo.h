#include "button.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

class exo
{
private:
    int lHipA = 175, lAncleA = 175, rHipA = 175, rAncleA = 175, stayA = 180, sitHip = 90, sitAncle = 90;
    Servo lHip, lAncle, rHip, rAncle;
    LiquidCrystal_I2C lcd;
public:
    String fcmd[8] {"sit","stay","walk","wOp","set Left Hip","set Left Anc","set Right Hip","set Right Anc"};
    button bl;
    button br;
    exo();
    void atach(int Hipl, int Anclel, int Hipr, int Ancler, int butL, int butR);
    int getLHipA() {return lHipA;};
    int getLAncleA() {return lAncleA;};
    int getRHipA() {return rHipA;};
    int getRAncleA() {return rAncleA;};
    void servRul(int lH, int lA, int rH, int rA);
    void lcdPrint(String str);
    void move();
    void stay();
    void sit();
    void stay(bool b);
    void sit(bool b);
    void wOtS();
    void climbU();
    void climbD();
    void setLHipA();
    void setLAncleA();
    void setRHipA();
    void setRAncleA();
    void setSitHitA();
    void setSitAncleA();
    String rAngle();
};
