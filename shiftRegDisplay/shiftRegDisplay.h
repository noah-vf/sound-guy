#ifndef shiftRegDisplay_h
#define shiftRegDisplay_h
#include "Arduino.h"


class shiftRegDisplay {
  public:
    int colclockPin;
    int coldataPin;
    int latchPin;
    int rowclockPin;
    int rowdataPin;
    long lastUpdate;
    long nextUpdate;
    int updateRate;
    byte colValues[8];
    shiftRegDisplay(int colclockPin, int coldataPin, int rowclockPin, int rowdataPin,int latchPin, int updateRate);
    void shiftOutCol(byte myDataOut);
    void shiftOutRow(byte myDataOut);
    void shiftRow();
    void shiftCol();
    bool updateDisplay();
    void xyPaint(int col, int row);
    void xyClr(int col, int row);
    int yConvert(int y);
    void drawLine(int startx, int starty, int endx, int endy);
    void clr();
	void rotateLeft();
	
  private:
	void fastDigitalWrite(int pin, bool value);
};
#endif
