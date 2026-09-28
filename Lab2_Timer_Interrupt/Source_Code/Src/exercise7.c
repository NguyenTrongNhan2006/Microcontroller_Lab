#include "exercises.h"
void exercise7_init(void)
{
    clock_init(); scan_interrupt_reset();
    timer_set_periodic(0, 1000);
}
void exercise7_tick(void)
{
    timer_run();
    scan_interrupt_tick(LAB2_SCAN_SLOT_MS, 4, 0);
}
void exercise7_poll(void) { service_clock(1); }
