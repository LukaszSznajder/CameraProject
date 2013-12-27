/*************************************************************
project: <type project name here>
author: <type your name here>
description: <type what this file does>
*************************************************************/
#include "Interface.h"
#include "LcdDevice.h"
#include "MeetAndroid.h"
#include "motorail_main.h"

#define baundRate 115200
#define debugMode true

Interface interface;
MeetAndroid meetAndroid;

//LcdDevice lcd2;

void setup() {
	meetAndroid.registerFunction(slider, 'o');
	Serial.begin(115200);
}

void loop() {
	interface.buttonsRefresh();
	interface.interfaceRefresh();
	meetAndroid.receive();
	
}

void slider(byte flag, byte numOfValues)
{
  interface.setBluetoothValue(meetAndroid.getFloat());
}
