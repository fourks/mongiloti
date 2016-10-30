#include <Arduino.h>

//#include "MenuSystem.h"
#include <MIDI.h>
#include <SPI.h>
#include <Wire.h>

#include "defines.h"
#include "encoder.h"
#include "pot.h"
#include "trellis.h"
#include "display.h"
// #include "logo.h"

//MenuSystem ms;

//set Midi channel
#define CHANNEL 7

//rgb test
int rgbon = 155;
int rgboff = 255;
//const int ledPin = 13;

void setup()   {

        //???
        analogReadResolution(7);
        analogReadAveraging(8);
//        pinMode(ledPin, OUTPUT);

        //do we need this? Not for MIDI anyway.
        //Serial.begin(9600);

        //setup Midi

        //setups
        //setupTrellis();

        setupDisplay();
        delay(5000);

        //setupMenu();
        setupButton();

        //RGB LED's (INPUT because of 5v instead of gnd)
        // pinMode(LED_RED, INPUT);
        // pinMode(LED_GREEN, INPUT);
        // pinMode(LED_BLUE, INPUT);
        // //rgb
        // analogWrite(LED_RED, rgboff);
        // analogWrite(LED_GREEN, rgboff);
        // analogWrite(LED_BLUE, rgboff);

        //draw();
        MIDI.begin();

        setupPots();

        //MIDI.sendNoteOn(50, 100, CHANNEL);
        MIDI.sendNoteOn(50, 100, CHANNEL);
        MIDI.sendNoteOff(50, 100, CHANNEL);
}


void loop() {
//     digitalWrite(ledPin, HIGH);   // set the LED on
//     delay(1000);                  // wait for a second
//     digitalWrite(ledPin, LOW);    // set the LED off
//     delay(1000);                  // wait for a second

        delay(30); // 30ms delay is required for Trellis, TODO!

        //midi test
        //MIDI.sendNoteOn(50, 100, CHANNEL);
        //delay(500);
        //MIDI.sendNoteOff(50, 100, CHANNEL);

        processButton();
        //processEncoder();
        processPots();
        //processTrellis();

        updateDisplay();
}
