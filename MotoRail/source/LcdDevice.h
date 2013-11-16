#ifndef LcdDevice_h
#define LcdDevice_h
#include "LiquidCrystal.h"

#include "Arduino.h"

class LcdDevice{
public:
	LcdDevice(LiquidCrystal LCD);
	void lcdRefresh(LiquidCrystal LCD);
	void zeroValues();
	void lcdClear(LiquidCrystal LCD);
	int manualSpeed;
	int manualPosition;
	int smartFps;
	int smartOutputDuration;
	int smartEventDuration;
	int samrtMovementRange;
	int basicMoveDelay;
	int basicMoveFrames;
	int basicMoveRange;
	
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
