#ifndef Interface_h
#define Interface_h

#include "Arduino.h"
#include "motorInstructions.h"

class Interface {
public:
	Interface();
	void interfaceRefresh();
	void buttonsRefresh();
	void clearAll();
	void debug();
	void updateMotorInstructions();
	
private:
};
#endif