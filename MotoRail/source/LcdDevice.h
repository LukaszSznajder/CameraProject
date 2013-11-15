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
	int currentPage;
	int manualSpeed;
	int manualPosition;
	int smartFps;
	int smartOutputDuration;
	int smartEventDuration;
	int samrtMovementRange;
	bool startFlag;
	int lcdButton;
	int lcdPressed;
private:

};

#endif
