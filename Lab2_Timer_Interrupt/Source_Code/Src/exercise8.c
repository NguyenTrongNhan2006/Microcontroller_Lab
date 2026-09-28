#include "exercises.h"
void exercise8_init(void)
{
    clock_init();
    index_led = 0;
    update7SEG(index_led++);
    timer_set_periodic(0, 1000);
    timer_set_periodic(1, LAB2_SCAN_SLOT_MS);
}
void exercise8_tick(void) { timer_run(); }
void exercise8_poll(void) { service_clock(1); service_display(); }
