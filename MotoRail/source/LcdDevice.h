#ifndef LcdDevice_h
#define LcdDevice_h
#include "LiquidCrystal.h"
#include "Parameters.h"

#include "Arduino.h"

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

class LcdDevice{
public:

	Parameters parameters;
	LcdDevice(LiquidCrystal LCD);
	void lcdRefresh(LiquidCrystal LCD);
	void zeroValues();
	void lcdClear(LiquidCrystal LCD);
	void setContent();
	void setBluetoothValue(float value);
	
	bool startFlag;
	int lcdButton;
	int lcdPressed;
	bool forceRefresh;
	
	int cursorLine;
	int cursorPosition;
	int currentPage;
	int currentMenu;
	int lastPage;
	int firstPage;
	
	int previousPage;
	int previousCursorLine;
	int previousCursorPosition;
	
	void incrementParameters();
	void decrementParameters();
	
	void moveLineDown();
	void moveLineUp();
	void levelDown();
	void levelUp();
	void storeMenu();
	void restoreMenu();

private:
	int _previousPage;
	int _previousCursorLine;
	
};

//INTRO (Pages: 1)


#endif
