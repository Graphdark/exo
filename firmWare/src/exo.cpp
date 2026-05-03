#include "exo.h"

exo::exo()
{
}

void exo::atach(int Hipl, int Anclel, int Hipr, int Ancler, int butL, int butR)
{
    lHip.attach(Hipl);
    lAncle.attach(Anclel);
    rHip.attach(Hipr);
    rAncle.attach(Ancler);
    bl.atach(butL);
    br.atach(butR);
    lcd.attach(0x27, 16, 2);//0x20
    lcd.init();
    lcd.backlight();
}

void exo::servRul(int lH, int lA, int rH, int rA)
{
    lHip.write(lH);
    lAncle.write(lA);
    rHip.write(rH);
    rAncle.write(rA);
}

void exo::lcdPrint(String str)
{
    int l = (16 - str.length())/2;
    lcd.clear();
    lcd.setCursor(0,l);
    lcd.print(str);
}

void exo::move()
{
    if (bl.click())
    {
        lHip.write(lHipA);
        lAncle.write(lAncleA);
        Serial.println(rAngle());
        lAncle.write(stayA);
        lHip.write(stayA);
    }
    if (br.click())
    {
        rHip.write(rHipA);
        rAncle.write(rAncleA);
        Serial.println(rAngle());
        rAncle.write(stayA);
        rHip.write(stayA);
    }
    
    // if (bl.click())
    // {
    //     rAncle.write((rAncleA));
    //     delay(10);
    //     rHip.write((rHipA));
    //     delay(10);
    //     lHip.write((lHipA));
    //     delay(10);
    //     lAncle.write((lAncleA));
    //     delay(10);
    //     // rAncle.write((lHipA));
    // }
    // if (br.click())
    // {
    //     lAncle.write((rAncleA));
    //     delay(10);
    //     lHip.write((rHipA));
    //     delay(10);
    //     rHip.write((lHipA));
    //     delay(10);
    //     rAncle.write((lAncleA));
    //     delay(10);
    //     // lAncle.write((lHipA));
    //     // delay(10);
    // }
}

void exo::setLHipA()
{
    if (bl.click())
    {
        if (lHipA == 135) lHipA = lHipA;
        lHipA += lHipA;
    }
    else if (br.click())
    {
        if (lHipA == 0) lHipA = lHipA;
        lHipA -= lHipA;
    }
    lcdPrint("Left Hip ang:" + lHipA);
}

void exo::setLAncleA()
{
    if (bl.click())
    {
        if (lAncleA == 180) lAncleA = lAncleA;
        lAncleA += lAncleA;
    }
    else if (br.click())
    {
        if (lAncleA == 30) lAncleA = lAncleA;;
        lAncleA -= lAncleA;
    }
    lcdPrint("Left Anc ang:" + lAncleA);
}

void exo::setRHipA()
{
    if (bl.click())
    {
        if (rHipA == 135) rHipA = rHipA;
        rHipA += rHipA;
    }
    else if (br.click())
    {
        if (rHipA == 0) rHipA = rHipA;
        rHipA -= rHipA;
    }
    lcdPrint("RightHip ang:" + lHipA);
}

void exo::setRAncleA()
{
    if (bl.click())
    {
        if (rAncleA == 180) rAncleA = rAncleA;
        rAncleA += rAncleA;
    }
    else if (br.click())
    {
        if (rAncleA == 30) rAncleA = rAncleA;
        rAncleA -= rAncleA;
    }
    lcdPrint("RightAnc ang:" + rAncleA);
}

String exo::rAngle()
{
    String res = String(lHip.read()) + " " + String(lAncle.read()) + " " + String(rHip.read()) + " " + String(rAncle.read());
    return res;
}

void exo::sit()
{
    if (br.click()&&bl.click())
    {
        lHip.write(sitHip-10);
        lAncle.write(sitAncle-10);
        rHip.write(sitHip-10);
        rAncle.write(sitAncle-10);
        delay(100);
    }
}

void exo::sit(bool b)
{
    lHip.write(sitHip-10);
    lAncle.write(sitAncle-10);
    rHip.write(sitHip-10);
    rAncle.write(sitAncle-10);
    delay(100);
}

void exo::wOtS()
{
    stay(true);
    if (bl.click())
    {
        if(rAncle.read()==stayA&&rHip.read()==stayA)
        {
            lHip.write(sitHip);
            lAncle.write(sitAncle);
            lAncle.write(stayA);
            lHip.write(stayA);
        }
    }
    if (br.click())
    {
        if (lAncle.read()==stayA&&lHip.read()==stayA)
        {
            rHip.write(sitHip);
            rAncle.write(sitAncle);
            rAncle.write(stayA);
            rHip.write(stayA);
        }
    }
    // if (bl.click())
    // {
    //     lHip.write(45);
    //     delay(100);
    //     lAncle.write(135);
    //     delay(100);
    //     rHip.write(180);
    //     delay(100);
    //     rAncle.write(180);
    //     delay(100);
    //     lHip.write(180);
    //     delay(100);
    //     lAncle.write(180);
    //     delay(100);
    // }
    // if (br.click())
    // {
    //     rHip.write(45);
    //     delay(100);
    //     rAncle.write(135);
    //     delay(100);
    //     lHip.write(180);
    //     delay(100);
    //     lAncle.write(180);
    //     delay(100);
    //     rHip.write(180);
    //     delay(100);
    //     rAncle.write(180);
    //     delay(100);
    // }
}

void exo::stay(bool b)
{
    lHip.write(180);
    lAncle.write(180);
    rHip.write(180);
    rAncle.write(180);
    delay(100);
}

void exo::stay()
{
    if (br.click()&&bl.click())
    {
        lHip.write(180);
        lAncle.write(180);
        rHip.write(180);
        rAncle.write(180);
        delay(100);
    }
}



