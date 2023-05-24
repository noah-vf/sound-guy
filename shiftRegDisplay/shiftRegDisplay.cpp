/*
  
 ShiftRegDisplay, v.1
 Class for bitbanging communications to 2 shift registers, in order to control a 1088-style LED matrix

 Bugs:
  updateDisplay timing may be borked. Refresh rate stays in POV for reasonable updateRate though. 
 */



#include "Arduino.h"
#include "shiftRegDisplay.h"
shiftRegDisplay::shiftRegDisplay(int colclockPin, int coldataPin, int rowclockPin, int rowdataPin,int latchPin, int updateRate) {
      pinMode(colclockPin, OUTPUT);
      pinMode(coldataPin, OUTPUT);
      pinMode(rowclockPin, OUTPUT);
      pinMode(rowdataPin, OUTPUT);
      pinMode(latchPin, OUTPUT);
      this->colclockPin = colclockPin;
      this->coldataPin = coldataPin;
      this->rowdataPin = rowdataPin;
      this->rowclockPin = rowclockPin;
      this->latchPin = latchPin;
      this->updateRate = updateRate;
      this->lastUpdate = 0;
}

void shiftRegDisplay::shiftOutCol(byte myDataOut) { //Shift a byte to the column register. Latching is not performed.
  int i=0;
  int pinState;
  digitalWrite(coldataPin, 0);
  digitalWrite(colclockPin, 0);
  for (i=7; i>=0; i--)  {

    digitalWrite(colclockPin, 0);
    if ( myDataOut & (1<<i) ) {
      pinState= 1; //Reverse these pinStates to invert the values
    }
    else {
      pinState= 0;
    }
    digitalWrite(coldataPin, pinState);
    digitalWrite(colclockPin, 1);
    digitalWrite(coldataPin, 0);

  }
  digitalWrite(colclockPin, 0);
}

void shiftRegDisplay::shiftOutRow(byte myDataOut) { //Shift a byte to the row register. Latching is not performed.
  int i=0;
  int pinState;
  digitalWrite(rowdataPin, 0);
  digitalWrite(rowclockPin, 0);
  for (i=7; i>=0; i--)  {

    digitalWrite(rowclockPin, 0);
    if  ( myDataOut & (1<<i) ) {
      pinState= 0;
    }
    else {
      pinState= 1;
    }
    digitalWrite(rowdataPin, pinState);
    digitalWrite(rowclockPin, 1);
    digitalWrite(rowdataPin, 0);

  }
  digitalWrite(rowclockPin, 0);
}
void shiftRegDisplay::shiftRow() {
  digitalWrite(rowclockPin, 0);
  digitalWrite(rowclockPin, 1);
  digitalWrite(rowclockPin, 0);
}
void shiftRegDisplay::shiftCol() {
  digitalWrite(colclockPin, 0);
  digitalWrite(colclockPin, 1);
  digitalWrite(colclockPin, 0);
}

bool shiftRegDisplay::updateDisplay(){   //Update the entire display based on the contents of colValues

    digitalWrite(latchPin, 0);
    this->shiftOutCol(1);              

    
    for (int j = 0; j < 8; j++) {  //bitbang the column values one-by-one
      digitalWrite(latchPin, 0);
      if (j>=1){
		this->shiftCol();
      }
	this->shiftOutRow(this->colValues[j]);
    digitalWrite(latchPin, 1);

	}
  this->lastUpdate = micros();
  return(1);
  }


void shiftRegDisplay::xyPaint(int x, int y) {             //Pick a coordinate, draw a dot. Should be as fast as possible since this is an atomic function
  byte row;
  row = this->yConvert(y);

  
  int TranslatedX = 8 - x;
  this->colValues[TranslatedX] = byte(this->colValues[TranslatedX]) | row;
}

void shiftRegDisplay::xyClr(int x, int y) {
  byte row;
  row = this->yConvert(y);

  
  int TranslatedX = 8 - x;
  this->colValues[TranslatedX] = byte(this->colValues[TranslatedX]) & ~row;
}

void shiftRegDisplay::clr() {
  for (int i; i < 8; i++) {
    this->colValues[i] = 0;
  }
}
int shiftRegDisplay::yConvert(int y){
    byte row;
    switch (y) {
    case 1:
      row = 1;
      break;
    case 2: 
      row = 2;
      break;
    case 3:
      row = 4;
      break;
    case 4:
      row = 8;
      break;
    case 5:
      row = 16;
      break;
    case 6: 
      row = 32;
      break;
    case 7:
      row = 64;
      break;
    case 8:
      row = 128;
      break;
    default:
      row = 0;
      break;
  }
  return(row);
}

void shiftRegDisplay::drawLine(int startx, int starty, int endx, int endy) {
  if (starty == endy) {
    for (int i=0; i <= (endx - startx); i++) {
    this->xyPaint(startx+i,starty);
    }
  }
  else if (startx == endx) {
    for (int i=0; i<= endy - starty; i++) {
      this->xyPaint(startx, starty+i);
      }
    }
  else if (abs(endx-startx) == abs(endy-starty)) {
    for (int i=0; i<=(endx-startx); i++){
      this->xyPaint(startx+i, starty+i);
    }
}
}

