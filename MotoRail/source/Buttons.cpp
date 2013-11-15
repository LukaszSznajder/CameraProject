#include "Arduino.h"
#include "Buttons.h"

#define buttonsPin 17

Buttons::Buttons(){
	pinMode(buttonsPin, INPUT);
	digitalWrite(buttonsPin, HIGH);
	button = 0;
}

void Buttons::scanButtons(){

	int btnValue;
	int whichButton1;
	int whichButton2;
	int whichButton3;
	int _deBounceDelay = 10;
	long int _pressedTDel = 100000;
	long int _currentTime = 0;

	btnValue = analogRead(buttonsPin);
	whichButton1 = _whichButton(btnValue);
	_currentTime = micros();
	if((whichButton1!=0) && (_currentTime>(_pressedTime+_pressedTDel))){
		delay(_deBounceDelay);	
		btnValue = analogRead(buttonsPin);
		whichButton2 = _whichButton(btnValue);
		if (whichButton1 == whichButton2){
			delay(_deBounceDelay);
			btnValue = analogRead(buttonsPin);
			whichButton3 = _whichButton(btnValue);
			if(whichButton2 == whichButton3)
				pressed++;
				button = whichButton3;
				_pressedTime = micros();
		}
	}
}

int Buttons::_whichButton(int btnVal){ 
	int pressed_btn = 0;
	
  //5v - 1023
  //4.12v btn1 - 843 -> 900 - 700; btnVal<900 &&btnVal>700
  //3.3v btn2 - 675 -> 700 - 600; btnVal<700 && btnVal>600
  //2.47v btn3 - 0.5 -> 600 - 400; btnVal<600 && btnVal>400
  //1.65v btn4 - 337.6 -> 400 - 300; btnVal<400 && btnVal>300
  //0.83v btn5 - 169.8 -> 300 - 100; btn<300 && btnVal>100
  //0v btn6 - 0 -> 100 - 0; btn<100
	
	if(btnVal>900){
		pressed_btn = 0;
	}
	else if(btnVal<900 && btnVal>700){
		pressed_btn = 1;
	}
	else if(btnVal<700 && btnVal>600){
		pressed_btn = 2;
	}
	else if(btnVal<600 && btnVal>400){
		pressed_btn = 3;
	}
	else if (btnVal<400 && btnVal>300){
		pressed_btn = 4;
	}
	else if (btnVal<300 && btnVal>100){
		pressed_btn = 5;
	}
	else if (btnVal<100){
		pressed_btn = 6;
	}
	return(pressed_btn);
}

