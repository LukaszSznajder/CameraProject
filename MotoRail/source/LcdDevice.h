#ifndef LcdDevice_h
#define LcdDevice_h
#include "LiquidCrystal.h"
#include "Parameters.h"

#include "Arduino.h"

class LcdDevice{
public:

	Parameters parameters;
	LcdDevice(LiquidCrystal LCD);
	void lcdRefresh(LiquidCrystal LCD);
	void zeroValues();
	void lcdClear(LiquidCrystal LCD);
	
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


#endif
