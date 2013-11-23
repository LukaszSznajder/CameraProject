#ifndef BasicSequence_h
#define BasicSequence_h


#include "Arduino.h"
#include "Parameters.h"

class  BasicSequence{
public:
	BasicSequence();
	Parameters parameters;
	void setParameters(Parameters _parameters);
	void runBasicSequence(Parameters _parameters);
private:
};
#endif