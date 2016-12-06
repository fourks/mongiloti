
#include "all.h"

int menuIndex = 0;
bool drawn = true;

void setup()   {
        //???
        analogReadResolution(7);
        analogReadAveraging(8);

        //setups
        setupTrellis();
        setupDisplay();
        delay(1000); //display logo

        setupButton();
        setupPots();

        //update the display
        MIDI.begin();
}

void loop() {

        //if anything under current MenuItem has changed then.
        //redraw menu
        if (!drawn) {
                drawMenu(menuIndex);
        }

        updateState();
        //display the currently set screen
        updateDisplay();
}
