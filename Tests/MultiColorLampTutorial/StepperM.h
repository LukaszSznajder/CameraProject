#ifndef StepperM_h
#define StepperM_h

#include "Arduino.h"

class StepperM
{
  public:
    StepperM();
    void doStep(boolean dir,int steps, float stepSpeed);
};

#endif
