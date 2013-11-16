#include "Tlm.h"
/*
void slider(byte flag, byte numOfValues)
{
  int sliderPosition;
  
  sliderPosition = meetAndroid.getInt();
  X_axis.Execute(AP, sliderPosition);
}

void start(byte flag, byte numOfValues){
  meetAndroid.flush();
  Serial.print("start"); Serial.print("\n");
  for(currentFrame;currentFrame<numbOfFrames;currentFrame++){
    Serial.print("current frame: "); Serial.print(currentFrame); Serial.print("\n");
    meetAndroid.receive();
    stepperM.doStep(true,numbSteps,moveSpeed);
    delay(settleTime*1000);
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(cameraTime*1000);
  }
  currentFrame = 0;
}


void frames(byte flag, byte numOfValues){
  numbOfFrames = meetAndroid.getInt();
  Serial.print("\n"); Serial.print("frames"); Serial.print(numbOfFrames); Serial.print("\n");
}

void delaY(byte flag, byte numOfValues){
  delayTime = meetAndroid.getFloat();
  Serial.print("delay Time (s)"); Serial.print(delayTime); Serial.print("\n"); 
}

void speeD(byte flag, byte numOfValues){
  moveSpeed = ((delayTime - cameraTime - settleTime)/numbSteps)/2;
  moveSpeed = moveSpeed*1000*1000;
  Serial.print("move Speed"); Serial.print(moveSpeed); Serial.print("\n");
}

void pause(byte flag, byte numOfValues){
  Serial.print("pause"); Serial.print("\n");
  meetAndroid.flush();
  while(true){
    meetAndroid.receive();
  }
}

void stoP(byte flag, byte numOfValues){
  Serial.print("stop"); Serial.print("\n");
  meetAndroid.flush();
  currentFrame = 0;
  while(true){
    meetAndroid.receive();
  }
}

void steps(byte flag, byte numOfValues){
 numbSteps = meetAndroid.getInt();
 Serial.print("step size"); Serial.print(numbSteps); Serial.print("\n");
}
*/