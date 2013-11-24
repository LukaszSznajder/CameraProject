#ifndef BigEasyDriver_h
#define BigEasyDriver_h

#include "Arduino.h"

class BigEasyDriver{
  public:
    BigEasyDriver(int dirPin, int stepPin);
    void setDebugMode(boolean debug);

    void doRev(float rev); // approximatley 2 rev are 10 cm.
    void doDeg(float deg); //in deg
    void doMove(float distance); //in cm, to whole length of the rail is 72cm
    void doStep(double totalSteps); // steeps per rev 6400
    void doAbsolutePercent(int percent);
    
    float convertStepsToDistance(double steps);
    float convertDegToDistance(double deg);
    float convertRevToDistance(double rev);

    void setSps(int sps); // steps per second, normaly 10000 is considered fast and 1000 slow, 
    void setLineSpeed(float lineSpeed); //in cm/s, will be used instead of Sps if not zero.
    void setDirection(bool dir); // true cw, false ccw
    void invDirection(int invDir); //invert direction
    void setRampSteps(int setRampSteps); //number of steps ramping up and down
    
  private:
    boolean _debugMode;
    int _dirPin;
    int _stepPin;
    int _invDir;
    bool _dir;
    float _lineSpeed;
    int _sps;
    float _currentLocation;
	float _fullLength;
	float _ramp;
	int _rampStep;
};

#endif
