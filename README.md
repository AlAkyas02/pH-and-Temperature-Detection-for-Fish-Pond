# pH and Temperature Detection for Fish Pond
**Team name**
1. M. Aulia Rahman (1102204383)
2. Martuagus Jonathan (1102200448)
3. Alfiqri Radifa Nugraha (1102200661)
4. Muhammad Abdul Halim Al Akyas (1102201680)

A. **Introduction**

>This project is to make a device that can calculate pH and temperature inside a pond for fish farmers. If there is some problem, like the pH is too high or too low, and when the temperature is too high or too low, there is a buzzer alarm to alert farmers. So the farmers can maintain the pond's pH and temperature afterward.

B. **Preparation**
>This project uses several components that are needed to make the device. There are:
>- 1 DFRobotV2 pH sensor
>- 1 DS18B20 temperature sensor
>- 1 Arduino Uno
>- 1 LCD I2C
>- 1 Buzzer 5-12V
>- 6 Pilot lamp 12V DC (2 red, 2 yellow, 2 green)
>- 1 Adaptor AC/DC 12V

C. **Assembling**
>To make sure all components went to the correct pin input/output, follow this step:
>- DFRobotV2 pH sensor --> pin A0
>- DS18B20 temperature sensor --> pin 2
>- LCD I2C --> pin SDA, SCL, VCC, and Ground
>- Red LED --> pin 3 (pH) and 7 (temperature)
>- Yellow LED --> pin 4 (pH) and 8 (temperature)
>- Green LED --> pin 5 (pH) and 9 (temperature) 
>- Buzzer 5-12V --> pin 10

D. **Coding**
>To make the device, there's a code to put inside Arduino Uno.
```
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
```
E. **Documentation**

![Wiring Progress](https://github.com/AlAkyas02/pH-and-Temperature-Detection-for-Fish-Pond/assets/154904312/a286606a-1564-40fa-a705-f9d3ea67f95d)
>Wiring Progress


![Result on LCD and Lamp](https://github.com/AlAkyas02/pH-and-Temperature-Detection-for-Fish-Pond/assets/154904312/24f4d9c6-cb8d-4eb2-aae2-6a99490e8476)
>Result on LCD and lamp


https://github.com/AlAkyas02/pH-and-Temperature-Detection-for-Fish-Pond/assets/154904312/90fa98a1-3a99-45c7-8db0-fad280b65851
>The project video

F. **Document**

[pH and Temperature Detection for Fish Pond.pdf](https://github.com/AlAkyas02/pH-and-Temperature-Detection-for-Fish-Pond/files/13776532/pH.and.Temperature.Detection.for.Fish.Pond.pdf)
