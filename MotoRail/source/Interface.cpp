#include "Arduino.h"
#include "Interface.h"
#include "LcdDevice.h"
#include "Buttons.h"
#include "BigEasyDriver.h"
#include "BasicSequence.h"

#define lineUp 3
#define lineDown 2
#define right 4
#define left 1
#define accept 6
#define cancel 5

#define rampStepsSimpleMove 300

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

#define mainMenu 11
#define SimpleMoveMenu 12
#define SmartSequenceMenu 13
#define SequenceBasicMenu 14

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
	lcd.setContent();
	lcd.lcdRefresh(LCD);
}

void Interface::clearAll(){
	//lcd.lcdClear();
}

void Interface::debug(){
	//lcd.lcdButton = btn.button;
	//lcd.lcdPressed = lcd.currentPage;
	//lcd.lcdRefresh(LCD);
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
	switch (_button){
// lineDown  	
// (btn: 2)
// if on First Page or on Last Page and cursor Position is Not 1 move cursor but don't skip line
// if cursor position is 1 Move Page Down
		case lineDown: //(btn: 2)
			lcd.moveLineDown();
			lcd.lcdRefresh(LCD);
			_button = 0;
			break;
		case lineUp: //(btn: 3)
			lcd.moveLineUp();
			lcd.lcdRefresh(LCD);
			_button = 0;
			break;			
		case left: //(btn: 1)
			lcd.decrementParameters();
			_button = 0;
			lcd.lcdRefresh(LCD);
			break;
		case right: //(btn: 4)
			lcd.incrementParameters();
			_button = 0;	
			lcd.lcdRefresh(LCD);																																			
			break;
//ACCEPT//
		case accept: //(btn: 6)
			switch (lcd.currentMenu){
				case  mainMenu:
					lcd.storeMenu();
					lcd.levelDown();
					break;
	//SMART//
				case  SmartSequenceMenu:
					if (lcd.cursorLine == 5){ 
						digitalWrite(ledPin, HIGH);
						motor = basicSequence.runSmartSequence(lcd.parameters, motor);
					}
					break;
	//BASIC//
				case  SequenceBasicMenu:
					if(lcd.cursorLine == 4){
						digitalWrite(ledPin, HIGH);
						motor = basicSequence.runBasicSequence(lcd.parameters, motor);
					}
					break;
	//SIMPLE//
				case  SimpleMoveMenu:
					motor.setRampSteps(rampStepsSimpleMove);
					motor.moveTime = 0;
					motor.setSps(lcd.parameters.manualSpeed);
					motor.doAbsolutePercent(lcd.parameters.manualPercent);
					break;
				default:
					break;
				}
			_button = 0;
			lcd.lcdRefresh(LCD);
			break;		
		case cancel: //  (btn: 5)
			lcd.restoreMenu();
			_button = 0;
			lcd.lcdRefresh(LCD);
			break;
		default:
			break;
	}
}

void Interface::buttonsRefresh(){
	_button = btn.scanButtons();
}

void Interface::updateMotorInstructions(){

}

