#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Relay
#define Relay_gnd 2
#define Relay_vcc 3
#define Relay_in 4
// change according of your own....
#define DRY 800
#define WET 200
#define THRESHOLD 400
#define Sensor A0
String value = "";
void setup()
{
Serial.begin(9600);
pinMode(Relay_vcc, OUTPUT);
pinMode(Relay_gnd, OUTPUT);
pinMode(Relay_in, OUTPUT);
digitalWrite(Relay_vcc, HIGH);
digitalWrite(Relay_gnd, LOW);
delay(3000);
lcd.begin();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Moisture:");
lcd.setCursor(0,1);
lcd.print("Pump:");
}
void loop()
{
value = String (map(analogRead(Sensor), DRY, WET, 100,0)) + "%";
Serial.print("Current value is : ");
Serial.print(analogRead(Sensor));
Serial.print(" | Moisture Percentage : ");
Serial.print(value);
Serial.print(" | Motor : ");
lcd.setCursor(9,0);
lcd.print(" ");
lcd.setCursor(9,0);
lcd.print(value);
lcd.setCursor(5,1);
lcd.print(" ");
lcd.setCursor(5,1);
if(analogRead(Sensor)<THRESHOLD){
digitalWrite(Relay_in, HIGH);
lcd.print("ON");
Serial.println("ON");
}else{
digitalWrite(Relay_in, LOW);
lcd.print("OFF");
Serial.println("OFF");
}
delay(20);
}