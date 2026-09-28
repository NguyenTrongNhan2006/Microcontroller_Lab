#include "exercises.h"

/* Exercise 3: buffered four-digit scanning. */
void exercise3_init(void)
{
    const int values[MAX_LED] = {1,2,3,4};
    for (int i = 0; i < MAX_LED; ++i) led_buffer[i] = values[i];
    scan_interrupt_reset();
}
void exercise3_tick(void) { scan_interrupt_tick(500, 4, 1); }
void exercise3_poll(void) { }
