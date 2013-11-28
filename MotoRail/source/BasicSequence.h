#ifndef BasicSequence_h
#define BasicSequence_h


#include "Arduino.h"
#include "Parameters.h"
#include "BigEasyDriver.h"

class  BasicSequence{
public:
	BasicSequence();
	Parameters parameters;
	void setParameters(Parameters _parameters);
	BigEasyDriver runBasicSequence(Parameters _parameters,BigEasyDriver motorBS);
	BigEasyDriver runSmartSequence(Parameters _parameters, BigEasyDriver motorSS);
private:
};
#endif