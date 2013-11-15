/*************************************************************
project: <type project name here>
author: <type your name here>
description: <type what this file does>
*************************************************************/

/*
//------------------------------------
//------------------------------------
//	
//	  1234567890123456
//   -----------------
// 1 | ? Simple Move
// 2 | V Seqence Smart
// 3 |   Seqence Basic
//   -----------------
//
//-----------
//Sub-Menu's:
//
// Simple Move:  
//	  1234567890123456
// -------------------
// 1 | Click to move
// 2 |<<<<S:xx>>>>P:xx
// ------------------- 
//
// Sequence Smart: 
//    1234567890123456
// -------------------
// 1 | ? FPS:xx #
// 2 | V Output:xxx s
// 3 |   Event:xxx min
// 4 |   Range:xx %
// 5 |   Start
// -------------------
//
// Sequence Basic:
//    1234567890123456
// -------------------
// 1 | ? Delay:xx s
// 2 | V Frames:xxx #
// 3 |   Move:xx cm
// 5 |   Start
// -------------------
//
//------------------------------------
//------------------------------------
*/

#include "Arduino.h"
#include "LcdDevice.h"
#include "LiquidCrystal.h"

//#define version v0.1
#define backLightPin 8

//#define topMenuLine1 #Simple Move

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

LcdDevice::LcdDevice(){

	pinMode(backLightPin, OUTPUT);
	digitalWrite(backLightPin, HIGH);
	lcd.begin(16,2);
	lcd.clear(); 
	lcd.setCursor(0, 0); // (column, row)
	lcd.print("Motorized Camera");
	lcd.setCursor(0, 1); // (column, row)
	//lcd.print(version);
	
	manualSpeed = 0;
	manualPosition = 0;
	smartFps = 0;
	smartOutputDuration = 0;
	smartEventDuration = 0;
	samrtMovementRange = 0;
	startFlag = 0;
}

void LcdDevice::lcdRefresh(){
	lcd.setCursor(0, 0); // (column, row)
	lcd.print("Motorized Camera");
	lcd.setCursor(0, 1); // (column, row)
	//lcd.print(version);
}

void LcdDevice::displayText(){
}

void LcdDevice::displayNumeric(){
}

void LcdDevice::zeroValues(){
	manualSpeed = 0;
	manualPosition = 0;
	smartFps = 0;
	smartOutputDuration = 0;
	smartEventDuration = 0;
	samrtMovementRange = 0;
	startFlag = 0;
}