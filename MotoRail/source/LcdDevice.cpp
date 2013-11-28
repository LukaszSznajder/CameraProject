#include "Arduino.h"
#include "LcdDevice.h"
#include "LiquidCrystal.h"
#include "Parameters.h"
 
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
#define incrementSize 1
#define mainMenu 11
#define SimpleMoveMenu 12
#define SmartSequenceMenu 13
#define SequenceBasicMenu 14

//INTRO (Pages: 1)
#define	myScreenmenu1name "Intro"
#define	myScreenmenu1page1line1 "Motorized Rail"
#define	myScreenmenu1page1line2 "v0.1"
//MAIN MENU (Pages: 2)
#define	myScreenmenu2name "Main Menu"
	//page1
#define	myScreenmenu2page1line1 " Simple Move"
#define	myScreenmenu2page1line2 " Smart Sequence"
	//page2
#define	myScreenmenu2page2line1 " Basic Sequence"
	//myScreen.menu2.page2.line2 = " ";
//SIMPLE MOVE (Pages: 1)
#define	myScreenmenu3name "Simple Move"
	//page1
#define	myScreenmenu3page1line1 " Speed:"
#define	myScreenmenu3page1line2 " Position:"
//SMART SEQUENCE (Pages: 4)
#define	myScreenmenu4name "Smart Sequence"
	//page1
#define	myScreenmenu4page1line1 " FPS:"
#define	myScreenmenu4page1line2 " Output:"
	//page2
#define	myScreenmenu4page2line1 " Event:"
#define	myScreenmenu4page2line2 " Range:"
	//page3
#define	myScreenmenu4page3line1 " Start"
	//myScreen.menu4.page3.line2 = " ";
//BASIC SEQUENCE (Pages: 3)
#define	myScreenmenu5name "Basic Sequence"
	//page1
#define	myScreenmenu5page1line1 " Delay:"
#define	myScreenmenu5page1line2 " Frames:"
	//page2
#define	myScreenmenu5page2line1 " Move:"
#define	myScreenmenu5page2line2 " Start"
 
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
	 
	parameters.manualPercent = 0;
	parameters.smartFps = 0;
	parameters.manualSpeed = 4000;
	parameters.smartOutputDuration = 0;
	parameters.smartEventDuration = 0;
	parameters.samrtMovementRange = 0;
	parameters.basicMoveDelay = 0;
	parameters.basicMoveFrames = 0;
	parameters.basicMoveRange = 0;
	startFlag = 0;
	currentPage = 0;
	currentMenu = mainMenu;
	cursorLine = 0;
	forceRefresh = false;
}
 
void LcdDevice::lcdClear(LiquidCrystal LCD){
	LCD.clear();
}
 
void LcdDevice::setContent(){

}
 
