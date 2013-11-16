# include "Arduino.h"
# include "SerialAga.h"
//# include "math.h"

SerialCom::SerialCom(bool debugMode){
	_arrayLength = 10;
	_serialCount = 0;
	_instLength = 2;
	_exMessageFlag = false;
	_debugMode = debugMode;
}

void SerialCom::start(double baundRate){
	Serial.begin(baundRate);
	if(_debugMode){
		Serial.print("Serial initialized to baud rate: ");
		Serial.println(baundRate);
	}
}

void SerialCom::setInstLength(int instLength){
	_instLength = instLength;
}

void SerialCom::setArrayLength(int arrayLength){
	_arrayLength = arrayLength;
}

void SerialCom::setDebugMode(boolean debug){
	_debugMode = debug;
}

void SerialCom::serialSend(char * number){
}

boolean SerialCom::newMessage(){
	return _exMessageFlag;
}

void SerialCom::resetFlag(){
	 _exMessageFlag = false;
}

void SerialCom::serialDecodeInst(char * inst, char * message){

	*inst = *message;

	*(inst+1) = *(message+1);
}

float SerialCom::serialDecodeVal(char * inChar){
	float retVal = 0;
	int factor = 1;
	float decFactor = 1;
	int sign = 1;
	int signOffset = 0;
	if(_debugMode){
		Serial.println("------------------------");
		Serial.println("DECODING NEW VALUE");
		Serial.println("------------------------");
	}
	if(*(inChar+_instLength) == '-'){
		if(_debugMode)
			Serial.println(" Negative sign encoded");
		sign = -1;
		signOffset = 1;
	}
	for(int i=0;i<_messageLength-_instLength-signOffset;i++){
		if(_debugMode){
			Serial.print("n = "); Serial.println(i);
		}
		if (*(inChar+_messageLength-i-1) == '.'){
			if(_debugMode)
				Serial.println(" Decimal point encoded");
			for(int j = 0; j < i; j++){
				decFactor = decFactor * 0.1;
			}
		}
		else{
			retVal = retVal + (*(inChar+_messageLength-i-1)-'0')*factor;
			if(_debugMode){
				Serial.print(" Current Factor = "); Serial.println(factor);
				Serial.print(" Current sum of returned values = "); Serial.println(retVal);
			}
			factor = factor * 10;
		}
	}

	if(_debugMode){
		Serial.println(" ");
		Serial.println("SUMMARY");
		Serial.print(" Decimal point factor = "); Serial.println(decFactor);
		Serial.print(" Return value = "); Serial.println(retVal);
		Serial.print(" The received string has been decoded to:"); Serial.println(retVal* sign * decFactor);
		Serial.println("------------------------");
	}
	return retVal* sign * decFactor;
}


void SerialCom::serialRecieve(char *inChar){
	while(Serial.available()) {
		delay(50);
		if(_serialCount == 0){
			for(int i=0;i<_arrayLength;i++){
				*(inChar+i)= 0;
			}
		}
		_serialCount++;
		*(inChar+_serialCount-1) = (char)Serial.read();
		if(_debugMode){
			Serial.print("Read: "); Serial.print(*(inChar+_serialCount-1)); Serial.print("; n: "); Serial.println(_serialCount-1);
		}
		if(*(inChar+_serialCount-1)=='\n') {
			_messageLength = _serialCount - 1;
			_serialCount = 0;
			_intMessageFlag = true;
			_exMessageFlag = true;
		}
	}

}




