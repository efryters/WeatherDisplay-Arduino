#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

#include "CustomChars.h"


#define RED 0x1

#define MN_OPTIONS 4

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
int menu = 0;
bool lcdChanged = false;
String messageIn = "";

void setMenu(int);

void setup()
{
    Serial.begin(9600);
    lcd.begin(16,2);
    lcd.createChar(0, overcastL);
    lcd.createChar(1, overcastR);
    lcd.createChar(2, solA);
    lcd.createChar(3, solB);
    setMenu(0);
}  

void resetLCD()    
{
    lcd.clear();
}

void printCustom(int xPos, int yPos, int icon)
{
    lcd.setCursor(xPos,yPos);
    lcd.write(icon);
}

void printText(int xPos, int yPos, bool inverted, String msg)
{
    if (inverted)
        {
            lcd.rightToLeft();
            lcd.setCursor(xPos,yPos);
            lcd.print(flipString(msg));
            lcd.leftToRight();
            }
    else
    {
            lcd.setCursor(xPos,yPos);
            lcd.print(msg);
            lcd.leftToRight();
    }

}

void debugMsg(String Msg)
{
    Serial.println(Msg);
}

void updateDisplay(int menu)
{
    if (lcdChanged)
    {
        lcd.clear();
        
        lcd.setCursor(15,0);
        lcd.rightToLeft();
        lcd.print(flipString(messageIn));
        lcdChanged = false;
        lcd.leftToRight();
        printCustom(0,0,0);
        printCustom(1,0,1);
        setMenu(menu);
    }
}

String flipString(String in)
{
    int len = in.length() - 1;
    char temp;
    if (in.length() % 2 == 0)
    {
        for (int i = 0; i < in.length()/2; i++)
        {
            temp = in[i];
            in[i] = in[in.length()-1-i];
            in[in.length()-i-1] = temp;
        }
    }
    else
    {
        for (int i = 0; i < (in.length()-1)/2; i++)
        {
            temp = in[i];
            in[i] = in[in.length()-1-i];
            in[in.length()-i-1] = temp;
        }
    }
    return in;
}

void setMenu(int menuOpt)
{
        switch(menuOpt)
    {
        case 0:
            //lcd.clear();
            messageIn = "Kitchener, ON";
            if (messageIn.length() > 12)
            {
                messageIn = messageIn.substring(0,12);
            }
            printText(15,1,true,messageIn);
            messageIn = "20";
            messageIn = messageIn + (char)223;
            printText(15,0,true,messageIn);
            printCustom(0,0,0);
            printCustom(1,0,1);
            break;
        
        
        
        case 1:
            //lcd.clear();
            lcd.setCursor(0,1);
            lcd.print("Menu 1");
            debugMsg("menu 1");
            break;           
        case 2:
            //lcd.clear();
            lcd.setCursor(0,1);
            lcd.print("Menu 2");
            debugMsg("menu 2");
            break;           
        case 3:
            //lcd.clear();
            lcd.setCursor(0,1);
            lcd.print("Menu 3");
            debugMsg("menu 3");
            break;           
        case 4:
            //lcd.clear();
            lcd.setCursor(0,1);
            lcd.print("Menu 4");
            debugMsg("menu 4");
            break;           
    }
}

void loop()
{

uint8_t buttons = lcd.readButtons();
if (buttons)
{
    if (buttons & BUTTON_UP) 
    {    
        menu++;
        resetLCD();
        setMenu(menu);
    }
    if (buttons & BUTTON_DOWN)
        menu--;
        resetLCD();
        setMenu(menu);    
}    

if (menu < 0)
    menu = MN_OPTIONS;
else if (menu > MN_OPTIONS)
    menu = 0;

while (Serial.available() > 0)
{
    messageIn = Serial.readString();
    lcdChanged = true;
}

//updateDisplay(menu);
}   