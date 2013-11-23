#include "Arduino.h"
#include "BigEasyDriver.h"

//Acceleration available, ramp up and ramp down 200 steps. If move = 600 steps, no acceleration.

#define pi 3.14159265359

#define distRot 5.093
#define steepsPerRev 6400
#define gearRadius 0.7958
#define distPerStep 0.0007953125 //cm

bool _checkFlag;
int _stepCount;

#define clk 16000000
#define n 8
#define stSpeed 2000
#define ramp 0.1 //Not used
#define rampStep 200
#define maxSpeed 10000

StepperControl::StepperControl(int dirPin, int stepPin){
	pinMode(dirPin, OUTPUT);
	pinMode(stepPin, OUTPUT);
	_dirPin = dirPin;
	_invDir = -1;
	_stepPin = stepPin;
	_dir = true;
	_lineSpeed = 1; //cm/s
	_debugMode = false;
	_sps = maxSpeed;
}

void StepperControl::doStep(double steps){

	float inc;

    digitalWrite(_dirPin,_dir);
    delay(50);
    
    if(_lineSpeed != 0){
		_sps = _lineSpeed/distPerStep;
		Serial.print("_lineSpeed"); Serial.println(_lineSpeed);
		Serial.print("_sps"); Serial.println(_sps);
    }

	_sps = _sps * 2.8;

    float rampSteps = rampStep;
    float startSpeed = stSpeed;

    float startPeriod = (1000000 * 1/startSpeed);
    float rampPeriod = startPeriod;
    double steadySteps = steps - rampSteps * 2;
    float steadyPeriod = (1000000 * 1/_sps);

    // if less steps then 2x ramp steps
    if(steps < rampSteps*2){
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
    
    long int startTime;
    long int finishTime;

    // RAMP UP
    if(_debugMode){
    	Serial.print(" steps: "); Serial.println(steps);
    	Serial.println(" ");
    	Serial.print(" Start speed: "); Serial.print(startSpeed); Serial.print(" Full speed: "); Serial.print(_sps); Serial.println(" steps/s");
    	Serial.println(" ------------------------------");
    	Serial.println(" Ramping up");
    	Serial.print(" steps: "); Serial.println(rampSteps);
    	Serial.print(" Start speed: "); Serial.print(startSpeed); Serial.println(" steps/s");
    	Serial.print(" start delay per step: "); Serial.print(rampPeriod); Serial.println(" microseconds");
    	Serial.print(" delay increment: "); Serial.print(inc); Serial.println(" microseconds");
    }
    
    startTime = millis();
    
    for(int i = 0;i<rampSteps;i++){
    	digitalWrite(_stepPin, HIGH);
    	delayMicroseconds(delayPeriod);
    	digitalWrite(_stepPin, LOW);
    	delayMicroseconds(delayPeriod);
    	rampPeriod = rampPeriod + inc;
    	delayPeriod = round(rampPeriod);
    }
    
    finishTime = millis();
    float acceleration = (1000*(_sps - startSpeed))/((finishTime - startTime));
    Serial.print(" Time: "); Serial.print(finishTime - startTime); Serial.println(" ms");
    Serial.print(" Acceleration: "); Serial.print(acceleration); Serial.println(" steps/s^2");

    // STEADY SPEED
    if(_debugMode){
    	Serial.println(" ------------------------------");
        Serial.println(" Constant speed");
        Serial.print(" steps: "); Serial.println(steadySteps);
        Serial.print(" Full speed: "); Serial.print(_sps); Serial.println(" steps/s");
        Serial.print(" Constant delay per step: "); Serial.print(rampPeriod); Serial.println(" microseconds");   
        Serial.print(" delay increment: "); Serial.print(" 0"); Serial.println(" microseconds");
    }
    
    startTime = millis();
    
    for(long i = 0;i<steadySteps;i++){
    	digitalWrite(_stepPin, HIGH);
    	delayMicroseconds(steadyPeriod);
    	digitalWrite(_stepPin, LOW);
    	delayMicroseconds(steadyPeriod);
    }
    
    finishTime = millis();
    Serial.print(" Time: "); Serial.print(finishTime - startTime); Serial.println(" ms");

    //RAMP DOWN
    if(_debugMode){
    	Serial.println(" ------------------------------");
    	Serial.println(" Ramping down");
    	Serial.print(" steps: "); Serial.println(rampSteps);
    	Serial.print(" End speed: "); Serial.print(startSpeed); Serial.println(" steps/s");
    }
    
    startTime = millis();
    
    for(int i = 0;i<rampSteps;i++){
    	digitalWrite(_stepPin, HIGH);
    	delayMicroseconds(delayPeriod);
    	digitalWrite(_stepPin, LOW);
    	delayMicroseconds(delayPeriod);
    	rampPeriod = rampPeriod - inc;
    	delayPeriod = round(rampPeriod);
    }
    
    finishTime = millis();
    
    if(_debugMode){
        Serial.print(" End delay: "); Serial.println(rampPeriod); Serial.println(" microseconds");
        Serial.print(" delay increment: "); Serial.print(inc); Serial.println(" microseconds");
        Serial.print(" Time: "); Serial.print(finishTime - startTime); Serial.println(" ms");
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



