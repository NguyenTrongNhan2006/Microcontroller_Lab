#ifndef __EXERCISES_H
#define __EXERCISES_H

#include "stm32f1xx_hal.h"

/* Change this value from 1 to 10 to select the exercise to run. */
#ifndef LAB1_ACTIVE_EXERCISE
#define LAB1_ACTIVE_EXERCISE 1
#endif

void exercise1_init(void);
void exercise1_run(void);
void exercise2_init(void);
void exercise2_run(void);
void exercise3_init(void);
void exercise3_run(void);
void display7SEG(int num);
void exercise4_run(void);
void exercise5_run(void);
void exercise6_init(void);
void exercise6_run(void);
void clearAllClock(void);
void exercise7_run(void);
void setNumberOnClock(int num);
void exercise8_run(void);
void clearNumberOnClock(int num);
void exercise9_run(void);
void exercise10_run(void);

#endif
