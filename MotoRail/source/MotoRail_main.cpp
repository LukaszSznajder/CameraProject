/*************************************************************
project: <type project name here>
author: <type your name here>
description: <type what this file does>
*************************************************************/
#include "Interface.h"
#include "LcdDevice.h"


Interface interface;
//LcdDevice lcd2;

void setup() {
}

void loop() {
	interface.buttonsRefresh();
	interface.interfaceRefresh();
}
