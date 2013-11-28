#include "Arduino.h"
#include "BigEasyDriver.h"

//Acceleration available, ramp up and ramp down 200 steps. If move = 600 steps, no acceleration.

#define pi 3.14159265359

#define debugMode false

#define distRot 5.093 //cm
#define steepsPerRev 6400
#define gearRadius 0.7958
#define fullLength 72 //cm
#define maxSpeed 6000 // steps/s
#define distPerStep 0.0007953125 //cm
#define delayOffset 50

bool _checkFlag;
int _stepCount;

#define clk 16000000
#define n 8
#define stSpeed 500
#define ramp 0.1 //Not used.
#define rampStep 200

BigEasyDriver::BigEasyDriver(int dirPin, int stepPin){
	pinMode(dirPin, OUTPUT);
	pinMode(stepPin, OUTPUT);
	_dirPin = dirPin;
	_invDir = -1;
	_stepPin = stepPin;
	_dir = true;
	_lineSpeed = 0;
	_debugMode = debugMode;
	_fullLength = fullLength;
	_sps = 0;
	_currentLocation = 0;
	_ramp = ramp;
	_rampStep = rampStep; 
}

void BigEasyDriver::doStep(double totalSteps){

	if(_debugMode){
		Serial.print("start_currentLocation: "); Serial.println(_currentLocation);
	}
	if(_dir)
		_currentLocation = _currentLocation - BigEasyDriver::convertStepsToDistance(totalSteps);
	else
		_currentLocation = _currentLocation + BigEasyDriver::convertStepsToDistance(totalSteps);
	if(_debugMode){
		Serial.print("end_currentLocation: "); Serial.println(_currentLocation);
		Serial.println("******************************");
	}
	
	if(_lineSpeed != 0){
		_sps = _lineSpeed/distPerStep;
    }
	
	float rampSteps;
    //float rampSteps = steps * ramp;
    float startSpeed;
	float inc;
	float startPeriod;
	double steadySteps;
	float steadyPeriod;
	float stepPeriod;
	//_sps
	float a, b, c, d;
	float timeRamp;
	float fullSpeed;
	float Accel;
	long int startTime;
    long int finishTime;
    
    long int startStepTime;
    long int finishStepTime;
	
	startSpeed = stSpeed;
	rampSteps = rampStep;
	steadySteps = totalSteps - rampSteps * 2;
	
	a = 2 * startSpeed;
	b = steadySteps - moveTime*startSpeed - 2*totalSteps;
	c = moveTime*(totalSteps - steadySteps);
	d = sqrt(pow(b,2)-4*a*c);
	timeRamp = ((-b) - d)/(2*a);
		
	fullSpeed = (2*rampSteps+timeRamp*startSpeed-2*startSpeed*timeRamp)/(timeRamp);
	if(fullSpeed<startSpeed){
		fullSpeed = startSpeed;
		if(_debugMode){
			Serial.println("NO ACCELERATION, TO SLOW!!!");
		}
	}
	
	if(moveTime == 0){
		fullSpeed = _sps;
	}
	
	if(fullSpeed>maxSpeed){
		fullSpeed = maxSpeed;
		if(_debugMode){
			Serial.println("CAN NOT MEET DEADLINE, TO FAST!!!");
		}
	}
	Accel = (fullSpeed - startSpeed)/timeRamp; //staps/s*s
	
	startPeriod = (1000000 * 1/startSpeed);
	steadyPeriod = (1000000 * 1/fullSpeed);
	
	stepPeriod = startPeriod;//   - delayOffset;
	
    inc = (steadyPeriod - startPeriod)/(rampSteps);

    digitalWrite(_dirPin,_dir);
    delay(50);
   
    // if less steps then 2x ramp steps
    if(totalSteps < rampSteps*2){
    	steadySteps = totalSteps;
    	rampSteps = 0;
    	if(_debugMode){
			Serial.println("NO ACCELERATION, TO SHORT!!!");
		}
	}
    
    // RAMP UP
    if(_debugMode){
		Serial.print("moveTotal: "); Serial.println(moveTime);
    	Serial.print("steps: "); Serial.println(totalSteps);
    	Serial.print("Start speed: "); Serial.print(startSpeed); Serial.print(" Full speed: "); Serial.println(fullSpeed);
    	Serial.print("timeRamp: "); Serial.println(timeRamp);
    	Serial.print("fullSpeed: "); Serial.println(fullSpeed);
    	Serial.print("AccelShould: "); Serial.println(Accel);
    	Serial.println("******************************");
    	Serial.println("//Ramping up");
    	Serial.print("steps: "); Serial.println(rampSteps);
    	Serial.print("Start step period: "); Serial.print(stepPeriod); Serial.println(" microseconds");
    	Serial.print("delay increment: "); Serial.println(inc);
    }
    
    startTime = millis();
    
	for(int i = 0;i<rampSteps;i++){
		//startStepTime = micros();
		digitalWrite(_stepPin, HIGH);
		delayMicroseconds(round(stepPeriod/2)-delayOffset);
		digitalWrite(_stepPin, LOW);
		delayMicroseconds(round(stepPeriod/2-delayOffset));
    	stepPeriod = stepPeriod + inc;
    	//finishStepTime = micros();
	}
	
	finishTime = millis();
	
	float acceleration = (1000*(fullSpeed - startSpeed))/((finishTime - startTime));
	if(_debugMode){
		Serial.print("Step Time: "); Serial.print(finishStepTime - startStepTime); Serial.println(" microseconds");
		Serial.print(" Time: "); Serial.print(finishTime - startTime); Serial.println(" ms");
		Serial.print(" AccelerationIs: "); Serial.print(acceleration); Serial.println(" steps/s^2");
    }

    // STEADY SPEED
    if(_debugMode){
    	Serial.println(" ------------------------------");
        Serial.println("--Constant speed");
        Serial.print(" steps: "); Serial.println(steadySteps);
        Serial.print(" Full speed: "); Serial.print(fullSpeed); Serial.println(" steps/s");
        Serial.print(" Constant delay per step: "); Serial.print(stepPeriod); Serial.println(" microseconds");   
        Serial.print(" delay increment: "); Serial.print(" 0"); Serial.println(" microseconds");
    }
    startTime = millis();
    
    for(long i = 0;i<steadySteps;i++){
		//startStepTime = micros();
    	digitalWrite(_stepPin, HIGH);
    	delayMicroseconds(round(stepPeriod/2)-delayOffset);
    	digitalWrite(_stepPin, LOW);
    	delayMicroseconds(round(stepPeriod/2)-delayOffset);
    	stepPeriod = stepPeriod + 0;
    	//finishStepTime = micros();
    }
    
    finishTime = millis();
 
    //RUMP DOWN
    if(_debugMode){
		Serial.print("Step Time: "); Serial.print(finishStepTime - startStepTime); Serial.println(" microseconds");
		Serial.print(" Time: "); Serial.print(finishTime - startTime); Serial.println(" ms");
    	Serial.println(" ------------------------------");
    	Serial.println("\\Ramping down");
    	Serial.print(" steps: "); Serial.println(rampSteps);
    	Serial.print(" End speed: "); Serial.print(startSpeed); Serial.println(" steps/s");
    }
    
    startTime = millis();
    
    for(int i = 0;i<rampSteps;i++){
		//startStepTime = micros();
    	digitalWrite(_stepPin, HIGH);
    	delayMicroseconds(round(stepPeriod/2)-delayOffset);
    	digitalWrite(_stepPin, LOW);
    	delayMicroseconds(round(stepPeriod/2)-delayOffset);
    	stepPeriod = stepPeriod - inc;
    	//finishStepTime = micros();
    }
    
    finishTime = millis();
    
     if(_debugMode){
		Serial.print("Step Time: "); Serial.print(finishStepTime - startStepTime); Serial.println(" microseconds");
        Serial.print(" End delay: "); Serial.println(stepPeriod); Serial.println(" microseconds");
        Serial.print(" delay increment: "); Serial.print(inc); Serial.println(" microseconds");
        Serial.print(" Time: "); Serial.print(finishTime - startTime); Serial.println(" ms");
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


