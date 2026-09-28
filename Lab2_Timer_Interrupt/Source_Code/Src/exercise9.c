#include "exercises.h"
void exercise9_init(void)
{
    exercise8_init();
    matrix_init_A();
    updateLEDMatrix(index_led_matrix++);
    timer_set_periodic(2, LAB2_MATRIX_SLOT_MS);
}
void exercise9_tick(void) { timer_run(); }
void exercise9_poll(void) { exercise8_poll(); service_matrix(); }
