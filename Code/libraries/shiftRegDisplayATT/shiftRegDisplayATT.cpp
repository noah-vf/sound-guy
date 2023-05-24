/*
  
 ShiftRegDisplay, v.1 ---ATTINY EDITION.
 
 This class has been optimised for a specific hardware configuration. For a more generalized, unoptimized version, look elsewhere.
 
 Class for bitbanging communications to 2 shift registers, in order to control a 1088-style LED matrix
 
 */
 
 
//Latch: 4 -> PortA4
//ColClock: 5 -> PortA5
//ColData: 6 -> PortA6
//RowClock: 9 -> PortB1
//RowData: 10->PortB0




#include "Arduino.h"
#include "shiftRegDisplayATT.h"
#include <avr/io.h>
shiftRegDisplayATT::shiftRegDisplayATT(int colclockPin, int coldataPin, int rowclockPin, int rowdataPin,int latchPin, int updateRate) {
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

void shiftRegDisplayATT::shiftOutCol(byte myDataOut) { //Shift a byte to the column register. Latching is not performed.
  int i=0;
  int pinState;
  PORTA &= ~bit(6);
  PORTA &= ~bit(5);
  for (i=7; i>=0; i--)  {

    PORTA &= ~bit(5);
    if ( myDataOut & (1<<i) ) {
      PORTA &= ~bit(6); //   1/2 Reverse this pair of commands to switch polarity
    }
    else {
      PORTA |= bit(6);	//	1/2 Reverse this pair of commands to switch polarity
    }
    PORTA |= bit(5);
    PORTA &= ~bit(6);

  }
  PORTA &= ~bit(5);
}

void shiftRegDisplayATT::shiftOutRow(byte myDataOut) { //Shift a byte to the row register. Latching is not performed.
  int i=0;
  bool pinState;
  PORTA &= ~bit(0);
  PORTB &= ~bit(1);
  for (i=7; i>=0; i--)  {

    PORTB &= ~bit(1);
    if  ( myDataOut & (1<<i) ) {
      PORTB |= bit(0); 			//	1/2 Reverse this pair of commands to switch polarity
    }
    else {
      PORTB &= ~bit(0); 		//	1/2 Reverse this pair of commands to switch polarity
    }
    PORTB |= bit(1);
    PORTA &= ~bit(0);

  }
  PORTB &= ~bit(1);
}
void shiftRegDisplayATT::shiftRow() {
  PORTB &= ~bit(1);
  PORTB |= bit(1);
  PORTB &= ~bit(1);
}
void shiftRegDisplayATT::shiftCol() {
  PORTA &= ~bit(5);
  PORTA |= bit(5);
  PORTA &= ~bit(5);
}

bool shiftRegDisplayATT::updateDisplay(){                     //Update the entire display based on the contents of colValues
  long updateTime = 1000000/this->updateRate;
  long currentTime = micros();
  if (currentTime - this->lastUpdate > updateTime) {    //Update only at the specified rate
    for (int j = 0; j < 8; j++) {  						//bitbang the column values one-by-one
      PORTA &= ~bit(4);
	  byte colNumber = 1<<j;
	  this->shiftOutCol(colNumber);
	  this->shiftOutRow(this->colValues[7-j]);
	  PORTA |= bit(4);
	}
	PORTA &= ~bit(4);
	this->shiftOutCol(0);
	this->shiftOutRow(0);
	PORTA |= bit(4);
	
  
  this->lastUpdate = micros();
  return(1);
  }
  else {
    return(0);
  }
}

void shiftRegDisplayATT::xyPaint(int x, int y) {             //Pick a coordinate, draw a dot. Should be as fast as possible since this is an atomic function
  byte row;
  row = this->yConvert(y);

  
  int TranslatedX = 8 - x;
  this->colValues[TranslatedX] = byte(this->colValues[TranslatedX]) | row;
}

void shiftRegDisplayATT::xyClr(int x, int y) {
  byte row;
  row = this->yConvert(y);

  
  int TranslatedX = 8 - x;
  this->colValues[TranslatedX] = byte(this->colValues[TranslatedX]) & ~row;
}

void shiftRegDisplayATT::clr() {
  for (int i; i < 8; i++) {
    this->colValues[i] = 0;
  }
}
int shiftRegDisplayATT::yConvert(int y){
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

void shiftRegDisplayATT::drawLine(int startx, int starty, int endx, int endy) {
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

//void shiftRegDisplayATT::bitmapDraw(uint64_t bitmap) {
  
//}
