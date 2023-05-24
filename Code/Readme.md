## ------------V1 NOTES --------------

This is the first complete version of the matrix bluetooth vis program. It contains a modified version of the standard V1 
shiftRegDisplay library. Set up for V0.1 matrix PCB, with 1088AS display modules. 

->To switch to the 1088BS configuration, reverse polarity of the "pinState" commands in shiftCol and shiftRow. 

->To rotate the display, switch the configured Row and Col data and clock pins, and also do the above. 

->the interpolated version is the one actually implemented in hardware. However either should work.