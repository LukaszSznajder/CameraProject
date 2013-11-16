#include "Arduino.h"
#include "MotorControl.h"
#include "BigEasyDriver.h"

#define pi 3.14159265359
#define dirPin 19
#define stepPin 18
#define gearRadius 0.7958
#define direction -1
#define fullLenght 72
#define steepsPerRev 6400

StepperControl MotorX(dirPin, stepPin);

MotorControl::MotorControl(bool debugMode){
	_fullLength = fullLenght;
	_debugMode = true;
	MotorX.setDebugMode(debugMode);
}

/*
Instructions:
Simple move:

	speed up
	speed down

Smart Move:
	
*/

void MotorControl::Execute(char * instruction, float value){
	if((*instruction == 'M') && (*(instruction + 1) == 'M')){
		_currentLocation = _currentLocation + value;
		if(_debugMode){
			Serial.print("Moving by: "); Serial.println(value);
		}
		MotorX.doMove(value);
	}
	else if((*instruction == 'A') && (*(instruction + 1) == 'P')){
		float moveBy = value/100*_fullLength - _currentLocation;
		_currentLocation = _currentLocation + moveBy;
		if(_debugMode){
			Serial.print("Moving by: "); Serial.println(moveBy);
			Serial.print(" Start location: "); Serial.println(_currentLocation - moveBy);
			Serial.print(" Finish location: "); Serial.println(_currentLocation);
		}
		MotorX.doMove(moveBy);
	}
	else if((*instruction == 'A') && (*(instruction + 1) == 'M')){
			float moveBy = value - _currentLocation;
			_currentLocation = _currentLocation + moveBy;
			MotorX.doMove(moveBy);
	}
	else if((*instruction == 'D') && (*(instruction + 1) == 'R')){
			MotorX.invDirection(value);
			if(_debugMode){
				Serial.print("Direction has been set to"); Serial.println(value);
			}
	}
	else if((*instruction == 'M') && (*(instruction + 1) == 'R')){
		MotorX.setDirection(true);
		_currentLocation = _currentLocation + value * (2*pi*gearRadius);;
		MotorX.doRev(value);
	}
	else if((*instruction == 'H') && (*(instruction + 1) == 'H')){
		_currentLocation = 0;
		if(_debugMode){
			Serial.println("current location = 0");
		}
	}
	else if((*instruction == 'S') && (*(instruction + 1) == 'S')){
		if(_debugMode){
			if(value > 0){
				MotorX.setSps(value);
				Serial.print("Speed set to: ");Serial.println(value);
			}
			else
				Serial.println("Invalid input: Negative speed or zero");
		}
	}
	else if((*instruction == 'M') && (*(instruction + 1) == 'S')){
		_currentLocation = _currentLocation + MotorX.convertStepsToDistance(value);
		MotorX.doStep(value);
	}
	else
		Serial.println("Invalid Instruction");
}

void MotorControl::setFullLength(float fullLength){
	_fullLength = fullLength;
}

void MotorControl::setCurrentLocation(float currentLocation){
	_currentLocation = currentLocation;
}

void MotorControl::setDebugMode(bool debugMode){
	_debugMode = debugMode;
}

void MotorControl::motorExecute(motorInstructions instructions){
	_currentLocation = _currentLocation + MotorX.convertStepsToDistance(100);
	MotorX.setSps(instructions.manualSpeed * 100);
	MotorX.doStep(100);
}

