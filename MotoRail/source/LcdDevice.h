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

struct ScreenContent{
		String menu1name;
		String menu1page1line1;
		String menu1page1line2;
		String menu2name;
		String menu2page1line1;
		String menu2page1line2;
		String menu2page2line1;
		//myScreen.menu2.page2.line2 = " ";
		//SIMPLE MOVE (Pages: 1)
		String menu3name;
		String menu3page1line1;
		String menu3page1line2;
		//SMART SEQUENCE (Pages: 4)
		String menu4name;
		String menu4page1line1;
		String menu4page1line2;
		String menu4page2line1;
		String menu4page2line2;
		String menu4page3line1;
		//myScreen.menu4.page3.line2 = " ";
		//BASIC SEQUENCE (Pages: 3)
		String menu5name;
		String menu5page1line1;
		String menu5page1line2;
		String menu5page2line1;
		String menu5page2line2;
};

class LcdDevice{
public:

	Parameters parameters;
	LcdDevice(LiquidCrystal LCD);
	void lcdRefresh(LiquidCrystal LCD);
	void zeroValues();
	void lcdClear(LiquidCrystal LCD);
	void setContent();
	
	bool startFlag;
	int lcdButton;
	int lcdPressed;
	bool forceRefresh;
	
	int cursorLine;
	int cursorPosition;
	
	int currentPage;
	int lastPage;
	int firstPage;
	
	int previousPage;
	int previousCursorLine;
	int previousCursorPosition;

private:
	int _previousPage;
	int _previousCursorLine;
};

//INTRO (Pages: 1)


#endif
