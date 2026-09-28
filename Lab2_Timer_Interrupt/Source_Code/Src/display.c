#include "lab2.h"
volatile int led_buffer[MAX_LED] = {1, 2, 3, 4};
int index_led;
static uint32_t scan_ms, dot_ms;
static const uint16_t enable_pins[MAX_LED] = {
    GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9
};

void disable7SEG(void)
{
    HAL_GPIO_WritePin(GPIOA, DIGIT_ENABLE_MASK, GPIO_PIN_SET);
}

void display7SEG(int num)
{
    static const uint8_t digits[10] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
    };
    HAL_GPIO_WritePin(GPIOB, SEGMENT_MASK, GPIO_PIN_SET);
    if (num >= 0 && num < 10)
        HAL_GPIO_WritePin(GPIOB, digits[num], GPIO_PIN_RESET);
}

void update7SEG(int index)
{
    /* Blank ALL anodes before changing shared segment data (avoid ghosting). */
    disable7SEG();
    if (index < 0 || index >= MAX_LED) return;
    int digit = led_buffer[index];
    display7SEG(digit);
    if (digit >= 0 && digit < 10)
        HAL_GPIO_WritePin(GPIOA, enable_pins[index], GPIO_PIN_RESET);
}

void scan_interrupt_reset(void)
{
    scan_ms = dot_ms = 0;
    index_led = 0;
    update7SEG(index_led);
}

void scan_interrupt_tick(uint32_t slot_ms, unsigned digits, int blink_dot)
{
    scan_ms += LAB2_TIMER_TICK_MS;
    if (scan_ms >= slot_ms) {
        scan_ms -= slot_ms;
        index_led = (index_led + 1) % (int)digits;
        update7SEG(index_led);
    }
    if (blink_dot) {
        dot_ms += LAB2_TIMER_TICK_MS;
        if (dot_ms >= 1000) {
            dot_ms -= 1000;
            HAL_GPIO_TogglePin(GPIOA, DOT_PIN);
        }
    }
}
