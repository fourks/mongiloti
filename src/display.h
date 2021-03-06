#ifndef DISPLAY_H
#define DISPLAY_H

#include "all.h"
#include "logo.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"


void drawScreen();
void drawDial(int x, int y, int r, int value);
void setupDisplay();
void updateDisplay();

#endif /* end of include guard:  */
