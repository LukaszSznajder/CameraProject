#ifndef SerialAga_h
#define SerialAga_h

#include "Arduino.h"

class SerialCom{
public:
	SerialCom(bool debugMode);
	// Define the length of Array the serial communication will be writing to
	void setArrayLength(int arrayLength);
	void start(double baundRate);
	void serialSend(char * start);
	void serialRecieve(char * inChar);
	void serialDecodeInst(char * inst, char * message);
	void setInstLength(int instLength);
	void setDebugMode(boolean debug);
	float serialDecodeVal(char * inChar);
	boolean newMessage();
	void resetFlag();
	//newMessage is a flag to notify that a new message has been received, calling this once will set the flag to false
private:
	int _serialCount;
	int _arrayLength;
	int _instLength;
	int _messageLength;
	boolean _debugMode;
	boolean _intMessageFlag;
	boolean _exMessageFlag;
};

#endif
