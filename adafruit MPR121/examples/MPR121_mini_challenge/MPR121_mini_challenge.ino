/*********************************************************
This is a Music player 12-channel by Capacitive touch

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

************************CONNECTIONS*****************************
*                                                              *
*                                                              *
*                                                              *
*          SDA--------------------------SDA                    *
*          SCL--------------------------SCL                    *
*          3.3V-------------------------3.3V                   *  
*          IRQ--------------------------D2                     *
*          BUZZER-----------------------D11                    *
*                                                              * 
*                                                              *
*                                                              *    
****************************************************************

Written by Akshay Chawla.  
*/



#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "pitches.h"

Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

//you can you any ONE of the below arrays for music tones.
int notes[]={NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_C5}; // C-Major scale
//int notes[]={NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5}; // A-Minor scale
//int notes[]={NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_AS4,NOTE_C5,NOTE_DS5}; // C Blues scale

int sound[12]={0,0,0,0,0,0,0,0};

void setup() {
  Serial.begin(9600);
  
  Serial.println("Touch sensor board test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("Touch sensor board not found, check wiring?");
    while (1);
  }
  Serial.println("Touch sensor board found!");
}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (int i=0; i<8; i++) {
    // *is* touched and *wasnt* touched before, alert! 
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      sound[i]=1;                                                     //makes the value of array as 1 if touched.
      Serial.print(i); Serial.println(" touched");
    }
    // *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {

      sound[i]=0;                                                    //makes the value of array as 0 if released.
      Serial.print(i); Serial.println(" released");
     
    }

    //checks if any key is pressed, and tone is played accordingly
     if(sound[i]==1)
      {
       tone(11, notes[i]); 
      }
      else if((sound[0]||sound[1]||sound[2]||sound[3]||sound[4]||sound[5]||sound[6]||sound[7])==0)
      noTone(11);
  }

  // reset our state
  lasttouched = currtouched;
  delay(100);
}
