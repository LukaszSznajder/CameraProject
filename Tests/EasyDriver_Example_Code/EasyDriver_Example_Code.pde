/*
Example code for driving 4 wire bipolar stepper motor 22.7.11 - Roy Fisher www.proto-pic.co.uk

Parts required:-
1 x Arduino UNO(PPUNO)
1 x EasyDriver Stepper Motor Driver(PPROB-10267)
1 x 4 Wire Bipolar Stepper Motor(PPROB-09238) Red wire - A, Green - C, Yellow - B, Blue - D 

By default the EasyDriver board is set to 1/8th mode so with motor being 200 steps/rev it takes 1600
steps to rotate motor 1 turn.

We were using a 12vDC PSU to power the EasyDriver motor input, remember to common the Arduino and 
PSU grounds!
*/


const int CW = 0;
const int CCW = 1;
const int MotorStep = 5;    //pin5 of the Arduino connects to the STEP pin of the EasyDriver board
const int MotorDir = 6;    //pin6 of the Arduino connects to the DIR pin of the EasyDriver board

void setup() {                
  // initialize the digital pin as Outputs
  
pinMode(MotorStep, OUTPUT);
pinMode(MotorDir, OUTPUT);
digitalWrite(MotorStep, LOW);
digitalWrite(MotorDir, CW);
}

void loop() 
{  
  
  RotateMotor(CW, 1600, 65435);  //Rotate motor clockwise 1 turn quickly
  delay(1000);
  RotateMotor(CCW, 1600, 64000);   //Rotate motor clockwise 1 turn more slowly
  delay(1000);
    
}


void RotateMotor(int Direction, int Steps, int Speed) 
// Speed values realistically can be anywhere from 0 to 65435(very slow to fast)
{
 int i;
 digitalWrite(MotorDir, Direction);    // Set direction to rotate motor
 for(i = 0; i < Steps; i++)
  {
  digitalWrite(MotorStep, HIGH);
  delayMicroseconds((65535 - Speed));
  digitalWrite(MotorStep, LOW);
  delayMicroseconds((65535 - Speed));
  } 
}


