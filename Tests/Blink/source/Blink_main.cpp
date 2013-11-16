#include "Arduino.h"
#include "blink_main.h"
#include "MeetAndroid.h"

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

// include the library code:
#include <LiquidCrystal.h>

int backLight = 8;    // pin 8 will control the backlight
int btnPin = 17;
int btn = 0;
int camTr = 16;
int camFc = 15;
int led1 = 12;
int led2 = 13;
int sStep = 18;
int sDir = 19;
int bat = 14;

int serialVal = 0;
int batVal = 0;
float btnVal = 1;
float oldBtnVal = 0;

MeetAndroid meetAndroid;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {

  meetAndroid.registerFunction(slider, 'o');
  Serial.begin(115200);

  pinMode(backLight, OUTPUT);
  pinMode(btnPin, INPUT);
  digitalWrite(btnPin, HIGH);
  pinMode(bat, INPUT);
  pinMode(camTr, OUTPUT);
  pinMode(camFc, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(sDir, OUTPUT);
  pinMode(sStep, OUTPUT);
  
  digitalWrite(backLight, LOW); 
  // set up the LCD's number of columns and rows: 
  //lcd.begin(20, 4);
  lcd.begin(16,2);
  lcd.clear(); 
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
}

void loop() {
  
 delay(100);
 btnVal = analogRead(btnPin);
 batVal = analogRead(bat);
  
  //5v - 1023
  //4.12v btn1 - 843 -> 900 - 700; btnVal<900 &&btnVal>700
  //3.3v btn2 - 675 -> 700 - 600; btnVal<700 && btnVal>600
  //2.47v btn3 - 0.5 -> 600 - 400; btnVal<600 && btnVal>400
  //1.65v btn4 - 337.6 -> 400 - 300; btnVal<400 && btnVal>300
  //0.83v btn5 - 169.8 -> 300 - 100; btn<300 && btnVal>100
  //0v btn6 - 0 -> 100 - 0; btn<100
  
    if(btnVal>900){
      btn = 0;
      digitalWrite(backLight, LOW);
      digitalWrite(camTr, LOW);
      digitalWrite(camFc, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }
    else if(btnVal<900 && btnVal>700){
      btn = 1;
      digitalWrite(backLight, HIGH);
      digitalWrite(camTr, HIGH);
    }
    else if(btnVal<700 && btnVal>600){
      btn = 2;
      digitalWrite(backLight, HIGH);
      digitalWrite(camTr, HIGH);
      delay(500);
      digitalWrite(camFc, HIGH);
    }
    else if(btnVal<600 && btnVal>400){
      btn = 3;
      digitalWrite(backLight, HIGH);
      
      digitalWrite(sDir, HIGH);
      for(int i = 0; i<1000; i++){
        digitalWrite(sStep, HIGH);
		delayMicroseconds(100);
		digitalWrite(sStep, LOW);
		delayMicroseconds(100);
      }
    }
    else if (btnVal<400 && btnVal>300){
      btn = 4;
      digitalWrite(backLight, HIGH);
      
      digitalWrite(sDir, LOW);
      for(int i = 0; i<1000; i++){
        digitalWrite(sStep, HIGH);
		delayMicroseconds(100);
		digitalWrite(sStep, LOW);
		delayMicroseconds(100);
      }
    }
    else if (btn<300 && btnVal>100){
      btn = 5;
      digitalWrite(backLight, HIGH);
      digitalWrite(led2, HIGH);
    }
    else if (btn<100){
      btn = 6;
      digitalWrite(backLight, HIGH);
      digitalWrite(led1, HIGH);
    }
      
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0)
  lcd.setCursor(0, 1); // (column, row)
  // print the number of seconds since reset:
  lcd.print(btn);
  lcd.setCursor(2, 1);
  lcd.print(batVal);
  lcd.setCursor(8, 1);
  lcd.print(serialVal);
  meetAndroid.receive();
}

void slider(byte flag, byte numOfValues)
{
  serialVal = meetAndroid.getInt();
}