void LcdDevice::lcdRefresh(LiquidCrystal LCD){
	 
	LCD.clear();
	switch (currentPage){
//1 INTRO (Pages: 1)
		case intro:
			LCD.setCursor(0, 0); // (column, row)
			LCD.print(myScreenmenu1page1line1);
			LCD.setCursor(0, 1);
			LCD.print(myScreenmenu1page1line2);
			lastPage = intro;
			firstPage = intro;
		break;
//2 MAIN MENU (Pages: 2)
		case mainMenuPage1:
			LCD.setCursor(0, 0); // (column, row)
			LCD.print(myScreenmenu2page1line1);
			LCD.setCursor(0, 1);
			LCD.print(myScreenmenu2page1line2);
			LCD.setCursor(cursorColumn, cursorPosition);
			LCD.print(">");
			firstPage = mainMenuPage1;
			lastPage = mainMenuPage2;
			break;
		case mainMenuPage2:
			LCD.setCursor(0, 0); // (column, row)
			LCD.print(myScreenmenu2page2line1);
			LCD.setCursor(0, 1);
			LCD.print(" ");
			LCD.setCursor(cursorColumn, cursorPosition);
			LCD.print(">");
			firstPage = mainMenuPage1;
			lastPage = mainMenuPage2;
			break;
//3 SIMPLE MOVE (Pages: 1)
		case SimpleMove:
			LCD.setCursor(0, 0); // (column, row)
			LCD.print(myScreenmenu3page1line1);
			LCD.print(parameters.manualSpeed);
			LCD.setCursor(0, 1);
			LCD.print(myScreenmenu3page1line2);
			LCD.print(parameters.manualPercent);
			LCD.setCursor(cursorColumn, cursorPosition);
			LCD.print(">");
			firstPage = SimpleMove;
			lastPage = SimpleMove;
			break;
//4 SMART SEQUENCE (Pages: 4)
		case SmartSequencePage1:
			LCD.setCursor(0, 0); // (column, row)
			LCD.print(myScreenmenu4page1line1);
			LCD.print(parameters.smartFps);
			LCD.setCursor(0, 1);
			LCD.print(myScreenmenu4page1line2);
			LCD.print(parameters.smartOutputDuration);
			LCD.setCursor(cursorColumn, cursorPosition);
			LCD.print(">");
			firstPage = SmartSequencePage1;
			lastPage = SmartSequencePage3;
			break;
		case SmartSequencePage2:
			LCD.setCursor(0, 0); // (column, row)
			LCD.print(myScreenmenu4page2line1);
			LCD.print(parameters.smartEventDuration);
			LCD.setCursor(0, 1);
			LCD.print(myScreenmenu4page2line2);
			LCD.print(parameters.samrtMovementRange);
			LCD.setCursor(cursorColumn, cursorPosition);
			LCD.print(">");
			firstPage = SmartSequencePage1;
			lastPage = SmartSequencePage3;
			break;
		case SmartSequencePage3:
			LCD.setCursor(0, 0); // (column, row)
			LCD.print(myScreenmenu4page3line1);
			LCD.setCursor(0, 1);
			LCD.print(" ");
			LCD.setCursor(cursorColumn, cursorPosition);
			LCD.print(">");
			firstPage = SmartSequencePage1;
			lastPage = SmartSequencePage3;
			break;
		case SmartSequencePage4:
			LCD.setCursor(0, 0); // (column, row)
			LCD.print(" ");
			LCD.setCursor(0, 1);
			LCD.print(" ");
			LCD.setCursor(cursorColumn, cursorPosition);
			LCD.print("-");
			break;
//5 BASIC SEQUENCE (Pages: 3)
		case SequenceBasicPage1:
			LCD.setCursor(0, 0); // (column, row)
			LCD.print(myScreenmenu5page1line1);
			LCD.print(parameters.basicMoveDelay);
			LCD.setCursor(0, 1);
			LCD.print(myScreenmenu5page1line2);
			LCD.print(parameters.basicMoveFrames);
			LCD.setCursor(cursorColumn, cursorPosition);
			LCD.print(">");
			firstPage = SequenceBasicPage1;
			lastPage = SequenceBasicPage2;
			break;
		case SequenceBasicPage2:
			LCD.setCursor(0, 0); // (column, row)
			LCD.print(myScreenmenu5page2line1);
			LCD.print(parameters.basicMoveRange);
			LCD.setCursor(0, 1);
			LCD.print(myScreenmenu5page2line2);
			LCD.setCursor(cursorColumn, cursorPosition);
			LCD.print(">");
			firstPage = SequenceBasicPage1;
			lastPage = SequenceBasicPage2;
			break;
		case SequenceBasicPage3:
			LCD.setCursor(0, 0); // (column, row)
			LCD.print(" ");
			LCD.setCursor(0, 1);
			LCD.print(" ");
			LCD.setCursor(cursorColumn, cursorPosition);
			LCD.print(">");
			break;
		default:
		break;
	}
//	}
}
 
void LcdDevice::zeroValues(){
	parameters.smartFps = 0;
	parameters.smartOutputDuration = 0;
	parameters.smartEventDuration = 0;
	parameters.samrtMovementRange = 0;
	parameters.basicMoveDelay = 0;
	parameters.basicMoveFrames = 0;
	parameters.basicMoveRange = 0;
	startFlag = 0;
}

