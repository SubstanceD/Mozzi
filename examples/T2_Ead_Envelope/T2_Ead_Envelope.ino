/*  Example playing an enveloped noise source
 *  using Mozzi sonification library.
 *
 *  Demonstrates Ead (exponential attack decay).
 *
 *  Circuit: Audio output on digital pin 9.
 *
 *  Mozzi help/discussion/announcements:
 *  https://groups.google.com/forum/#!forum/mozzi-users
 *
 *  Tim Barrass 2012.
 *  This example code is in the public domain.
 */

#include <MozziGutsT2.h>
#include <Oscil.h> // oscillator template
#include <tables/whitenoise8192_int8.h>
#include <Ead.h> // exponential attack decay
#include <EventDelay.h>

#define CONTROL_RATE 256 // powers of 2 please

Oscil <WHITENOISE8192_NUM_CELLS, AUDIO_RATE> aNoise(WHITENOISE8192_DATA); // audio noise
EventDelay kDelay(CONTROL_RATE); // for triggering envelope start
Ead kEnvelope(CONTROL_RATE); // resolution will be CONTROL_RATE

int gain;

void setup(){
  startMozziT2(CONTROL_RATE);
  // cast to float because the resulting freq will be small
  aNoise.setFreq((float)AUDIO_RATE/WHITENOISE8192_SAMPLERATE);
  int attack = 30;
  int decay = 1000;
  kEnvelope.set(attack,decay);
  kDelay.set(attack+decay+100);
  Serial.begin( 57600 );
}


void updateControlT2(){
  if(kDelay.ready()){
    kEnvelope.start();
    kDelay.start();
  }
  gain = (int) kEnvelope.next();
  Serial.println(gain);
}


int updateAudioT2(){
  return (gain*aNoise.next())>>8;
}


void loop(){
  audioHookT2(); // required here
}







