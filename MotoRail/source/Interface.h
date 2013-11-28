#ifndef Interface_h
#define Interface_h

#include "Arduino.h"
#include "Parameters.h"
#include "BasicSequence.h"


class Interface {
public:
	Interface();
	BasicSequence basicSequence;
	void interfaceRefresh();
	void buttonsRefresh();
	void clearAll();
	void debug();
	void updateMotorInstructions();
private:
	int _button;
};

#endif