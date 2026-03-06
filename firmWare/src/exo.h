#include "button.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

class exo
{
private:
    int lHipA = 5, lAncleA = 95, rHipA = 180, rAncleA = 10, sitHip = 90, sitAncle = 90;
    Servo lHip, lAncle, rHip, rAncle;
    button bl;
    button br;
    void rAngle();
public:
    String fcmd[8] {"sit","stay","walk","wOp","set Left Hip","set Left Anc","set Right Hip","set Right Anc"};
    LiquidCrystal_I2C lcd;
    exo();
    void atach(int Hipl, int Anclel, int Hipr, int Ancler, int butL, int butR);
    int getLHipA() {return lHipA;};
    int getLAncleA() {return lAncleA;};
    int getRHipA() {return rHipA;};
    int getRAncleA() {return rAncleA;};
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
    bool needClear = false;
};
