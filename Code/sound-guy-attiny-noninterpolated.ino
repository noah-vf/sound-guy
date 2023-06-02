/* THIS LIBRARY DOES NOT SUPPORT INTERPOLATION. 1 Band is repeated in 2 of the 8 rows.
     Shift Register Audio Display, v2
     Uses shiftRegDisplay and MSGEQ7 classes to generate a graphic EQ 
     This version is rotated right for hardware version 2
     To do: AGC?
*/

#include "MSGEQ7.h"
#include "shiftRegDisplayATT.h"


#define pinReset 7
#define pinStrobe 1
#define pinAnalog A0
#define pinLatch 4
#define pinColClock 5
#define pinColData 6
#define pinRowClock 9
#define pinRowData 10


#define MSGEQ7_INTERVAL ReadsPerSecond(60)
#define MSGEQ7_SMOOTH 100// Range: 0-255

shiftRegDisplayATT disp(pinColClock,pinColData,pinRowClock,pinRowData,pinLatch,80000);
CMSGEQ7<MSGEQ7_SMOOTH, pinReset, pinStrobe, pinAnalog> MSGEQ7;



void setup() {
  MSGEQ7.begin();

}

byte valueMap(byte inputValue) { //Map analog readings to a number that corresponds to all the LEDs in a certain column. Byte -> "Row of LEDS".
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



void loop() {   //If a new reading is available, get it, map it, push it to display. If not, keep updating display.
  bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);
  byte calcValues[8];

  if (newReading) {               // Take new measurement 
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

    calcValues[7] = bass;	
    calcValues[6] = bass;							
    calcValues[5] = bass2;
    calcValues[4] = low;
    calcValues[3] = low2;
    calcValues[2] = mid;
    calcValues[1] = mid2;
    calcValues[0] = high;
  

   }

   
  for (int y = 0; y < 8; y++){                      //Rotate the display right. For every new column value, derive it from unrotated column values
    byte newValue = 0; 
    for (int j = 0; j<8; j++){                      
      if ((calcValues[7-j] & (1<<y)) > 0) {
        newValue = newValue + (1<<j);
      }
    }
    disp.colValues[y] = newValue;               
  }

 disp.updateDisplay();
}
