# sound-guy
### Bluetooth Audio Visualizer With 1088-Style LED Matrix

This project started with an impulse purchase of a bunch of MSGEQ7 IC's from an online retailer. These chips provide an analog output representing a 7-band graphic equalizer. Combined with some cheap MH-M28 drop-in bluetooth modules, I thought the MSGEQ7 could be a good backbone for a fun little module, and thus was born what would become the Sound Guy, a portable usb-powered bluetooth to 3.5mm Aux adapter with an 8x8 LED matrix playing a visualization of the audio being played. This is a work-in-progress, thanks for checking it out! 


# Hardware: 

-MSGEQ7 7-Band Graphic Equalizer

-74xC595 Shift Register (2x)

-1088-style 8x8 LED Matrix Displays

-ATTINY84 microcontroller @ 8MHZ (internal)

-Adafruit ItsyBitsy M0 Express acting as ISP

-MH-M28 Bluetooth Audio Receiver

# Software: 

-Arduino IDE 

-MSGEQ7 Library from https://github.com/NicoHood
