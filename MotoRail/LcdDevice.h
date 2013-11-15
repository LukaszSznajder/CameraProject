//-------------------------------------------------------------------
#ifndef __LcdDevice_H__
#define __LcdDevice_H__
//-------------------------------------------------------------------

#include <arduino.h>
/*
//------------------------------------
//------------------------------------
//	
//	  1234567890123456
//   -----------------
// 1 | ? Simple Move
// 2 | V Seqence Smart
// 3 |   Seqence Basic
//   -----------------
//
//------------
//Sub-Menu's:
//
// Simple Move:  
//	  1234567890123456
// -------------------
// 1 | Click to move
// 2 |<<<<S:xx>>>>P:xx
// ------------------- 
//
// Sequence Smart: 
//    1234567890123456
// -------------------
// 1 | ? FPS:xx #
// 2 | V Output:xxx s
// 3 |   Event:xxx min
// 4 |   Range:xx %
// 5 |   Start
// -------------------
//
// Sequence Basic:
//    1234567890123456
// -------------------
// 1 | ? Delay:xx s
// 2 | V Frames:xxx #
// 3 |   Move:xx cm
// 5 |   Start
// -------------------
//
//------------------------------------
//------------------------------------
*/

class LcdDevice{
public:
	LcdDevice();
	void lcdRefresh();
	void zeroValues();
	int manualSpeed;
	int manualPosition;
	int smartFps;
	int smartOutputDuration;
	int smartEventDuration;
	int samrtMovementRange;
	bool startFlag;
	
private:
	void displayText();
	void displayNumeric();
}

//-------------------------------------------------------------------

//===================================================================
// -> DO NOT WRITE ANYTHING BETWEEN HERE...
// 		This section is reserved for automated code generation
// 		This process tries to detect all user-created
// 		functions in main_sketch.cpp, and inject their  
// 		declarations into this file.
// 		If you do not want to use this automated process,  
//		simply delete the lines below, with "&MM_DECLA" text 
//===================================================================
//---- DO NOT DELETE THIS LINE -- @MM_DECLA_BEG@---------------------
//---- DO NOT DELETE THIS LINE -- @MM_DECLA_END@---------------------
// -> ...AND HERE. This space is reserved for automated code generation!
//===================================================================


//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------
