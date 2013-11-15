#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"

class Buttons{
public:
	Buttons();
	void scanButtons();
	int button;
	int pressed;
	
private:
	int _whichButton(int btnVal);
	long int _pressedTime;
};

#endif