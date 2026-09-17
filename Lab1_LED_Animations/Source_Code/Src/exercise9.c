/**
  ******************************************************************************
  * @file           : exercise9.c
  * @brief          : Exercise 9 - Function clearNumberOnClock(int num)
  *                   Input: num from 0 to 11
  *                   Turn OFF the appropriate LED corresponding to clock position num.
  ******************************************************************************
  */

#include "exercises.h"

void clearNumberOnClock(int num) {
    // TODO: Turn off the LED corresponding to num (0 to 11)
}

void exercise9_run(void) {
    // Test clearNumberOnClock
    while (1) {
        for (int i = 0; i < 12; i++) {
            clearNumberOnClock(i);
            HAL_Delay(1000);
        }
    }
}
