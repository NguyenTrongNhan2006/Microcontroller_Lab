/**
  ******************************************************************************
  * @file           : exercise7.c
  * @brief          : Exercise 7 - Function clearAllClock()
  *                   Turn off all 12 LEDs connected from PA4 to PA15.
  ******************************************************************************
  */

#include "exercises.h"

void clearAllClock(void) {
    // TODO: Turn off all 12 clock LEDs (PA4 to PA15)
}

void exercise7_run(void) {
    // Test clearAllClock
    while (1) {
        clearAllClock();
        HAL_Delay(1000);
    }
}
