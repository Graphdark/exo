#include "exo.h"

void exo::setLegPos(bool l, int p) {
    switch (p) {
        case 0: // Сидя
            smoothSit(); // Плавное садение
            break;
            
        case 1: // Стоя
            smoothStand(); // Плавное вставание
            break;
            
        case 2: // Шаг
            if (l) {
                rHip.write(stayA); rAncle.write(stayA);
                lHip.write(lHipA); lAncle.write(stayA);
            } else {
                lHip.write(stayA); lAncle.write(stayA);
                rHip.write(rHipA); rAncle.write(stayA);
            }
            break;
            
        case 3: // Шаг на месте
            if (l) {
                rHip.write(stayA); rAncle.write(stayA);
                lHip.write(sitHip); lAncle.write(sitAncle);
            } else {
                lHip.write(stayA); lAncle.write(stayA);
                rHip.write(sitHip); rAncle.write(sitAncle);
            }
            break;
            
        default:
            break;
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
    lcdPrint("server");
    lHip.write(lH);
    lAncle.write(lA);
    rHip.write(rH);
    rAncle.write(rA);
}

void exo::lcdPrint(String str)
{
    int l = (16 - str.length())/2;
    lcd.clear();
    lcd.setCursor(l,0);
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

// void exo::setLHipA()
// {
//     if (bl.click() && lHipA < 180) lHipA++;      // +1 градус
//     else if (br.click() && lHipA > 0) lHipA--;   // -1 градус
//     lcdPrint("Left Hip ang:" + lHipA);
// }

// void exo::setLAncleA()
// {
//     if (bl.click())
//     {
//         if (lAncleA == 180) lAncleA = lAncleA;
//         lAncleA += lAncleA;
//     }
//     else if (br.click())
//     {
//         if (lAncleA == 30) lAncleA = lAncleA;;
//         lAncleA -= lAncleA;
//     }
//     lcdPrint("Left Anc ang:" + lAncleA);
// }

// void exo::setRHipA()
// {
//     if (bl.click())
//     {
//         if (rHipA == 135) rHipA = rHipA;
//         rHipA += rHipA;
//     }
//     else if (br.click())
//     {
//         if (rHipA == 0) rHipA = rHipA;
//         rHipA -= rHipA;
//     }
//     lcdPrint("RightHip ang:" + lHipA);
// }

// void exo::setRAncleA()
// {
//     if (bl.click())
//     {
//         if (rAncleA == 180) rAncleA = rAncleA;
//         rAncleA += rAncleA;
//     }
//     else if (br.click())
//     {
//         if (rAncleA == 30) rAncleA = rAncleA;
//         rAncleA -= rAncleA;
//     }
//     lcdPrint("RightAnc ang:" + rAncleA);
// }

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
      setLegPos(true,3);
    }
    if (br.click())
    {
      setLegPos(false,3);
    }
}

void exo::stay()
{
    setLegPos(true,1);
}

void exo::smoothStand() {
    int currentLHip = lHip.read();
    int currentLAncle = lAncle.read();
    int currentRHip = rHip.read();
    int currentRAncle = rAncle.read();
    
    const int hipDelay = 60;    // Бедро: замедление на 75% (в 4 раза медленнее базовых 15мс)
    const int ancleDelay = 30;  // Колено: замедление вдвое (в 2 раза медленнее)
    
    unsigned long lastHipMove = 0;
    unsigned long lastAncleMove = 0;
    
    while (currentLHip != stayA || currentLAncle != stayA || 
           currentRHip != stayA || currentRAncle != stayA) {
        
        unsigned long now = millis();
        
        // Двигаем бедра (медленно)
        if (now - lastHipMove >= hipDelay) {
            if (currentLHip != stayA) {
                currentLHip += (stayA > currentLHip) ? 1 : -1;
                lHip.write(currentLHip);
            }
            if (currentRHip != stayA) {
                currentRHip += (stayA > currentRHip) ? 1 : -1;
                rHip.write(currentRHip);
            }
            lastHipMove = now;
        }
        
        // Двигаем колени (быстрее)
        if (now - lastHipMove >= ancleDelay) {
            if (currentLAncle != stayA) {
                currentLAncle += (stayA > currentLAncle) ? 1 : -1;
                lAncle.write(currentLAncle);
            }
            if (currentRAncle != stayA) {
                currentRAncle += (stayA > currentRAncle) ? 1 : -1;
                rAncle.write(currentRAncle);
            }
            lastAncleMove = now;
        }
    }
}

void exo::smoothSit() {
    int currentLHip = lHip.read();
    int currentLAncle = lAncle.read();
    int currentRHip = rHip.read();
    int currentRAncle = rAncle.read();
    
    const int hipDelay = 15;    // Бедро: быстро
    const int ancleDelay = 30;  // Колено: медленно (в 2 раза)
    
    unsigned long lastHipMove = 0;
    unsigned long lastAncleMove = 0;
    
    while (currentLHip != sitHip || currentLAncle != sitAncle || 
           currentRHip != sitHip || currentRAncle != sitAncle) {
        
        unsigned long now = millis();
        
        // Двигаем бедра (быстро)
        if (now - lastHipMove >= hipDelay) {
            if (currentLHip != sitHip) {
                currentLHip += (sitHip > currentLHip) ? 1 : -1;
                lHip.write(currentLHip);
            }
            if (currentRHip != sitHip) {
                currentRHip += (sitHip > currentRHip) ? 1 : -1;
                rHip.write(currentRHip);
            }
            lastHipMove = now;
        }
        
        // Двигаем колени (медленно)
        if (now - lastAncleMove >= ancleDelay) {
            if (currentLAncle != sitAncle) {
                currentLAncle += (sitAncle > currentLAncle) ? 1 : -1;
                lAncle.write(currentLAncle);
            }
            if (currentRAncle != sitAncle) {
                currentRAncle += (sitAncle > currentRAncle) ? 1 : -1;
                rAncle.write(currentRAncle);
            }
            lastAncleMove = now;
        }
    }
}

