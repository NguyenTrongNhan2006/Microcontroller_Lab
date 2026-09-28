#include "exercises.h"

/* Exercise 1: two digits 1/2, 500 ms per slot. */
void exercise1_init(void)
{
    const int values[MAX_LED] = {1,2,0,0};
    for (int i = 0; i < MAX_LED; ++i) led_buffer[i] = values[i];
    scan_interrupt_reset();
}
void exercise1_tick(void) { scan_interrupt_tick(500, 2, 0); }
void exercise1_poll(void) { }
