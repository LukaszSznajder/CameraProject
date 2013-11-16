#ifndef MotorControl_h
#define MotorControl_h

#include "Arduino.h"
#include "motorInstructions.h"

class MotorControl{
public:
	MotorControl(bool debugMode);
	void Execute(char * instruction, float value);
	void motorExecute(motorInstructions instructions);
	void setCurrentLocation(float currentLocation); //in cm, measured form the motor end
	void setFullLength(float fullLength); //in cm
	void setDebugMode(bool debugMode);
	
private:
	float _currentLocation;
	float _fullLength;
	bool _debugMode;
};

#endif
