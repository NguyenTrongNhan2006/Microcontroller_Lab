#include "exercises.h"

/* Exercise 4: buffered four-digit scanning, 250 ms slots = 1 Hz frame. */
void exercise4_init(void)
{
    const int values[MAX_LED] = {1,2,3,4};
    for (int i = 0; i < MAX_LED; ++i) led_buffer[i] = values[i];
    scan_interrupt_reset();
}
void exercise4_tick(void) { scan_interrupt_tick(250, 4, 1); }
void exercise4_poll(void) { }
