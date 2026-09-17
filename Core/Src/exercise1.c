/**
  * Exercise 1: Switch status of two LEDs (LED-RED on PA5, LED-YELLOW on PA6)
  * every 2 seconds.
  *
  * Hardware connections:
  * - PA5: LED-RED (Cathode to PA5, Anode to +3.3V) -> Active LOW
  * - PA6: LED-YELLOW (Cathode to PA6, Anode to +3.3V) -> Active LOW
  */

#include "exercise1.h"

void exercise1_init(void) {
    // TODO: Configure PA5 and PA6 as GPIO Output
}

void exercise1_run(void) {
    // TODO: Infinite loop switching two LEDs every 2 seconds
    /*
    while (1) {
        // TODO: Turn LED-RED ON, LED-YELLOW OFF
        HAL_Delay(2000);
        // TODO: Turn LED-RED OFF, LED-YELLOW ON
        HAL_Delay(2000);
    }
    */
}
