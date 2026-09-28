#include "exercises.h"

void service_clock(int toggle_dot)
{
    uint32_t events = timer_take(0);
    if (events) {
        clock_advance(events);
        if (toggle_dot && (events & 1u)) HAL_GPIO_TogglePin(GPIOA, DOT_PIN);
    }
}

void service_display(void)
{
    uint32_t slots = timer_take(1);
    if (slots) {
        /* Skip expired scan slots after a busy foreground, keep phase. */
        index_led = (index_led + (int)((slots - 1) % MAX_LED)) % MAX_LED;
        update7SEG(index_led);
        index_led = (index_led + 1) % MAX_LED;
    }
}

void service_matrix(void)
{
    uint32_t slots = timer_take(2);
    if (slots) {
        index_led_matrix = (index_led_matrix +
            (int)((slots - 1) % MAX_LED_MATRIX)) % MAX_LED_MATRIX;
        updateLEDMatrix(index_led_matrix);
        index_led_matrix = (index_led_matrix + 1) % MAX_LED_MATRIX;
    }
}
