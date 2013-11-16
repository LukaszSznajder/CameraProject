int dirPin = 9;
int stepperPin = 10;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepperPin, OUTPUT);
}

void loop(){
  step(true,1600);
  delay(500);
  step(false,1600);
  delay(500);
}

void step(boolean dir,int steps){
  digitalWrite(dirPin,dir);
  delay(50);
  for(int i=0;i<steps;i++){
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(250);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(250);
  }
}
