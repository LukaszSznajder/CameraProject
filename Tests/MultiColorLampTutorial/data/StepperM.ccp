#include "Arduino.h"
#include "StepperM.h"

StepperM::StepperM()
{
}

void StepperM::doStep(boolean dir,int steps, float stepSpeed)
{  
    digitalWrite(dirPin,dir);
    for(int i=0;i<steps;i++){
      digitalWrite(stepperPin, HIGH);
      delayMicroseconds(stepSpeed);
      digitalWrite(stepperPin, LOW);
      delayMicroseconds(stepSpeed);
    }
  }
}

