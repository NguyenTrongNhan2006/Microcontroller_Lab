#ifndef SOFTWARE_TIMER_H
#define SOFTWARE_TIMER_H
#include "lab2.h"
#define TIMER_COUNT 4u
#define TIMER_CYCLE LAB2_TIMER_TICK_MS
extern volatile uint32_t timer0_counter;
extern volatile uint32_t timer0_flag;
void timers_reset(void);
/* Textbook one-shot: integer division, durations < TIMER_CYCLE do not fire. */
void setTimer0(int duration);
void timer_run(void);
int timer0_take(void);
/* Independent periodic timers, counts accumulated expirations until consumed. */
void timer_set_periodic(unsigned id, uint32_t duration_ms);
uint32_t timer_take(unsigned id);
#endif
