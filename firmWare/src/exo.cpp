#include "exo.h"

void exo::rAngle()
{
    lcd.setCursor(0,1);
    lcd.print("RH:") + lcd.print(rHip.read()) + lcd.print("RA:") + lcd.print(rAncle.read()) + lcd.print("    ");
    lcd.setCursor(0,0);
    lcd.print("LH:") + lcd.print(lHip.read()) + lcd.print("LA:") + lcd.print(lAncle.read()) + lcd.print("    ");
}

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

void exo::move()
{
    rAngle();
    if (bl.click())
    {
        rAncle.write((lHipA));
        delay(10);
        rHip.write((rHipA));
        delay(10);
        lHip.write((lHipA));
        delay(10);
        lAncle.write((lAncleA));
        delay(10);
        // rAncle.write((lHipA));
    }
    if (br.click())
    {
        lAncle.write((lHipA));
        delay(10);
        lHip.write((rHipA));
        delay(10);
        rHip.write((lHipA));
        delay(10);
        rAncle.write((lAncleA));
        delay(10);
        // lAncle.write((lHipA));
        // delay(10);
    }
    rAngle();
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
    bool needClear = true;
    if (needClear)
    {
        needClear = !needClear;
        lcd.clear();
    }
    lcd.setCursor(1,0);
    lcd.print("set Left Hip:");
    lcd.setCursor(1,1);
    lcd.print("Left Hip ang:")+lcd.print(lHipA);
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
    bool needClear = true;
    if (needClear)
    {
        needClear = !needClear;
        lcd.clear();
    }
    lcd.setCursor(1,0);
    lcd.print("set Left Ancle:");
    lcd.setCursor(1,1);
    lcd.print("Left Anc ang:")+lcd.print(lAncleA);
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
    bool needClear = true;
    if (needClear)
    {
        needClear = !needClear;
        lcd.clear();
    }
    lcd.setCursor(1,0);
    lcd.print("set Right Hip:");
    lcd.setCursor(1,1);
    lcd.print("RightHip ang:")+lcd.print(lHipA);
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
    if (needClear)
    {
        needClear = !needClear;
        lcd.clear();
    }
    lcd.setCursor(1,0);
    lcd.print("set Right Ancle:");
    lcd.setCursor(1,1);
    lcd.print("RightAnc ang:")+lcd.print(rAncleA);
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
    needClear = false;
    stay(true);
    if (bl.click())
    {
        lHip.write(45);
        delay(100);
        lAncle.write(135);
        delay(100);
        rHip.write(180);
        delay(100);
        rAncle.write(180);
        delay(100);
        lHip.write(180);
        delay(100);
        lAncle.write(180);
        delay(100);
    }
    if (br.click())
    {
        rHip.write(45);
        delay(100);
        rAncle.write(135);
        delay(100);
        lHip.write(180);
        delay(100);
        lAncle.write(180);
        delay(100);
        rHip.write(180);
        delay(100);
        rAncle.write(180);
        delay(100);
    }
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



