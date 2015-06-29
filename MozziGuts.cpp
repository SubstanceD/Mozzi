/*
 * MozziGuts.cpp
 *
 * Copyright 2012 Tim Barrass.
 *
 * This file is part of Mozzi.
 *
 * Mozzi by Tim Barrass is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
 * 
 * This version created by Marije Baalman for the ATTiny841 (c) 2015
 */

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <util/atomic.h>
#include "MozziGuts.h"
#include "mozzi_config.h" // at the top of all MozziGuts and analog files
// #include "mozzi_analog.h"
#include "CircularBuffer64.h"

#include "mozzi_utils.h"

#include <SPI.h>

/// -------- input ---------


/// -------- output --------

CircularBuffer64 <unsigned int> output_buffer; // fixed size 64

void audioHook() // 2us excluding updateAudio()
{
//setPin13High();
// #if (USE_AUDIO_INPUT==true)
// 	if (!input_buffer.isEmpty()) 
// 		audio_input = input_buffer.read();
// #endif
	if (!output_buffer.isFull()) {
		output_buffer.write((unsigned int) (updateAudio() + AUDIO_BIAS));

	}
//setPin13Low();
}

uint16_t normalModeMask = 0x3FFF;
// set pin 10 as the slave select for the DAC:
// const int slaveSelectPin = 10;
const int slaveSelectPin = 3;

static void startAudioSPI()
{
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);

  // initialize SPI:
  SPI.begin();
  SPI.usingInterrupt( 255 );
  
  cli();
  // CTC mode, pre-scaler 1:1
  TCCR1A = 0;
  TCCR1B = (1<<WGM12) | (1<<CS10);
  OCR1A = 750; // top at 1000
  TIMSK1 = ( 1<<OCIE1A );
  sei();
  
}

ISR(TIMER1_COMPA_vect)
{    
  uint16_t outputValue = output_buffer.read();
  outputValue = outputValue & normalModeMask;

  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);    // FIXME: faster version of this
  //  send in the address and value via SPI:
  SPI.transfer16(outputValue);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);    // FIXME: faster version of this  
}

//-----------------------------------------------------------------------------------------------------------------

static void updateControlWithAutoADC()
{
	updateControl();
	/*
	#if (USE_AUDIO_INPUT==true)
		adc_count = 0;
		startSecondAudioADC();
#endif
	*/
// 	adcStartReadCycle();
}

static void startControl(unsigned int control_rate_hz)
{
// 	TimerZero::init(1000000/control_rate_hz,updateControlWithAutoADC); // set period, attach updateControlWithAutoADC()
// 	TimerZero::start();
  
  // disable timer 0 interrupts
  TIMSK0 = 0;
  // use system clock (clkI/O)
  //ASSR &= ~(1 << AS2);
  // Clear Timer on Compare Match (CTC) mode
  TCCR0A = (1 << WGM01);

  // only need prescale bits in TCCR0B
//   TCCR0B = (1 << CS01) | (1 << CS00); // prescaler 1:64
  TCCR0B = (1 << CS02); // prescaler 1:256

  // set TOP so timer period is (ticks >> i)
//   OCR0A = (ticks >> i) - 1;
  OCR0A = 64;
  
  // start
  TIMSK0 |= (1 << OCIE0A);
}

// ISR for timer 0 Compare A interrupt
// TB2012 added ISR_NOBLOCK so it can be interrupted by Timer 1 (audio)

ISR(TIMER0_COMPA_vect, ISR_NOBLOCK)
{
	// disable timer 0 interrupts
	TIMSK0 = 0;
	updateControlWithAutoADC();
	// enable timer 2 COMPA interrupt
	TIMSK0 |= (1 << OCIE0A);
}


void startMozzi(int control_rate_hz)
{
// 	setupMozziADC(); // you can use setupFastAnalogRead() with FASTER or FASTEST in setup() if desired (not for Teensy 3.1)
	startControl(control_rate_hz);

	startAudioSPI();
}

void pauseMozzi()
{
}

void unPauseMozzi()
{
}

unsigned long audioTicks()
{
	return output_buffer.count();
}


unsigned long mozziMicros()
{
	return audioTicks() * MICROS_PER_AUDIO_TICK;
}
