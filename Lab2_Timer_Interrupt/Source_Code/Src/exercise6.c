#include "exercises.h"
void exercise6_init(void)
{
    clock_init(); scan_interrupt_reset();
    setTimer0(1000);
    timer_set_periodic(1, 1000);
}
void exercise6_tick(void)
{
    timer_run();
    scan_interrupt_tick(LAB2_SCAN_SLOT_MS, 4, 1);
}
void exercise6_poll(void)
{
    if (timer0_take()) {
        HAL_GPIO_TogglePin(GPIOA, RED_PIN);
        setTimer0(2000);
    }
    uint32_t elapsed = timer_take(1);
    if (elapsed) clock_advance(elapsed);
}
