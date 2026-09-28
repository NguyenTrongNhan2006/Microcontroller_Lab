#include "exercises.h"
void exercise5_init(void) { clock_init(); scan_interrupt_reset(); }
void exercise5_tick(void) { scan_interrupt_tick(LAB2_SCAN_SLOT_MS, 4, 1); }
/* Kept separately to show the blocking baseline in Exercise 5. */
void exercise5_poll(void) { HAL_Delay(1000); clock_advance(1); }
