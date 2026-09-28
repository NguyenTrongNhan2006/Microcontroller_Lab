#include "exercises.h"
void exercise10_init(void)
{
    exercise9_init();
    timer_set_periodic(3, 500);
}
void exercise10_tick(void) { timer_run(); }
void exercise10_poll(void)
{
    exercise8_poll();
    uint32_t steps = timer_take(3);
    if (steps) matrix_shift_left(steps);
    service_matrix();
}
