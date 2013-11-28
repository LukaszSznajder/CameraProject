#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"
#include "LcdDevice.h"

class Buttons{
public:
	Buttons();
	int scanButtons();
	int pressed;
	int multipleClicks;
	long multiClickTime;
	
private:
	int _whichButton(int btnVal);
	long int _pressedTime;
};

#endif