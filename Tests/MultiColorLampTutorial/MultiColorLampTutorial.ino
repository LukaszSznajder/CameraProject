
#include <MeetAndroid.h>
#include <StepperM.h>

int dirPin = 9;
int stepperPin = 10;
int ledPin = 11; 

int numbOfFrames = 0;
float delayTime = 0;
double moveSpeed = 0;
int numbSteps = 0;
int lastPosition;
int FULL_CIRCLE = 1600;
int currentFrame = 0;
float cameraTime = 1; 
float settleTime = 0.5;

// declare MeetAndroid so that you can call functions with it
MeetAndroid meetAndroid;

StepperM stepperM;

void setup()  
{
  Serial.begin(115200); 
  
  // register callback functions, which will be called when an associated event occurs.
  meetAndroid.registerFunction(slider, 'o');
  meetAndroid.registerFunction(frames, 'a');
  meetAndroid.registerFunction(delaY, 'd');
  meetAndroid.registerFunction(speeD, 'v');
  meetAndroid.registerFunction(steps, 'b');
  meetAndroid.registerFunction(stoP, 's');
  meetAndroid.registerFunction(pause, 'c'); 
  meetAndroid.registerFunction(start, 'p');

  // set all color leds as output pins
  pinMode(ledPin, OUTPUT);
  pinMode(stepperPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop()
{
  meetAndroid.receive();
}

void slider(byte flag, byte numOfValues)
{
  int moveBy;
  int doMove;
  
  moveBy = meetAndroid.getInt();
  doMove = moveBy - lastPosition;
  lastPosition = lastPosition + doMove;
  
  Serial.print("moving by: "); Serial.print(doMove); Serial.print("\n");
  if(doMove > 0){
    doStep(true,map(doMove, 0, 255, 0, FULL_CIRCLE),250);
    Serial.print("positive: "); Serial.print(map(doMove, 0, 255, 0, FULL_CIRCLE)); Serial.print("\n");
  }else{
    doStep(false,map(abs(doMove), 0, 255, 0, FULL_CIRCLE),250);
    Serial.print("negative: "); Serial.print(map(abs(doMove), 0, 255, 0, FULL_CIRCLE)); Serial.print("\n");
  }
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

void doStep(boolean dir,int steps, float stepSpeed){
  digitalWrite(dirPin,dir);
  for(int i=0;i<steps;i++){
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(stepSpeed);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(stepSpeed);
  }
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
