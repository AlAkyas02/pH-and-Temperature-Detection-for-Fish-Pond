#include "DFRobot_PH.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <toneAC.h>  // Tambahkan library toneAC

LiquidCrystal_PCF8574 lcd(0x27);

#define sensor_ds18b20 2
OneWire oneWire(sensor_ds18b20);
DallasTemperature sensors(&oneWire);

int sensorPin = A0;
float tegangan, nilaiph;
int suhu;
DFRobot_PH ph;

const int redLedPin = 3;
const int yellowLedPin = 4;
const int greenLedPin = 5;

const int redLedPin2 = 7;
const int yellowLedPin2 = 8;
const int greenLedPin2 = 9;

const int buzzerPin = 10;

void setup()
{
    Serial.begin(9600);
    ph.begin();
    sensors.begin();
    lcd.begin(16, 2);
    lcd.setBacklight(255);
    lcd.setCursor(0, 0);
    lcd.print("MONITORING PH AIR");
    lcd.setCursor(0, 1);
    lcd.print("IKAN LELE");
    delay(2000);
    lcd.clear();

    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);
}

void loop()
{
    sensors.requestTemperatures();
    static unsigned long timepoint = millis();
    if (millis() - timepoint > 1000U)
    {
        timepoint = millis();
        tegangan = analogRead(sensorPin) / 1024.0 * 5000;
        suhu = sensors.getTempCByIndex(0);
        nilaiph = ph.readPH(tegangan, suhu);

        Serial.print("Celsius temperature: ");
        Serial.print(suhu, 1);
        Serial.print("°C  pH:");
        Serial.println(nilaiph, 2);

        lampu();

        lcd.setCursor(0, 0);
        lcd.print("Suhu: ");
        lcd.setCursor(0, 5);
        lcd.print(suhu, 1);
        lcd.print((char)223);

        lcd.setCursor(0, 1);
        lcd.print("PH :");
        lcd.setCursor(4, 1);
        lcd.print(nilaiph, 2);

        lcd.setCursor(10, 1);
        if (nilaiph < 6){
            lcd.print("Asam  ");}
        else if (nilaiph > 8){
            lcd.print("Basa  ");}
        else {
            lcd.print("Normal");}
    }
    ph.calibration(tegangan, suhu);
}

void lampu()
{
    if (nilaiph > 8)
    {
        digitalWrite(redLedPin, HIGH);
        digitalWrite(yellowLedPin, LOW);
        digitalWrite(greenLedPin, LOW);
        toneAC(buzzerPin, 1000); 
    }
    else if (nilaiph < 6)
    {
        digitalWrite(redLedPin, LOW);
        digitalWrite(yellowLedPin, HIGH);
        digitalWrite(greenLedPin, LOW);
        toneAC(buzzerPin, 1000);
    }
    else 
    {
        digitalWrite(redLedPin, LOW);
        digitalWrite(yellowLedPin, LOW);
        digitalWrite(greenLedPin, HIGH);
        noTone(buzzerPin); // Matikan buzzer jika pH = 7
    }

    if (suhu <= 28)
    {
        digitalWrite(redLedPin2, LOW);
        digitalWrite(yellowLedPin2, HIGH);
        digitalWrite(greenLedPin2, LOW);
    }
    else if (suhu >= 30)
    {
        digitalWrite(redLedPin2, HIGH);
        digitalWrite(yellowLedPin2, LOW);
        digitalWrite(greenLedPin2, LOW);
    }
    else
    {
        digitalWrite(redLedPin2, LOW);
        digitalWrite(yellowLedPin2, LOW);
        digitalWrite(greenLedPin2, HIGH);
    }
}
