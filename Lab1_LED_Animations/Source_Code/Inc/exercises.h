/**
  ******************************************************************************
  * @file           : exercises.h
  * @brief          : Prototypes for all 10 exercises in Lab 1
  *                   HCMUT - Computer Engineering | Dr. Le Trong Nhan
  ******************************************************************************
  */

#ifndef __EXERCISES_H
#define __EXERCISES_H

#include "stm32f1xx_hal.h"

/* Exercise 1: 2 LEDs Alternating Blinky (PA5, PA6) */
void exercise1_init(void);
void exercise1_run(void);

/* Exercise 2: Single Traffic Light (PA5 RED, PA6 YELLOW, PA7 GREEN) */
void exercise2_init(void);
void exercise2_run(void);

/* Exercise 3: 4-Way Traffic Light (12 LEDs) */
void exercise3_init(void);
void exercise3_run(void);

/* Exercise 4: 7-Segment Common Anode Display (PB0..PB6) */
void display7SEG(int num);
void exercise4_run(void);

/* Exercise 5: 4-Way Traffic Light + 7-Segment Countdown */
void exercise5_run(void);

/* Exercise 6: Analog Clock - 12 LEDs Connection Sequence Test (PA4..PA15) */
void exercise6_init(void);
void exercise6_run(void);

/* Exercise 7: Turn off all 12 clock LEDs */
void clearAllClock(void);
void exercise7_run(void);

/* Exercise 8: Turn ON LED at clock position num (0..11) */
void setNumberOnClock(int num);
void exercise8_run(void);

/* Exercise 9: Turn OFF LED at clock position num (0..11) */
void clearNumberOnClock(int num);
void exercise9_run(void);

/* Exercise 10: Analog Clock Full Integration (Hour, Minute, Second) */
void exercise10_run(void);

#endif /* __EXERCISES_H */
