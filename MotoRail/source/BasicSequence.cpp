#include "Arduino.h"
#include "BasicSequence.h"
#include "Parameters.h"
#include "BigEasyDriver.h"

#define dirPin 19
#define stepPin 18
#define debug true
#define camTr 15
#define camFc 16	
#define fullLength 72 //cm

BigEasyDriver motorBS(dirPin, stepPin);

BasicSequence::BasicSequence(){
	pinMode(camTr, OUTPUT);
	pinMode(camFc, OUTPUT);
}

void BasicSequence::runBasicSequence(Parameters _parameters){
	parameters = _parameters;
	long timeStart = 0;
	long timeFinish = 0;

	
	//basicMoveDelay
	//basicMoveFrames
	//basicMoveRange
	
	float intervalLenght = parameters.basicMoveRange/parameters.basicMoveFrames; //in cm
	float time = intervalLenght/parameters.basicMoveDelay;
	motorBS.moveTime = time + 2; // in s
	
	if(debug){
		Serial.println("-------STARTING SIMPLE MOVE, parameters:-------");
		Serial.print("parameters.basicMoveDelay: "); Serial.println(parameters.basicMoveDelay); 
		Serial.print("parameters.basicMoveFrames: "); Serial.println(parameters.basicMoveFrames);
		Serial.print("parameters.basicMoveRange: "); Serial.println(parameters.basicMoveRange);
		Serial.print("intervalLenght: "); Serial.println(intervalLenght);
		Serial.print("lineSpeed: "); Serial.println(time);
	}
	
	digitalWrite(camFc, HIGH);
	delay(500);
	digitalWrite(camTr, HIGH);
	delay(500);
	digitalWrite(camTr, LOW);
	digitalWrite(camFc, LOW);
	
	
	for (int i=0;i<parameters.basicMoveFrames;i++){
		timeStart = millis();
		motorBS.doMove(intervalLenght);
		timeFinish = millis();
		if((timeFinish - timeStart)<1000*parameters.basicMoveDelay)
		delay(1000*parameters.basicMoveDelay-(timeFinish - timeStart));
		
		digitalWrite(camFc, HIGH);
		delay(500);
		digitalWrite(camTr, HIGH);
		delay(500);
		digitalWrite(camTr, LOW);
		digitalWrite(camFc, LOW);
	}
	
	if(debug){
		Serial.println("-------END SIMPLE MOVE, summary:-------");
		Serial.print("timeStart: "); Serial.println(timeStart);
		Serial.print("timeFinish: "); Serial.println(timeFinish);
		Serial.print("timeFinish - timeStart: "); Serial.println(timeFinish - timeStart);
		Serial.print("Extra delay: "); Serial.println(1000*parameters.basicMoveDelay-(timeFinish - timeStart));
	}
	
}

void BasicSequence::setParameters(Parameters _parameters){
	parameters = _parameters;
}
