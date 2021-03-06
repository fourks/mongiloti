#include "all.h"

#define CPU_RESTART_ADDR (uint32_t *)0xE000ED0C
#define CPU_RESTART_VAL 0x5FA0004
#define CPU_RESTART (*CPU_RESTART_ADDR = CPU_RESTART_VAL);

extern int menuIndex;
extern bool drawn;

//set Encoder pins
Encoder myEnc(7, 6);
long oldEncoderPosition  = 0;
long newEncoderPosition = 0;

void processButton(){

        // read button
        if (digitalRead(BUTTON) == HIGH) {
                //draw("button pressed");
                Serial.print("Button Pressed\n\r");
                CPU_RESTART
                //ms.select();
                //draw();
        } else {
                // Serial.println("Button Not Pressed");
        }
}

void processEncoder(){

        newEncoderPosition = myEnc.read()/4;
        if (newEncoderPosition != oldEncoderPosition) {
                oldEncoderPosition = newEncoderPosition;
                Serial.print(newEncoderPosition);
                Serial.printf(" ");
                menuIndex++;
                if (menuIndex == MENU_COUNT){ menuIndex=0;}
                //drawn = false;
                //ms.next();
                //draw();
        }
}

void setupButton(){
        // init button - PULLDOWN
        pinMode(BUTTON, INPUT_PULLDOWN);
}
