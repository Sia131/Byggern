
#include "node2_melody.h"



void buzz(int frequency, int length) {;
    sound_set_tone(frequency);
    
    for (int i = 1; i < length; i++){
        _delay_ms(1);
        
    }
}


void play_mario() {
  // iterate over the notes of the melody:
    int size = 49; //about the length of the song
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / mario_tempo[thisNote];
 
      buzz(mario_melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:

      int pauseBetweenNotes = noteDuration * 1.30;
      for(int i = 1; i < pauseBetweenNotes; i++){
          _delay_ms(1);
      }
 
    }
}

void play_underworld(){
  // iterate over the notes of the melody:
    int size = 56; //about the length of the song
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];
 
      buzz(underworld_melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:

      int pauseBetweenNotes = noteDuration * 1.30;
      for(int i = 1; i < pauseBetweenNotes; i++){
          _delay_ms(1);
      }
 
    }

}