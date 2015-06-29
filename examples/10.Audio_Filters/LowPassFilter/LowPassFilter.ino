/*  Example of filtering a wave,
    using Mozzi sonification library.
  
    Demonstrates LowPassFilter().
  
    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or 
    check the README or http://sensorium.github.com/Mozzi/
  
    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users
  
    Tim Barrass 2012, CC by-nc-sa.
*/

#include <SPI.h>

//#include <ADC.h>  // Teensy 3.1 uncomment this line and install http://github.com/pedvide/ADC
#include <MozziGuts.h>
#include <Oscil.h>

// #include <tables/chum9_int8.h> // recorded audio wavetable
#include <tables/saw256_int8.h>
#include <tables/cos2048_int8.h> // for filter modulation

#include <LowPassFilter.h>
#include <mozzi_rand.h>

#define CONTROL_RATE 64 // powers of 2 please

Oscil<256, AUDIO_RATE> aCrunchySound(SAW256_DATA);
Oscil<COS2048_NUM_CELLS, CONTROL_RATE> kFilterMod(COS2048_DATA);

LowPassFilter lpf;

void setup(){
  startMozzi(CONTROL_RATE);
//   aCrunchySound.setFreq(2.f);
  
  aCrunchySound.setFreq(200.f);  
//   kFilterMod.setFreq(1.3f);
  lpf.setResonance(200);
}

void loop(){
  audioHook();
}

void updateControl(){
//   if (rand(CONTROL_RATE/2) == 0){ // about once every half second
//     kFilterMod.setFreq((float)rand(255)/64);  // choose a new modulation frequency
//   }
  // map the modulation into the filter range (0-255)
//   byte cutoff_freq = 100 + kFilterMod.next()/2;
  byte cutoff_freq = 100;
  lpf.setCutoffFreq(cutoff_freq);
}

int updateAudio(){
  int asig = lpf.next(aCrunchySound.next() );
  return asig << 3;
}






