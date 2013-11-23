/*************************************************************
project: <type project name here>
author: <type your name here>
description: <type what this file does>
*************************************************************/
#include <tlm01_main.h>
#include <Arduino.h>
#include <SerialAga.h>
#include <MotorControl.h>
#include <MeetAndroid.h>
#include <AccelStepper.h>

#define arrayLength 10
#define instLength 2
#define baudRate 115200
#define debug true
#define noDebug false
#define LED 13

SerialCom MySerial (noDebug);
MotorDriver X_axis (debug);
//MeetAndroid meetAndroid;

//message is an array to store the message coming from the serial communication
char message [arrayLength];
char instruction [instLength];
float value = 0;

int numbOfFrames = 0;

int absolutePosition = 0;

void setup()   {
	MySerial.start(baudRate);
	
	pinMode(LED, OUTPUT);
	digitalWrite(LED, HIGH);
	
	//meetAndroid.registerFunction(slider, 'o');
	/*meetAndroid.registerFunction(frames, 'a');
	meetAndroid.registerFunction(delaY, 'd');
	meetAndroid.registerFunction(speeD, 'v');
	meetAndroid.registerFunction(steps, 'b');
	meetAndroid.registerFunction(stoP, 's');
	meetAndroid.registerFunction(pause, 'c'); 
	meetAndroid.registerFunction(start, 'p');*/
}

void loop()
{
	//meetAndroid.receive();
	MySerial.serialRecieve(message);
	if(MySerial.newMessage()){
		MySerial.resetFlag();
		value = MySerial.serialDecodeVal(message);
		MySerial.serialDecodeInst(instruction, message);
		X_axis.Execute(instruction, value);
	}
}

int main(void) {

  init();
  setup();

  while(true) {
    loop();
  }
}

/*
void slider(byte flag, byte numOfValues)
{
  analogWrite(LED, LOW);
  absolutePosition = meetAndroid.getInt();
  instruction[1] = 'A';
  instruction[2] = 'P';
  X_axis.Execute(instruction, absolutePosition);
}
*/
