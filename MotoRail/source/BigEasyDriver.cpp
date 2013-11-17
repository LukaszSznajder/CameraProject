#include "Arduino.h"
#include "BigEasyDriver.h"

//Acceleration available, ramp up and ramp down 200 steps. If move = 600 steps, no acceleration.

#define pi 3.14159265359

#define debugMode true

#define distRot 5.093
#define steepsPerRev 6400
#define gearRadius 0.7958
#define fullLength 72
#define fullSpeed 4000

bool _checkFlag;
int _stepCount;

#define clk 16000000
#define n 8
#define stSpeed 1000
#define ramp 0.1 //Not used.
#define rampStep 500

BigEasyDriver::BigEasyDriver(int dirPin, int stepPin){
	pinMode(dirPin, OUTPUT);
	pinMode(stepPin, OUTPUT);
	_dirPin = dirPin;
	_invDir = -1;
	_stepPin = stepPin;
	_dir = true;
	_lineSpeed = 1;
	_debugMode = debugMode;
	_fullLength = fullLength;
	_sps = 0;
	_currentLocation = 0;
	_ramp = ramp;
	_rampStep = rampStep; 
}

void BigEasyDriver::doStep(double steps){


	if(debugMode){
		Serial.print("start_currentLocation: "); Serial.println(_currentLocation);
	}
	float inc;
	if(_dir)
		_currentLocation = _currentLocation - BigEasyDriver::convertStepsToDistance(steps);
	else
		_currentLocation = _currentLocation + BigEasyDriver::convertStepsToDistance(steps);
	if(debugMode){
		Serial.print("end_currentLocation: "); Serial.println(_currentLocation);
		Serial.println(" ******************************");
	}

    digitalWrite(_dirPin,_dir);
    delay(50);

    float rampSteps = rampStep;
    //float rampSteps = steps * ramp;
    float startSpeed = stSpeed;

    float startPeriod = (1000000 * 1/startSpeed);
    float rampPeriod = startPeriod;
    double steadySteps = steps - rampSteps * 2;
    float steadyPeriod = (1000000 * 1/_sps);

    // if less steps then 3x ramp steps
    if(steps < rampSteps*3){
    	steadyPeriod = startPeriod;
    	steadySteps = steps;
    	rampSteps = 0;
	}

    // if the requested speed is less than the start speed
    if(_sps < startSpeed){
		startSpeed = _sps ;
	}

    int delayPeriod = startPeriod;

    inc = (steadyPeriod - startPeriod)/(rampSteps);

    // RAMP UP
    if(_debugMode){
    	Serial.print(" steps: "); Serial.println(steps);
    	Serial.println(" ");
    	Serial.print(" Start speed: "); Serial.print(startSpeed); Serial.print(" Full speed: "); Serial.println(_sps);
    	Serial.println(" ------------------------------");
    	Serial.println(" Ramping up");
    	Serial.print(" steps: "); Serial.println(rampSteps);
    	Serial.print(" start delay per step: "); Serial.println(rampPeriod);
    	Serial.print(" delay increment: "); Serial.println(inc);
    }
    for(int i = 0;i<rampSteps;i++){
		for(int k=0;k<=1;k=k+0.1){
		
			inc = (inc - startPeriod)/(10);
		
			digitalWrite(_stepPin, HIGH);
			delayMicroseconds(delayPeriod);
			digitalWrite(_stepPin, LOW);
			delayMicroseconds(delayPeriod);
			rampPeriod = rampPeriod + inc*k;
			delayPeriod = round(rampPeriod);
		}
    }

    // STEADY SPEED
    if(_debugMode){
    	Serial.println(" ------------------------------");
        Serial.println(" Constant speed");
        Serial.print(" steps: "); Serial.println(steadySteps);
        Serial.print(" Full speed: "); Serial.println(_sps);
        Serial.print(" Constant delay per step: "); Serial.println(rampPeriod);
    }
    for(long i = 0;i<steadySteps;i++){
    	digitalWrite(_stepPin, HIGH);
    	delayMicroseconds(steadyPeriod);
    	digitalWrite(_stepPin, LOW);
    	delayMicroseconds(steadyPeriod);
    }

    //RUMP DOWN
    if(_debugMode){
    	Serial.println(" ------------------------------");
    	Serial.println(" Ramping down");
    	Serial.print(" steps: "); Serial.println(rampSteps);
    }
    for(int i = 0;i<rampSteps;i++){
    	digitalWrite(_stepPin, HIGH);
    	delayMicroseconds(delayPeriod);
    	digitalWrite(_stepPin, LOW);
    	delayMicroseconds(delayPeriod);
    	rampPeriod = rampPeriod - inc;
    	delayPeriod = round(rampPeriod);
    }
    if(_debugMode){
        Serial.print(" End delay: "); Serial.println(rampPeriod);
        Serial.println(" ");
    }
 }

void BigEasyDriver::doRev(float rev){
	if(_debugMode){
		Serial.print(" revolutions: "); Serial.println(rev);
	}
	double steps = rev * steepsPerRev;
	BigEasyDriver::doStep(steps);
}

void BigEasyDriver::doDeg(float deg){
	float rev = deg/360;
	BigEasyDriver::doRev(rev);
}

void BigEasyDriver::doMove(float distance){
	if(_debugMode){
		Serial.print(" distance: "); Serial.println(distance);
	}
	if((distance)<0){
		distance = distance * (-1);
		if(_invDir==1)
			_dir = false; //CCW
		else
			_dir = true;
	}else
		if(_invDir==1)
			_dir = true;
		else
			_dir = false;
	float rev = distance * 1/(2*pi*gearRadius);
	BigEasyDriver::doRev(rev);
}

void BigEasyDriver::doAbsolutePercent(int percent){
	float _moveBy;
	_moveBy = (fullLength * percent/100 )  - _currentLocation;
	if(_debugMode){
		Serial.println(" ------------------------------");
		Serial.println("Absolute Percent Move"); 
		Serial.println(" ******************************");
		Serial.print("		percent: "); Serial.println(percent);
		
	}
	BigEasyDriver::doMove(_moveBy);
}

void BigEasyDriver::setLineSpeed(float lineSpeed){
	_lineSpeed = lineSpeed;
}

void BigEasyDriver::setDirection(bool dir){
	_dir = dir;
}

void BigEasyDriver::invDirection(int invDir){
	_invDir = invDir;
}

void BigEasyDriver::setDebugMode(boolean debug){
	_debugMode = debug;
}

void BigEasyDriver::setSps(int sps){
	_sps = sps;
}

float BigEasyDriver::convertStepsToDistance(double steps){
	float distance = 0;
	distance = (steps*2*pi*gearRadius)/steepsPerRev;
	return (distance);
}

float BigEasyDriver::convertDegToDistance(double deg){
	float distance = 0;
	distance = (deg/360)*2*pi*gearRadius;
	return (distance);
}

float BigEasyDriver::convertRevToDistance(double rev){
	float distance = 0;
	distance = rev*2*pi*gearRadius;
	return (distance);
}

void BigEasyDriver::setRampSteps(int setRampSteps){
	_rampStep = setRampSteps; 
} 


