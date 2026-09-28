#include "exercises.h"

/* Exercise 2: 12:30, four 500 ms slots and DOT. */
void exercise2_init(void)
{
    const int values[MAX_LED] = {1,2,3,0};
    for (int i = 0; i < MAX_LED; ++i) led_buffer[i] = values[i];
    scan_interrupt_reset();
}
void exercise2_tick(void) { scan_interrupt_tick(500, 4, 1); }
void exercise2_poll(void) { }
