//Author: Tautrimas Marciulionis
//2022-11
//Thermometer using DS18B20 sensor
//No license, use as you like, just mention the author.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

//funny custom character
byte customCharB[] = {
  0x04,
  0x0E,
  0x0A,
  0x0A,
  0x0A,
  0x0E,
  0x1F,
  0x1B
};

//degree character
byte customChar[] = {
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

float t1, t2;

void setup(){
  lcd.init();
  lcd.clear();
  lcd.backlight();
  analogWrite(5, 5);
  lcd.createChar(0, customChar);
  lcd.createChar(1, customCharB);
}


void loop(){
    sensors.requestTemperatures();
    delay(1000);
    t1 = sensors.getTempCByIndex(0);
    t2 = sensors.getTempCByIndex(2);
    lcd.clear();
    lcd.setCursor(0, 0);
    //if no sensor
    if (t1 ==-127){
      lcd.print("Temp 1 = ");
      lcd.write(1);
    }else{
      lcd.print("Temp 1 = ");    
      lcd.print(t1, 1); //one decimal point
      lcd.write(0);
      lcd.print("C");
    }

    lcd.setCursor(0, 1);
    if (t2 ==-127){
      lcd.print("Temp 2 = ");
      lcd.print("NA");
    }else{
      lcd.print("Temp 2 = ");    
      lcd.print(t2, 1);
      lcd.write(0);
      lcd.print("C");
    }
  }
