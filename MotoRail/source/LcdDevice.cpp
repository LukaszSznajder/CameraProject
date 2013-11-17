#include "Arduino.h"
#include "LcdDevice.h"
#include "LiquidCrystal.h"

#define backLightPin 8

#define cursorColumn 0

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
	
	manualPercent = 0;
	smartFps = 0;
	manualSpeed = 10000;
	smartOutputDuration = 0;
	smartEventDuration = 0;
	samrtMovementRange = 0;
	basicMoveDelay = 0;
	basicMoveFrames = 0;
	basicMoveRange = 0;
	startFlag = 0;
	currentPage = 0;
	cursorLine = 0;
	forceRefresh = false;
}

void LcdDevice::lcdClear(LiquidCrystal LCD){
	LCD.clear();
}

void LcdDevice::lcdRefresh(LiquidCrystal LCD){
		LCD.clear(); 		
		switch (currentPage){
		//INTRO (Pages: 1)
			case intro:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print("Motorized Rail");
				LCD.setCursor(0, 1);
				LCD.print("v0.1");
				lastPage = intro;
				firstPage = intro;
				break;
		//MAIN MENU (Pages: 2)
			case mainMenuPage1:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print(" Simple Move");
				LCD.setCursor(0, 1);
				LCD.print(" Smart Sequence");
				LCD.setCursor(cursorColumn, cursorPosition);
				LCD.print(">");
				firstPage = mainMenuPage1;
				lastPage = mainMenuPage2;
				break;
			case mainMenuPage2:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print(" Basic Sequence");
				LCD.setCursor(0, 1);
				LCD.print("          ");
				LCD.setCursor(cursorColumn, cursorPosition);
				LCD.print(">");
				firstPage = mainMenuPage1;
				lastPage = mainMenuPage2;
				break;
		//SIMPLE MOVE (Pages: 1)
			case SimpleMove:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print(" Speed: ");
				LCD.print(manualSpeed);
				LCD.setCursor(0, 1);
				LCD.print(" Position: ");
				LCD.print(manualPercent);
				LCD.print(" %");
				LCD.setCursor(cursorColumn, cursorPosition);
				LCD.print(">");
				firstPage = SimpleMove;
				lastPage = SimpleMove;
				break;
		//SMART SEQUENCE (Pages: 4)
			case SmartSequencePage1:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print(" FPS:");
				LCD.print(smartFps);
				LCD.print(" #");
				LCD.setCursor(0, 1);
				LCD.print(" Output:");
				LCD.print(smartOutputDuration);
				LCD.print(" s");
				LCD.setCursor(cursorColumn, cursorPosition);
				LCD.print(">");
				firstPage = SmartSequencePage1;
				lastPage = SmartSequencePage3;
				break;
			case SmartSequencePage2:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print(" Event:");
				LCD.print(smartEventDuration);
				LCD.print(" min");
				LCD.setCursor(0, 1);
				LCD.print(" Range:");
				LCD.print(samrtMovementRange);
				LCD.print(" %");
				LCD.setCursor(cursorColumn, cursorPosition);
				LCD.print(">");
				firstPage = SmartSequencePage1;
				lastPage = SmartSequencePage3;
				break;
			case SmartSequencePage3:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print(" Start");
				LCD.setCursor(0, 1);
				LCD.print("      ");
				LCD.setCursor(cursorColumn, cursorPosition);
				LCD.print(">");
				firstPage = SmartSequencePage1;
				lastPage = SmartSequencePage3;
				break;
			case SmartSequencePage4:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print("      ");
				LCD.setCursor(0, 1);
				LCD.print("      ");
				LCD.setCursor(cursorColumn, cursorPosition);
				LCD.print("-");
				break;
		//BASIC SEQUENCE (Pages: 3)
			case SequenceBasicPage1:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print(" Delay:");
				LCD.print(basicMoveDelay);
				LCD.print(" s");
				LCD.setCursor(0, 1);
				LCD.print(" Frames:");
				LCD.print(basicMoveFrames);
				LCD.print(" #");
				LCD.setCursor(cursorColumn, cursorPosition);
				LCD.print(">");
				firstPage = SequenceBasicPage1;
				lastPage = SequenceBasicPage2;
				break;
			case SequenceBasicPage2:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print(" Move:");
				LCD.print(basicMoveRange);
				LCD.print(" cm");
				LCD.setCursor(0, 1);
				LCD.print(" Start");
				LCD.setCursor(cursorColumn, cursorPosition);
				LCD.print(">");
				firstPage = SequenceBasicPage1;
				lastPage = SequenceBasicPage2;
				break;
			case SequenceBasicPage3:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print("      ");
				LCD.setCursor(0, 1);
				LCD.print("      ");
				LCD.setCursor(cursorColumn, cursorPosition);
				LCD.print(">");
				break;
		//BUTTON DEBUG (Pages: 1)
			case ButtonDebug:
				LCD.setCursor(0, 0); // (column, row)
				LCD.print("Button: ");
				LCD.print(lcdButton);
				LCD.setCursor(0, 1);
				LCD.print("Pressed: ");
				LCD.print(lcdPressed);
				LCD.setCursor(cursorColumn, cursorPosition);
				LCD.print(">");
				firstPage = ButtonDebug;
				lastPage = ButtonDebug;
				break;
			default:
				break;
		}
//	}
}

void LcdDevice::zeroValues(){
	smartFps = 0;
	smartOutputDuration = 0;
	smartEventDuration = 0;
	samrtMovementRange = 0;
	basicMoveDelay = 0;
	basicMoveFrames = 0;
	basicMoveRange = 0;
	startFlag = 0;
}

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
//------------
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