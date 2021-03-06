/*  Example of a sound changing volume with and without
 *  smoothing of the control signal to remove obvious clicks,
 *  using Mozzi sonification library.
 *
 *  Demonstrates using Smooth to filter a control signal at audio rate,
 *  EventDelay to schedule changes and rand() to choose random volumes.
 *
 *  Circuit: Audio output on digital pin 9.
 *
 *  Mozzi help/discussion/announcements:
 *  https://groups.google.com/forum/#!forum/mozzi-users
 *
 *  Tim Barrass 2012.
 *  This example code is in the public domain.
 */

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <EventDelay.h>
#include <Smooth.h>
#include <utils.h>

#define CONTROL_RATE 128

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

// for scheduling audio gain changes
EventDelay kGainChangeDelay(CONTROL_RATE);
const unsigned int gainChangeMsec = 200;

//  for scheduling turning smoothing on and off
EventDelay kSmoothOnOff(CONTROL_RATE);
const unsigned int smoothOnOffMsec = 2000;

float smoothness = 0.9975f;
Smooth <long> aSmoothGain(smoothness);
boolean smoothIsOn=true;
long target_gain = 0;


void setup(){
  aSin.setFreq(330u); // audio oscil set freq with unsigned int
  kGainChangeDelay.set(gainChangeMsec);
  kSmoothOnOff.set(smoothOnOffMsec);
  startMozzi(CONTROL_RATE);
}


void updateControl(){
  // switch smoothing on and off to show the difference
  if(kSmoothOnOff.ready()){
    if (smoothIsOn) {
      aSmoothGain.setSmoothness(0.f);
      smoothIsOn = false;
    }
    else{
      aSmoothGain.setSmoothness(smoothness);
      smoothIsOn = true;
    }
    kSmoothOnOff.start();
  }

  // random volume changes
  if(kGainChangeDelay.ready()){
    target_gain = rand((unsigned char) 255);
    kGainChangeDelay.start();
  }

}


int updateAudio(){
  return (int)(aSmoothGain.next(target_gain) * aSin.next()) >> 8; // shift back to char precision after multiply
}


void loop(){
  audioHook();
}





