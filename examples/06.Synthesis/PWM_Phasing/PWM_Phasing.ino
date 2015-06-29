/*  Example of pulse width modulation,
    using Mozzi sonification library.
     
    Based Miller Puckette's j03.pulse.width.mod example 
    in the Pure Data documentation, subtracting 2 sawtooth 
    waves with slightly different tunings to produce a 
    varying phase difference.
  
    Demonstrates Phasor().
  
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
#include <Phasor.h>

#include <LowPassFilter.h>

#define CONTROL_RATE 64 // powers of 2 please

Phasor <AUDIO_RATE> aPhasor1;
Phasor <AUDIO_RATE> aPhasor2;

LowPassFilter lpf;

float freq = 200.f;

void setup(){
  aPhasor1.setFreq(freq);
//   aPhasor2.setFreq(freq+1.1f);
  aPhasor2.setFreq(freq+50.1f);
  
  lpf.setResonance(200);
  lpf.setCutoffFreq(200.f);
  
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
}


void updateControl(){
}


int updateAudio(){
  int asig1 = (int)(aPhasor1.next()>>19);
  int asig2 = (int)(aPhasor2.next()>>19);
  int asig3 = lpf.next( (asig1 - asig2)/2);
//   return ((int)asig1-asig2)/2;
  return (asig3);
}


void loop(){
  audioHook(); // required here
}







