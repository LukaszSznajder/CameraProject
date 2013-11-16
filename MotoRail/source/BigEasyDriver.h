#ifndef StepperM_h
#define StepperM_h

#include "Arduino.h"

class StepperControl{
  public:
    StepperControl(int dirPin, int stepPin);

    void doRev(float rev);
    void doDeg(float deg); //in deg
    void doMove(float distance); //in cm
    void doStep(double steps);

    void setLineSpeed(float lineSpeed); //in cm/s
    void setSps(int sps); // steps per second
    void setDirection(bool dir); // true cw, false ccw

    void setDebugMode(boolean debug);

    void invDirection(int invDir); //invert direction
    
    float convertStepsToDistance(double steps);

  private:
    boolean _debugMode;
    int _dirPin;
    int _stepPin;
    int _invDir;
    bool _dir;
    float _lineSpeed;
    int _sps;
};

#endif
