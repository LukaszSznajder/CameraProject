#ifndef MotorControl_h
#define MotorControl_h

#include "Arduino.h"

class MotorDriver{
public:
	MotorDriver(bool debugMode);
	void Execute(char * instruction, float value);
	void setCurrentLocation(float currentLocation); //in cm, measured form the motor end
	void setFullLength(float fullLength); //in cm
	void setDebugMode(bool debugMode);
private:
	float _currentLocation;
	float _fullLength;
	bool _debugMode;
};

#endif
