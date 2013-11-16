#ifndef Interface_h
#define Interface_h

#include "Arduino.h"

class Interface {
public:
	Interface();
	void interfaceRefresh();
	void buttonsRefresh();
	void clearAll();
	void debug();
	
private:
};
#endif