void LcdDevice::incrementParameters(){

	if(currentPage==SimpleMove && cursorPosition==0)
				parameters.manualSpeed = parameters.manualSpeed + 500;
			else if(currentPage==SimpleMove && cursorPosition==1)
				parameters.manualPercent = parameters.manualPercent + 5;
// Smart Sequence				
			else if(currentPage==SmartSequencePage1 && cursorPosition==0)
				parameters.smartFps = parameters.smartFps + incrementSize; 			
			else if(currentPage==SmartSequencePage1 && cursorPosition==1)
				parameters.smartOutputDuration = parameters.smartOutputDuration + incrementSize;
			else if(currentPage==SmartSequencePage2 && cursorPosition==0)
				parameters.smartEventDuration = parameters.smartEventDuration + incrementSize;
			else if(currentPage==SmartSequencePage2 && cursorPosition==1)
				parameters.samrtMovementRange = parameters.samrtMovementRange + incrementSize;
// Basic Sequence	
			else if(currentPage==SequenceBasicPage1 && cursorPosition==0)
				parameters.basicMoveDelay = parameters.basicMoveDelay + incrementSize;
			else if(currentPage==SequenceBasicPage1 && cursorPosition==1)
				parameters.basicMoveFrames = parameters.basicMoveFrames + incrementSize;
			else if(currentPage==SequenceBasicPage2 && cursorPosition==0)
				parameters.basicMoveRange = parameters.basicMoveRange + incrementSize;
}


void LcdDevice::decrementParameters(){
	if(currentPage==SimpleMove && cursorPosition==0)
				parameters.manualSpeed = parameters.manualSpeed - 500;
			else if(currentPage==SimpleMove && cursorPosition==1)
				parameters.manualPercent = parameters.manualPercent - 5;
// Smart Sequence
			else if(currentPage==SmartSequencePage1 && cursorPosition==0)
				parameters.smartFps = parameters.smartFps - incrementSize; 
			else if(currentPage==SmartSequencePage1 && cursorPosition==1)
				parameters.smartOutputDuration = parameters.smartOutputDuration - incrementSize;
			else if(currentPage==SmartSequencePage2 && cursorPosition==0)
				parameters.smartEventDuration = parameters.smartEventDuration - incrementSize;
			else if(currentPage==SmartSequencePage2 && cursorPosition==1)
				parameters.samrtMovementRange = parameters.samrtMovementRange - incrementSize;
// Basic Sequence	
			else if(currentPage==SequenceBasicPage1 && cursorPosition==0)
				parameters.basicMoveDelay = parameters.basicMoveDelay - incrementSize;
			else if(currentPage==SequenceBasicPage1 && cursorPosition==1)
				parameters.basicMoveFrames = parameters.basicMoveFrames - incrementSize;
			else if(currentPage==SequenceBasicPage2 && cursorPosition==0)
				parameters.basicMoveRange = parameters.basicMoveRange - incrementSize;
}

void LcdDevice::moveLineDown(){
	if(cursorPosition!=1){
				cursorPosition = 1;		
				cursorLine = cursorLine + 1;
			} else if(currentPage < lastPage){
				cursorPosition = 0;
				currentPage = currentPage + 1;
				cursorLine = cursorLine + 1;
			}
}

void LcdDevice::moveLineUp(){
	if(cursorPosition!=0){
				cursorPosition = 0;
				cursorLine = cursorLine - 1;
			} else if(currentPage > firstPage){
				cursorPosition= 1;
				currentPage = currentPage - 1; 
				cursorLine = cursorLine - 1;
			}
}

void LcdDevice::levelDown(){
	
	cursorLine = 1;
	if(currentPage == mainMenuPage1){
	//Simple Move
		switch(cursorPosition){
			case 0: 
				currentPage = SimpleMove;
				currentMenu = SimpleMoveMenu;
				cursorPosition = 0;
				break;
	//Smart Sequence
			case 1: 
				currentPage = SmartSequencePage1;
				currentMenu = SmartSequenceMenu;
				cursorPosition = 0;
				break;
			default: break;
		}
	}
	else if(currentPage == mainMenuPage2){
		switch(cursorPosition){
			//Sequence Basic
			case 0: 
				currentPage = SequenceBasicPage1;
				currentMenu = SequenceBasicMenu;
				cursorPosition = 0;
				break;
			//None
			case 1:
				break;
			default: break;
		}
	}
}

void LcdDevice::levelUp(){

}

void LcdDevice::storeMenu(){
	previousPage = currentPage;
	previousCursorLine = cursorLine;
	previousCursorPosition = cursorPosition;
}

void LcdDevice::restoreMenu(){
	currentPage = previousPage;
	currentMenu = mainMenu;
	cursorLine = previousCursorLine;
	cursorPosition = previousCursorPosition;

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
