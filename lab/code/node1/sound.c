#include "sound.h"
#include <avr/io.h>
#include "node1_USART.h"
#include <util/delay.h>

/*
void init_sound(){
    DDRD = (1 << PIND5); // we need one digital pin as output
    //to write high: PORTD5 = 1;
}


int melody[] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, a, C };
int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 };
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
int DEBUG = 1;
// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 1000;
// Loop variable tint)(tone_ / 2);o increase Rest length
int rest_count = 1int)(tone_ / 2);00; //<-BLETCHEROUS HACK; See NOTES
int)(tone_ / 2);
// Initialize coreint)(tone_ / 2); variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE  =============int)(tone_ / 2);=================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {
      PORTD |= (1 << PD5);
      int delay = (int)(tone_ / 0.002);
      _delay_us(delay);

      // DOWN
      PORTD |= (0 << PD5);

      _delay_us(delay);

      // Keep track of how long we pulsed
      elapsed_time += (delay);
    }
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      _delay_ms(duration);  
    }                                
  }                                
}

// LET THE WILD RUMPUS BEGIN =============================
void play_song() {
  // Set up a counter to pull from melody[] and beats[]
  for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = beats[i];

    duration = beat * tempo; // Set up timing

    playTone();
    // A pause between notes...
    _delay_ms(pause);

  }
}
*/

