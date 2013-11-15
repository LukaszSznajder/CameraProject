#include "Arduino.h"
#include "Interface.h"
#include "LcdDevice.h"
#include "Buttons.h"

Buttons btn;

LiquidCrystal LCD(2, 3, 4, 5, 6, 7);
LcdDevice lcd(LCD);

Interface::Interface(){
	LCD.begin(16,2);
	//lcd.lcdClear();
	lcd.currentPage = 0;
	//lcd.lcdButton = btn.button;
	//lcd.lcdPressed = btn.pressed;
	lcd.lcdRefresh(LCD);
}

void Interface::clearAll(){
	//lcd.lcdClear();
}

void Interface::refreshAll(){
	//lcd.lcdRefresh();
}

void Interface::buttonsRefresh(){
	btn.scanButtons();
}

