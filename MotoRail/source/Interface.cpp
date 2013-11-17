#include "Arduino.h"
#include "Interface.h"
#include "LcdDevice.h"
#include "Buttons.h"
#include "BigEasyDriver.h"

#define lineUp 3
#define lineDown 2
#define right 4
#define left 1
#define accept 6
#define cancel 5

#define rampStepsSimpleMove 500

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
#define ledPin 13
#define incrementSize 1

#define dirPin 19
#define stepPin 18

#define noDebug false

BigEasyDriver motor(dirPin, stepPin);

Buttons btn;

LiquidCrystal LCD(2, 3, 4, 5, 6, 7);
LcdDevice lcd(LCD);

Interface::Interface(){
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
	LCD.begin(16,2);
	LCD.noCursor();
	lcd.currentPage = mainMenuPage1;
	lcd.cursorLine = 0;
	lcd.lcdRefresh(LCD);
}

void Interface::clearAll(){
	//lcd.lcdClear();
}

void Interface::debug(){
	lcd.lcdButton = btn.button;
	lcd.lcdPressed = lcd.currentPage;
	lcd.lcdRefresh(LCD);
}

/* Interface Navigation:

The following pages are available in the menu:

Page Name		    | Page Number
-------------------------------
intro 				|	0
mainMenuPage1 		|	1
mainMenuPage2 		|	2
SimpleMove 			|	3
SmartSequencePage1 	|	4
SmartSequencePage2 	|	5
SmartSequencePage3 	|	6
SmartSequencePage4 	|	7
SequenceBasicPage1 	|	8
SequenceBasicPage2 	|	9
SequenceBasicPage3 	|	10
ButtonDebug 		|	11

Switch Case condition is used to interpret navigation intention of the user.
There are 6 buttons on the panel for user to click:

- lineUp 		(btn: 3)
- lineDown 		(btn: 2)
- right 		(btn: 4)
- left 			(btn: 1)
- accept 		(btn: 6)
- back/cancel 	(btn: 5)

Depending on the what the current page is (currentPage) and it's properties like, 
fistPage & lastPage of the currentPage, the user can navigate up and down, 
accept selection or mave back/cancel.

Page 1:
-------------------------------------------------------
cursorPosition = 0 -> -(cursorLine = 1) currentPage = 1
cursorPosition = 1 ->  (cursorLine = 2) 
-------------------------------------------------------
Page 2:	
-------------------------------------------------------			   
cursorPosition = 0 ->  (cursorLine = 3)	currentPage = 2 
cursorPosition = 1 ->  (cursorLine = 4)
-------------------------------------------------------
*/
void Interface::interfaceRefresh(){
	switch (btn.button){
// lineDown  	
// (btn: 2)
// if on First Page or on Last Page and cursor Position is Not 1 move cursor but don't skip line
// if cursor position is 1 Move Page Down
		case lineDown:
			if(lcd.cursorPosition!=1){
				lcd.cursorPosition = 1;		
				lcd.cursorLine = lcd.cursorLine + 1;
				lcd.lcdRefresh(LCD);
			} else if(lcd.currentPage < lcd.lastPage){
				lcd.cursorPosition = 0;
				lcd.currentPage = lcd.currentPage + 1;
				lcd.cursorLine = lcd.cursorLine + 1;
				lcd.lcdRefresh(LCD);
			}
			btn.button = 0;
			break;
// lineUp
//(btn: 3)
		case lineUp:
			if(lcd.cursorPosition!=0){
				lcd.cursorPosition = 0;
				lcd.cursorLine = lcd.cursorLine - 1;
				lcd.lcdRefresh(LCD);
			} else if(lcd.currentPage > lcd.firstPage){
				lcd.cursorPosition= 1;
				lcd.currentPage = lcd.currentPage - 1; 
				lcd.cursorLine = lcd.cursorLine - 1;
				lcd.lcdRefresh(LCD);
			}
			btn.button = 0;
			break;
//  left 			
//(btn: 1)

		case left:
// Simple Move
			if(lcd.currentPage==SimpleMove && lcd.cursorPosition==0)
				lcd.manualSpeed = lcd.manualSpeed - 500;
			else if(lcd.currentPage==SimpleMove && lcd.cursorPosition==1)
				lcd.manualPercent = lcd.manualPercent - 5;
// Smart Sequence
			else if(lcd.currentPage==SmartSequencePage1 && lcd.cursorPosition==0)
				lcd.smartFps = lcd.smartFps - incrementSize; 
			else if(lcd.currentPage==SmartSequencePage1 && lcd.cursorPosition==1)
				lcd.smartOutputDuration = lcd.smartOutputDuration - incrementSize;
			else if(lcd.currentPage==SmartSequencePage2 && lcd.cursorPosition==0)
				lcd.smartEventDuration = lcd.smartEventDuration - incrementSize;
			else if(lcd.currentPage==SmartSequencePage2 && lcd.cursorPosition==1)
				lcd.samrtMovementRange = lcd.samrtMovementRange - incrementSize;
// Basic Sequence	
			else if(lcd.currentPage==SequenceBasicPage1 && lcd.cursorPosition==0)
				lcd.basicMoveDelay = lcd.basicMoveDelay - incrementSize;
			else if(lcd.currentPage==SequenceBasicPage1 && lcd.cursorPosition==1)
				lcd.basicMoveFrames = lcd.basicMoveFrames - incrementSize;
			else if(lcd.currentPage==SequenceBasicPage2 && lcd.cursorPosition==0)
				lcd.basicMoveRange = lcd.basicMoveRange - incrementSize;
			btn.button = 0;
			lcd.lcdRefresh(LCD);
			break;
// right 			
//(btn: 4)
		case right:
// Simple Move
			if(lcd.currentPage==SimpleMove && lcd.cursorPosition==0)
				lcd.manualSpeed = lcd.manualSpeed + 500;
			else if(lcd.currentPage==SimpleMove && lcd.cursorPosition==1)
				lcd.manualPercent = lcd.manualPercent + 5;
// Smart Sequence				
			else if(lcd.currentPage==SmartSequencePage1 && lcd.cursorPosition==0)
				lcd.smartFps = lcd.smartFps + incrementSize; 			
			else if(lcd.currentPage==SmartSequencePage1 && lcd.cursorPosition==1)
				lcd.smartOutputDuration = lcd.smartOutputDuration + incrementSize;
			else if(lcd.currentPage==SmartSequencePage2 && lcd.cursorPosition==0)
				lcd.smartEventDuration = lcd.smartEventDuration + incrementSize;
			else if(lcd.currentPage==SmartSequencePage2 && lcd.cursorPosition==1)
				lcd.samrtMovementRange = lcd.samrtMovementRange + incrementSize;
// Basic Sequence	
			else if(lcd.currentPage==SequenceBasicPage1 && lcd.cursorPosition==0)
				lcd.basicMoveDelay = lcd.basicMoveDelay + incrementSize;
			else if(lcd.currentPage==SequenceBasicPage1 && lcd.cursorPosition==1)
				lcd.basicMoveFrames = lcd.basicMoveFrames + incrementSize;
			else if(lcd.currentPage==SequenceBasicPage2 && lcd.cursorPosition==0)
				lcd.basicMoveRange = lcd.basicMoveRange + incrementSize;
			btn.button = 0;	
			lcd.lcdRefresh(LCD);																																			
			break;
// accept 			
//(btn: 6)
/*

MAIN MENU Page 1:
- Simple Move
- Smart Sequence
MAIN MENU Page 2:
- Sequence Basic

*/
		case accept:
			switch (lcd.currentPage){
//MAIN MENU Page 1
				case  mainMenuPage1:
					lcd.previousPage = lcd.currentPage;
					lcd.previousCursorLine = lcd.cursorLine;
					lcd.previousCursorPosition = lcd.cursorPosition;
					switch (lcd.cursorPosition){
	//Simple Move
						case 0: 
							lcd.currentPage = SimpleMove;
							lcd.cursorPosition = 0;
							break;
	//Smart Sequence
						case 1: 
							lcd.currentPage = SmartSequencePage1;
							lcd.cursorPosition = 0;
							break;
						default: break;
					}
					break;
//MAIN MENU Page 2
				case  mainMenuPage2:
					lcd.previousPage = lcd.currentPage;
					lcd.previousCursorLine = lcd.cursorLine;
					lcd.previousCursorPosition = lcd.cursorPosition;
					switch (lcd.cursorPosition){
	//Sequence Basic
						case 0: 
							lcd.currentPage = SequenceBasicPage1;
							lcd.cursorPosition = 0;
							break;
	//None
						case 1:
							break;
						default: break;
					}
					break;
	//Simple Move
				case  SimpleMove:
					motor.setRampSteps(rampStepsSimpleMove);
					motor.setSps(lcd.manualSpeed);
					motor.doAbsolutePercent(lcd.manualPercent);
					break;
				default:
					break;
				}
			btn.button = 0;
			lcd.lcdRefresh(LCD);
			break;
// back/cancel 		
//  (btn: 5)
		case cancel:
			lcd.currentPage = lcd.previousPage;
			lcd.cursorLine = lcd.previousCursorLine;
			lcd.cursorPosition = lcd.previousCursorPosition;
			btn.button = 0;
			lcd.lcdRefresh(LCD);
			break;
		default:
			break;
	}
}


void Interface::buttonsRefresh(){
	btn.scanButtons();
}

void Interface::updateMotorInstructions(){

}

