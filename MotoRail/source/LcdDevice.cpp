#include "Arduino.h"
#include "LcdDevice.h"
#include "LiquidCrystal.h"

#define backLightPin 8

#define intro 0
#define mainMenuPage1 1
#define mainMenuPage2 2
#define SimpleMove 3
#define SmartSequencePage1 4
#define SmartSequencePage2 5
#define SmartSequencePage3 6
#define SmartSequencePage4 7
#define SequenceBasicPage1 8
#define SequenceBasicPage2 9
#define SequenceBasicPage3 10
#define ButtonDebug 11

// initialize the library with the numbers of the interface pins
//LiquidCrystal LCD(2, 3, 4, 5, 6, 7);

LcdDevice::LcdDevice(LiquidCrystal LCD){
	
	LCD.begin(16,2);
	pinMode(backLightPin, OUTPUT);
	digitalWrite(backLightPin, HIGH);
	LCD.clear(); 
	LCD.setCursor(0, 0);
	LCD.print("Motorized Camera");
	LCD.setCursor(0, 1); // (column, row)
	LCD.print("v0.1");
	
	manualSpeed = 0;
	manualPosition = 0;
	smartFps = 0;
	smartOutputDuration = 0;
	smartEventDuration = 0;
	samrtMovementRange = 0;
	startFlag = 0;
	currentPage = 0;
}

void LcdDevice::lcdClear(LiquidCrystal LCD){
	LCD.clear();
}

void LcdDevice::lcdRefresh(LiquidCrystal LCD){
	LCD.clear(); 
	LCD.setCursor(0, 0); // (column, row)
	switch (currentPage){
		case intro:
			LCD.setCursor(0, 0);
			LCD.print("Motorized Rail");
			LCD.setCursor(0, 1);
			LCD.print("v0.1");
			break;
		case mainMenuPage1:
			LCD.setCursor(0, 0);
			LCD.print("   Simple Move");
			LCD.setCursor(0, 1);
			LCD.print("   Smart Sequence");
			break;
		case mainMenuPage2:
			LCD.setCursor(0, 0);
			LCD.print("   Smart Sequence");
			LCD.setCursor(0, 1);
			LCD.print("   Basic Sequence");
			break;
		case SimpleMove:
			LCD.setCursor(0, 0);
			LCD.print(" Click to move");
			LCD.setCursor(0, 1);
			LCD.print("<<<<S:xx>>>>P:xx");
			break;
		case SmartSequencePage1:
			LCD.setCursor(0, 0);
			LCD.print("   FPS:xx #");
			LCD.setCursor(0, 1);
			LCD.print("   Output:xxx s");
			break;
		case SmartSequencePage2:
			LCD.setCursor(0, 0);
			LCD.print("   Output:xxx s");
			LCD.setCursor(0, 1);
			LCD.print("   Event:xxx min");
			break;
		case SmartSequencePage3:
			LCD.setCursor(0, 0);
			LCD.print("   Event:xxx min");
			LCD.setCursor(0, 1);
			LCD.print("   Range:xx %");
			break;
		case SmartSequencePage4:
			LCD.setCursor(0, 0);
			LCD.print("   Range:xx %");
			LCD.setCursor(0, 1);
			LCD.print("   Start");
			break;
		case SequenceBasicPage1:
			LCD.setCursor(0, 0);
			LCD.print("   Delay:xx s");
			LCD.setCursor(0, 1);
			LCD.print("   Frames:xxx #");
			break;
		case SequenceBasicPage2:
			LCD.setCursor(0, 0);
			LCD.print("   Frames:xxx #");
			LCD.setCursor(0, 1);
			LCD.print("   Move:xx cm");
			break;
		case SequenceBasicPage3:
			LCD.setCursor(0, 0);
			LCD.print("   Move:xx cm");
			LCD.setCursor(0, 1);
			LCD.print("   Start");
			break;
		case ButtonDebug:
			LCD.setCursor(0, 0);
			LCD.print("Button: ");
			LCD.print(lcdButton);
			LCD.setCursor(0, 1);
			LCD.print("Pressed: ");
			LCD.print(lcdPressed);
			break;
		default:
			break;
	}
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