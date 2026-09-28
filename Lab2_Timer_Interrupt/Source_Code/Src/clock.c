#include "lab2.h"
int hour = 15, minute = 8, second = 50;

void updateClockBuffer(void)
{
    int digits[MAX_LED] = {hour / 10, hour % 10, minute / 10, minute % 10};
    /* The scan ISR must never see only half of a new HH:MM buffer. */
    uint32_t irq = __get_PRIMASK();
    __disable_irq();
    for (int i = 0; i < MAX_LED; ++i) led_buffer[i] = digits[i];
    __set_PRIMASK(irq);
}

void clock_init(void)
{
    hour = 15; minute = 8; second = 50;
    updateClockBuffer();
}

void clock_advance(uint32_t seconds)
{
    uint32_t value = (uint32_t)(hour * 3600 + minute * 60 + second);
    value = (value + seconds % 86400u) % 86400u;
    hour = (int)(value / 3600);
    minute = (int)(value / 60 % 60);
    second = (int)(value % 60);
    updateClockBuffer();
}
