#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int sensor_pin = A0;
int solenoidPin = 4;    //This is the output pin on the Arduino we are using
int buzzerPin = 8;
int output_value ;

void setup() {
   pinMode(solenoidPin, OUTPUT);           //Sets the pin as an output
   Serial.begin(9600);

   Serial.println("Reading From the Sensor ...");

   delay(2000);

   }

void play_alarm() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzerPin);
  }
}

void loop() {

   output_value= analogRead(sensor_pin);

   output_value = map(output_value,1050,170,0,100);

   if(output_value < 50) {
    play_alarm();
    digitalWrite(solenoidPin, HIGH); 
   }
   else{
    digitalWrite(solenoidPin, LOW); 
   }

   Serial.print("Mositure : ");

   Serial.print(output_value);

   Serial.println("%");

   delay(1000);

   }
