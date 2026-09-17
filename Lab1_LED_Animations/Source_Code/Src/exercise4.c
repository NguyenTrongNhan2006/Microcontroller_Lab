/**
  ******************************************************************************
  * @file           : exercise4.c
  * @brief          : Exercise 4 - 7-Segment Display (7SEG-COM-ANODE)
  *                   Connected to PB0 to PB6 (segments a through g).
  *                   Common Anode -> Logic 0 (0V) turns segment ON.
  *                   Function: display7SEG(int num) with num from 0 to 9.
  ******************************************************************************
  */

#include "exercises.h"

void display7SEG(int num) {
    // TODO: Implement 7-Segment Common Anode decoding (PB0=a .. PB6=g)
    // 0 turns segment ON, 1 turns segment OFF
}

void exercise4_run(void) {
    int counter = 0;
    while (1) {
        if (counter >= 10) counter = 0;
        display7SEG(counter++);
        HAL_Delay(1000);
    }
}
