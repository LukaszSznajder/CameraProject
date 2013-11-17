/*************************************************************
project: <type project name here>
author: <type your name here>
description: <type what this file does>
*************************************************************/
#include "Interface.h"
#include "LcdDevice.h"

#define baundRate 115200
#define debugMode true

Interface interface;

//LcdDevice lcd2;

void setup() {
	if(debugMode){
		Serial.begin(baundRate);
	}
}

void loop() {
	interface.buttonsRefresh();
	interface.interfaceRefresh();
}
