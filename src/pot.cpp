#include "pot.h"
#include "Wire.h"
#include "control.h"
#include "display.h"

const int potCount = 10;

// take this as the Pot midimap
Pot pots[potCount] {
        { POT_A0, "OSC1 Shape", 23 },
        { POT_A1, "OSC2 Shape", 28 },
        { POT_A2, "OSC Mix", 31 },
        { POT_A3, "Attack", 73 },
        { POT_A6, "Decay", 75 },
        { POT_A7, "Sustain", 79 },
        { POT_A8, "Release", 72 },
        { POT_A9, "Cutoff", 74 },
        { POT_A10, "Resonance", 71 },
        { POT_A11, "Gain", 77 }
};

void setupPots(){

        //Set pot initial values
        for (int i = 0; i<potCount; i++) {
                pots[i].set_cv(pots[i].read());
                pots[i].push_cv();
        }
}

void processPots(){
        //scan pots for change

        for (int i = 0; i<potCount; i++) {
            if (pots[i].read() != pots[i].get_cv()) {
                pots[i].set_cv(pots[i].read());
                pots[i].push_cv();
                draw(pots[i].get_name(), pots[i].read());
            } else {
                //draw(pots[i].get_name(), pots[0].read());
            }
        }
}

Pot::Pot(int pin, const char* name, byte cc) : Control(name, cc)
{
        _pin = pin;
        _index = -1;
        _mapMax = 1024;
        _mapMin = 0;
        _res = 1;
        attach(_pin);
}

void Pot::attach(int pin) {
        _pin = pin;
        _index = 0;

        int start = analogRead(pin);
        for(int i = 0; i < SMOOTH_ANALOG_INPUT_SIZE; i++) {
                _samples[i] = start;
        }
}

void Pot::scale(int min, int max) {
        if (max <= min) {
                return;
        }

        _mapMin = min;
        _mapMax = max;

        _res = 1024 / (max - min) * 2;
}

int Pot::raw() {
        if (_pin == -1) {
                return -1;
        }

        int value = analogRead(_pin);
        int last = _samples[_index];
        if (abs(value - last) <= _res) {
                value = last;
        }

        _index = (_index + 1) % SMOOTH_ANALOG_INPUT_SIZE;
        _samples[_index] = value;

        return value;
}

int Pot::read() {
        raw();

        int total = 0;
        for(int i = 0; i < SMOOTH_ANALOG_INPUT_SIZE; i++) {
                total += _samples[i];
        }

        int current = total / SMOOTH_ANALOG_INPUT_SIZE;
        return map(current, 0, 1024, _mapMin, _mapMax);
}
