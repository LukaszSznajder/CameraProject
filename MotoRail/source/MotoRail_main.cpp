/*************************************************************
project: <type project name here>
author: <type your name here>
description: <type what this file does>
*************************************************************/
#include "Interface.h"
#include "LcdDevice.h"
#include "MotorControl.h"
#include "motorInstructions.h"

#define noDebug false

MotorControl motor(noDebug);
Interface interface;
motorInstructions MotorInstructions;

//LcdDevice lcd2;

void setup() {
}

void loop() {
	interface.buttonsRefresh();
	interface.interfaceRefresh();
	MotorInstructions = interface.updateMotorInstructions();
	motor.motorExecute(MotorInstructions);	
}
