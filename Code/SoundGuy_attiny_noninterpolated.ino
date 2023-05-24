/* THIS LIBRARY DOES NOT SUPPORT INTERPOLATION. 1 Band is repeated in 2 of the 8 rows.
     Shift Register Audio Display, v1 
     Uses shiftRegDisplay and MSGEQ7 classes to generate a graphic EQ 
     To do: AGC?
*/
#include "MSGEQ7.h"
#include "shiftRegDisplay.h"

// Pinmap for Arduino Uno. Uncomment to Enable
/*
#define pinReset A1
#define pinStrobe A2
#define pinAnalog A3
#define pinLatch 8
#define pinColClock 9
#define pinColData 10
#define pinRowClock 12
#define pinRowData 13
*/
// Pinmap for ATTiny84. Uncomment to enable.

#define pinReset 7
#define pinStrobe 1
#define pinAnalog A0
#define pinLatch 4
#define pinColClock 5
#define pinColData 6
#define pinRowClock 9
#define pinRowData 10




#define MSGEQ7_INTERVAL ReadsPerSecond(50)
#define MSGEQ7_SMOOTH 100 // Range: 0-255

byte averages[8][20];
shiftRegDisplay disp(pinColClock,pinColData,pinRowClock,pinRowData,pinLatch,8000);
CMSGEQ7<MSGEQ7_SMOOTH, pinReset, pinStrobe, pinAnalog> MSGEQ7;



void setup() {
  MSGEQ7.begin();
}

byte valueMap(byte inputValue) { //Map analog readings to a number that corresponds to all the LEDs in a certain column
  if (inputValue<32){
    return(1);
  }
  else if (inputValue<64){
    return(3);
  }
  else if(inputValue<96){
    return(7);
  }
  else if(inputValue<128){
    return(15);
  }
  else if(inputValue<160){
    return(31);
  }
  else if (inputValue<192){
    return(63);
  }
  else if (inputValue<224){
    return(127);
  }
  else {
    return(255);
  }
}

int arrayAverage(byte inputArray[20]) {   
  int average = (inputArray[0] + inputArray[1]+ inputArray[2]+ inputArray[3]+ inputArray[4]+ inputArray[5]+ inputArray[6]+ inputArray[7]+ inputArray[8]+ inputArray[9]+ inputArray[10]+ inputArray[11]+ inputArray[12]+ inputArray[13]+ inputArray[14]+ inputArray[15]+ inputArray[16]+ inputArray[17]+ inputArray[18]+ inputArray[19])/20;
  return(average);
}

void loop() {   //If a new reading is available, get it, map it, push it to display. If not, keep updating display.
  bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);
  if (newReading) {
   byte bass = MSGEQ7.get(MSGEQ7_0);
    bass = mapNoise(bass);
    byte bass2 = MSGEQ7.get(MSGEQ7_1);
    bass2 = mapNoise(bass2);
    byte low = MSGEQ7.get(MSGEQ7_2);
    low = mapNoise(low);
    byte low2 = MSGEQ7.get(MSGEQ7_3);
    low2 = mapNoise(low2);
    byte mid = MSGEQ7.get(MSGEQ7_4);
    mid = mapNoise(mid);
    byte mid2 = MSGEQ7.get(MSGEQ7_5);
    mid2 = mapNoise(mid2);
    byte high = MSGEQ7.get(MSGEQ7_6);
    high = mapNoise(high);

    int  scaleFactor = 1;
    
    disp.colValues[0]= byte(valueMap(scaleFactor*bass));
    disp.colValues[1]= byte(valueMap(scaleFactor*bass2));
    disp.colValues[2]= byte(valueMap(scaleFactor*low));
    disp.colValues[3]= byte(valueMap(scaleFactor*low2));
    disp.colValues[4]= byte(valueMap(scaleFactor*mid));
    disp.colValues[5]= byte(valueMap(scaleFactor*mid2));
    disp.colValues[6]= byte(valueMap(scaleFactor*mid2));
    disp.colValues[7]= byte(valueMap(scaleFactor*high));


    
    

   }
 disp.updateDisplay();
}
