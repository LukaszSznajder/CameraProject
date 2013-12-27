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
	void setBluetoothValue(float value);
private:
	int _button;
	int long _currentTime;
	int long _previousTime;
};

#endif