/**
  ******************************************************************************
  * @file           : exercise8.c
  * @brief          : Exercise 8 - Function setNumberOnClock(int num)
  *                   Input: num from 0 to 11
  *                   Turn ON the appropriate LED corresponding to clock position num.
  ******************************************************************************
  */

#include "exercises.h"

void setNumberOnClock(int num) {
    // TODO: Turn on the LED corresponding to num (0 to 11)
}

void exercise8_run(void) {
    // Test setNumberOnClock
    while (1) {
        for (int i = 0; i < 12; i++) {
            setNumberOnClock(i);
            HAL_Delay(1000);
        }
    }
}
