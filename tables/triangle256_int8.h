#ifndef TRIANGLE256_H_
#define TRIANGLE256_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <avr/pgmspace.h>

#define TRIANGLE256_NUM_CELLS 256
#define TRIANGLE256_SAMPLERATE 256

const int8_t __attribute__((section(".progmem.data"))) TRIANGLE256_DATA []  =
        {
	  0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 
	  40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 
	  78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 
	  114, 116, 118, 120, 122, 124, 126, 126, 124, 122, 120, 118, 116, 114, 112, 110, 
	  108, 106, 104, 102, 100, 98, 96, 94, 92, 90, 88, 86, 84, 82, 80, 78, 76, 74, 72, 
	  70, 68, 66, 64, 62, 60, 58, 56, 54, 52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 
	  30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10, 
	  -12, -14, -16, -18, -20, -22, -24, -26, -28, -30, -32, -34, -36, -38, -40, -42, 
	  -44, -46, -48, -50, -52, -54, -56, -58, -60, -62, -64, -66, -68, -70, -72, -74, 
	  -76, -78, -80, -82, -84, -86, -88, -90, -92, -94, -96, -98, -100, -102, -104, 
	  -106, -108, -110, -112, -114, -116, -118, -120, -122, -124, -126, -128, -128, 
	  -126, -124, -122, -120, -118, -116, -114, -112, -110, -108, -106, -104, -102, 
	  -100, -98, -96, -94, -92, -90, -88, -86, -84, -82, -80, -78, -76, -74, -72, 
	  -70, -68, -66, -64, -62, -60, -58, -56, -54, -52, -50, -48, -46, -44, -42, 
	  -40, -38, -36, -34, -32, -30, -28, -26, -24, -22, -20, -18, -16, -14, -12, 
	  -10, -8, -6, -4, -2
        };

#endif /* TRIANGLE256_H_ */