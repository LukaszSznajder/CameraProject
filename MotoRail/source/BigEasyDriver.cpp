#include "Arduino.h"
#include "BigEasyDriver.h"

//Acceleration available, ramp up and ramp down 200 steps. If move = 600 steps, no acceleration.

#define pi 3.14159265359

#define distRot 5.093
#define steepsPerRev 6400
#define gearRadius 0.7958

bool _checkFlag;
int _stepCount;

#define clk 16000000
#define n 8
#define stSpeed 7000
#define ramp 0.1
#define rampStep 200

StepperControl::StepperControl(int dirPin, int stepPin){
	pinMode(dirPin, OUTPUT);
	pinMode(stepPin, OUTPUT);
	_dirPin = dirPin;
	_invDir = 1;
	_stepPin = stepPin;
	_dir = true;
	_lineSpeed = 1;
	_debugMode = false;
}

void StepperControl::doStep(double steps){

	float inc;

    digitalWrite(_dirPin,_dir);
    delay(50);

    float rampSteps = rampStep;
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
    	digitalWrite(_stepPin, HIGH);
    	delayMicroseconds(delayPeriod);
    	digitalWrite(_stepPin, LOW);
    	delayMicroseconds(delayPeriod);
    	rampPeriod = rampPeriod + inc;
    	delayPeriod = round(rampPeriod);
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

void StepperControl::doRev(float rev){
	if(_debugMode){
		Serial.print(" revolutions: "); Serial.println(rev);
	}
	double steps = rev * steepsPerRev;
	StepperControl::doStep(steps);
}

void StepperControl::doMove(float distance){
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
	StepperControl::doRev(rev);
}

void StepperControl::doDeg(float deg){
	float rev = deg/360;
	StepperControl::doRev(rev);
}

void StepperControl::setLineSpeed(float lineSpeed){
	_lineSpeed = lineSpeed;
}

void StepperControl::setDirection(bool dir){
	_dir = dir;
}

void StepperControl::invDirection(int invDir){
	_invDir = invDir;
}

void StepperControl::setDebugMode(boolean debug){
	_debugMode = debug;
}

void StepperControl::setSps(int sps){
	_sps = sps;
}

float StepperControl::convertStepsToDistance(double steps){
	float distance = 0;
	
	distance = (steps*2*pi*gearRadius)/steepsPerRev;
	return (distance);
}



