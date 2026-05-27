#include "exo.h"

void exo::setLegPos(bool l, int p)
{
    if (l == legState) return;
    legState = l;

    switch (p)
    {
        case 0: // Сидя
            rHip.write(sitHip);   rAncle.write(sitAncle);
            lHip.write(sitHip);   lAncle.write(sitAncle);
            break;

        case 1: // Стоя
            rHip.write(stayA);    rAncle.write(stayA);
            lHip.write(stayA);    lAncle.write(stayA);
            break;

        case 2: // Шаг
            if (l) {
                rHip.write(stayA);  rAncle.write(stayA);
                lHip.write(lHipA);  lAncle.write(lAncleA);
            } else {
                lHip.write(stayA);  lAncle.write(stayA);
                rHip.write(lHipA);  rAncle.write(lAncleA);
            }
            break;

        case 3: // Одна нога сидит, другая стоит
            if (l) {
                rHip.write(stayA);  rAncle.write(stayA);
                lHip.write(sitHip); lAncle.write(sitAncle);
            } else {
                lHip.write(stayA);  lAncle.write(stayA);
                rHip.write(sitHip); rAncle.write(sitAncle);
            }
            break;
            
        default:
            break; // Защита от невалидного p
    }
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
        setLegPos(true,2);
    }
    if (br.click())
    {
        setLegPos(false,2);
    }
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
    setLegPos(true,0);
}

void exo::wOtS()
{
    if (bl.click())
    {
      setLegPos(true,2);
    }
    if (br.click())
    {
      setLegPos(false,2);
    }
}

void exo::stay()
{
    setLegPos(true,1);
}



