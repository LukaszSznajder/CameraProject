#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"

class Buttons{
public:
	Buttons();
	void scanButtons();
	int button;
	int pressed;
	int multipleClicks;
	long multiClickTime;
	
private:
	int _whichButton(int btnVal);
	long int _pressedTime;
};

#endif