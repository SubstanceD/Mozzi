#ifndef AUDIOCONFIGATTINYX41_14BIT_H
#define AUDIOCONFIGATTINYX41_14BIT_H


/** @ingroup core
*/
/* Used internally to put the 0-biased generated audio into the centre of the output range (14 bits on ATTiny841 with SPI) */
#define AUDIO_BIAS ((uint16_t) 4096)

// #define AUDIO_BIAS ((uint8_t) 244)

// #define AUDIO_CHANNEL_1_PIN A14

#endif        //  #ifndef AUDIOCONFIGATTINYX41_14BIT_H

