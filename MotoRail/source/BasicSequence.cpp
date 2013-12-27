#include "Arduino.h"
#include "BasicSequence.h"
#include "Parameters.h"
#include "BigEasyDriver.h"

#define dirPin 19
#define stepPin 18
#define debug false
#define camTr 15
#define camFc 16	
#define fullLength 72 //cm
#define shutterTime 1

//BigEasyDriver motorBS(dirPin, stepPin);

BasicSequence::BasicSequence(){
	pinMode(camTr, OUTPUT);
	pinMode(camFc, OUTPUT);
}

BigEasyDriver BasicSequence::runSmartSequence(Parameters _parameters, BigEasyDriver motorSS){
	float fpsO;
	
	//smartFps
	//smartOutputDuration in s
	//smartEventDuration in s
	//samrtMovementRange in cm
		
	_parameters.basicMoveFrames = _parameters.smartFps*_parameters.smartOutputDuration;
	fpsO = _parameters.basicMoveFrames/_parameters.smartEventDuration;
	_parameters.basicMoveDelay = 1/fpsO;
	_parameters.basicMoveRange = _parameters.samrtMovementRange;
	
	motorSS = BasicSequence::runBasicSequence(_parameters, motorSS);
	
	return(motorSS);
	
}

BigEasyDriver BasicSequence::runBasicSequence(Parameters _parameters, BigEasyDriver motorBS){
	parameters = _parameters;
	long timeStart = 0;
	long timeFinish = 0;

	//basicMoveDelay
	//basicMoveFrames
	//basicMoveRange
	
	float intervalLenght = parameters.basicMoveRange/parameters.basicMoveFrames; //in cm
	float time = parameters.basicMoveDelay;
	
	if((time - shutterTime) > 0){
		motorBS.moveTime = time - shutterTime; // in s
	} else
		motorBS.moveTime = time;
	
	if(debug){
		Serial.println("-------STARTING SIMPLE MOVE, parameters:-------");
		Serial.print("parameters.basicMoveDelay: "); Serial.println(parameters.basicMoveDelay); 
		Serial.print("parameters.basicMoveFrames: "); Serial.println(parameters.basicMoveFrames);
		Serial.print("parameters.basicMoveRange: "); Serial.println(parameters.basicMoveRange);
		Serial.print("intervalLenght: "); Serial.println(intervalLenght);
		Serial.print("moveTime: "); Serial.println(motorBS.moveTime);
	}
	
	digitalWrite(camFc, HIGH);
	delay(400);
	digitalWrite(camTr, HIGH);
	delay(400);
	digitalWrite(camTr, LOW);
	digitalWrite(camFc, LOW);
	
	
	for (int i=0;i<parameters.basicMoveFrames;i++){
		
		timeStart = millis();
		motorBS.doMove(intervalLenght);
		
		timeFinish = millis();
		
		if(((timeFinish + 800) - timeStart)<1000*parameters.basicMoveDelay)
			delay(1000*parameters.basicMoveDelay-((timeFinish + 800) - timeStart));
		
		digitalWrite(camFc, HIGH);
		delay(400);
		digitalWrite(camTr, HIGH);
		delay(400);
		digitalWrite(camTr, LOW);
		digitalWrite(camFc, LOW);
		
		
		if(debug){
			Serial.println("---------------------------");
			Serial.print("frame #: "); Serial.println(i);
			Serial.print("Duration: "); Serial.println(timeFinish - timeStart);
			Serial.print("Extra delay: "); Serial.println(1000*parameters.basicMoveDelay-(timeFinish - timeStart));
		}
	}
	
	return(motorBS);
	
}

void BasicSequence::setParameters(Parameters _parameters){
	parameters = _parameters;
}
