/**
  * Exercise 4: 7-Segment LED Display (7SEG-COM-ANODE)
  * Connected to PB0 to PB6 (segments a to g).
  * Common Anode: logic 0 (0V) turns ON segment.
  *
  * Implement function: void display7SEG(int num);
  * num is in range 0 to 9.
  */

#include "exercise4.h"

void display7SEG(int num) {
    // TODO: Implement decoding logic for 7SEG Common Anode (PB0..PB6)
    // 0: ON, 1: OFF
}

void exercise4_run(void) {
    int counter = 0;
    while (1) {
        if (counter >= 10) counter = 0;
        display7SEG(counter++);
        HAL_Delay(1000);
    }
}
