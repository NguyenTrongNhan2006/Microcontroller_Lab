#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "exercises.h"

GPIO_TypeDef test_gpio_a = {0xFFFF}, test_gpio_b = {0xFFFF};
TIM_HandleTypeDef htim2 = {TIM2};
static uint32_t irq_mask;
static int in_isr;
static unsigned delay_calls, gpio_writes;
uint32_t __get_PRIMASK(void) { return irq_mask; }
void __disable_irq(void) { irq_mask = 1; }
void __set_PRIMASK(uint32_t value) { irq_mask = value; }

void HAL_GPIO_WritePin(GPIO_TypeDef *port, uint16_t pins, GPIO_PinState value)
{
    assert(port == GPIOA || port == GPIOB);
#if LAB2_ACTIVE_EXERCISE >= 8
    assert(!in_isr); /* No display/GPIO work in ISR in exercises 8..10. */
#endif
    if (port == GPIOB) {
        if (pins & SEGMENT_MASK)
            assert((GPIOA->odr & DIGIT_ENABLE_MASK) == DIGIT_ENABLE_MASK);
        if (pins & MATRIX_ROW_MASK)
            assert((GPIOA->odr & MATRIX_ENABLE_MASK) == MATRIX_ENABLE_MASK);
    }
    ++gpio_writes;
    if (value == GPIO_PIN_SET) port->odr |= pins;
    else port->odr &= (uint16_t)~pins;
}
void HAL_GPIO_TogglePin(GPIO_TypeDef *port, uint16_t pins)
{
#if LAB2_ACTIVE_EXERCISE >= 8
    assert(!in_isr);
#endif
    ++gpio_writes;
    port->odr ^= pins;
}
static void interrupt_tick(void)
{
    assert(!irq_mask);
    in_isr = 1;
    HAL_TIM_PeriodElapsedCallback(&htim2);
    in_isr = 0;
}
void HAL_Delay(uint32_t ms)
{
    assert(LAB2_ACTIVE_EXERCISE == 5 && !in_isr);
    assert(ms == 1000);
    ++delay_calls;
    for (uint32_t t = 0; t < ms / LAB2_TIMER_TICK_MS; ++t) interrupt_tick();
}
#if LAB2_ACTIVE_EXERCISE != 5
static void ticks(unsigned count, int poll)
{
    while (count--) {
        interrupt_tick();
        if (poll) lab2_poll();
    }
}
#endif
static int enabled_digit(void)
{
    for (int i = 0; i < 4; ++i)
        if (!(GPIOA->odr & (GPIO_PIN_6 << i))) {
            assert(((uint16_t)~GPIOA->odr & DIGIT_ENABLE_MASK) == (GPIO_PIN_6 << i));
            return i;
        }
    return -1;
}
static void test_timers(void)
{
    timers_reset();
    for (int i = 0; i < 200; ++i) timer_run();
    assert(!timer0_flag); /* No setTimer0: never starts. */
    setTimer0(1);
    for (int i = 0; i < 10; ++i) timer_run();
    assert(!timer0_flag); /* Textbook floor(1/10) = 0. */
    setTimer0(10);
    timer_run(); assert(timer0_flag && timer0_take());
    assert(!timer0_take());
    setTimer0(1000);
    for (int i = 0; i < 99; ++i) timer_run();
    assert(!timer0_flag && timer0_counter == 1);
    timer_run(); assert(timer0_take());
    setTimer0(-10); assert(timer0_counter == 0);
    timer_set_periodic(0, 25); /* Rounded UP to 3 ticks. */
    for (int i = 0; i < 10; ++i) timer_run();
    assert(timer_take(0) == 3 && timer_take(0) == 0);
    timer_set_periodic(0, 0);
    timer_run(); assert(timer_take(0) == 0);
    timer_set_periodic(4, 10); assert(timer_take(4) == 0);
    irq_mask = 1;
    setTimer0(1000); timer_set_periodic(0, 1000);
    (void)timer_take(0); (void)timer0_take(); timers_reset();
    assert(irq_mask == 1); irq_mask = 0;
}
static void test_display_clock_matrix(void)
{
    const uint8_t digits[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
    GPIOA->odr = 0xFFFF; GPIOB->odr = 0xFFFF;
    for (int d = 0; d < 10; ++d)
        for (int i = 0; i < 4; ++i) {
            led_buffer[i] = d;
            update7SEG(i);
            assert(enabled_digit() == i);
            assert(((uint16_t)~GPIOB->odr & SEGMENT_MASK) == digits[d]);
            assert((GPIOA->odr & (uint16_t)~DIGIT_ENABLE_MASK) ==
                   ((uint16_t)~DIGIT_ENABLE_MASK));
            assert((GPIOB->odr & (uint16_t)~SEGMENT_MASK) ==
                   ((uint16_t)~SEGMENT_MASK));
        }
    update7SEG(-1); assert(enabled_digit() == -1);
    update7SEG(4); assert(enabled_digit() == -1);
    led_buffer[0] = 10; update7SEG(0); assert(enabled_digit() == -1);
    led_buffer[0] = -1; update7SEG(0); assert(enabled_digit() == -1);
    hour = 7; minute = 3; second = 0;
    irq_mask = 1; updateClockBuffer(); assert(irq_mask == 1); irq_mask = 0;
    assert(led_buffer[0] == 0 && led_buffer[1] == 7 &&
           led_buffer[2] == 0 && led_buffer[3] == 3);
    hour = 23; minute = 59; second = 59;
    clock_advance(1); assert(hour == 0 && minute == 0 && second == 0);
    clock_advance(86400 + 3661);
    assert(hour == 1 && minute == 1 && second == 1);
    matrix_init_A();
    const uint8_t rows[] = {0x18,0x24,0x42,0x42,0x7E,0x42,0x42,0x00};
    for (int row = 0; row < 8; ++row) {
        unsigned rendered = 0;
        for (int col = 0; col < 8; ++col)
            if (matrix_buffer[col] & (1u << row)) rendered |= 0x80u >> col;
        assert(rendered == rows[row]);
    }
    const uint16_t columns[] = {0x4,0x8,0x400,0x800,0x1000,0x2000,0x4000,0x8000};
    for (int col = 0; col < 8; ++col) {
        uint16_t saved_segments = GPIOB->odr & 0xFF;
        updateLEDMatrix(col);
        assert(((uint16_t)~GPIOA->odr & MATRIX_ENABLE_MASK) == columns[col]);
        assert(((uint16_t)~GPIOB->odr >> 8) == matrix_buffer[col]);
        assert((GPIOB->odr & 0xFF) == saved_segments);
    }
    updateLEDMatrix(-1); assert((GPIOA->odr & MATRIX_ENABLE_MASK) == MATRIX_ENABLE_MASK);
    updateLEDMatrix(8); assert((GPIOB->odr & MATRIX_ROW_MASK) == MATRIX_ROW_MASK);
    uint8_t original[8]; memcpy(original, matrix_buffer, 8);
    matrix_shift_left(1);
    for (int col = 0; col < 8; ++col) assert(matrix_buffer[col] == original[(col + 1) % 8]);
    matrix_shift_left(7); assert(memcmp(original, matrix_buffer, 8) == 0);
}
int main(void)
{
    test_timers();
    test_display_clock_matrix();
    GPIOA->odr = GPIOB->odr = 0xFFFF;
    lab2_init();
    assert(enabled_digit() == 0);
    unsigned before = gpio_writes;
    TIM_HandleTypeDef other = {(void *)(uintptr_t)3};
    HAL_TIM_PeriodElapsedCallback(&other);
    assert(gpio_writes == before);
#if LAB2_ACTIVE_EXERCISE == 5
    for (int i = 0; i < 120; ++i) lab2_poll();
    assert(delay_calls == 120);
    assert(hour == 15 && minute == 10 && second == 50);
#else
    for (unsigned t = 1; t <= 500; ++t) {
        ticks(1, 1);
#if LAB2_ACTIVE_EXERCISE <= 3
        unsigned slot_ticks = 50;
#else
        unsigned slot_ticks = 25;
#endif
#if LAB2_ACTIVE_EXERCISE == 1
        assert(enabled_digit() == (int)(t / slot_ticks % 2));
#else
        assert(enabled_digit() == (int)(t / slot_ticks % 4));
#endif
#if LAB2_ACTIVE_EXERCISE >= 2
        assert((GPIOA->odr & DOT_PIN) == ((t / 100 % 2) ? 0 : DOT_PIN));
#endif
#if LAB2_ACTIVE_EXERCISE >= 6
        assert(hour == 15 && minute == 8 && second == 50 + (int)(t / 100));
#endif
#if LAB2_ACTIVE_EXERCISE == 6
        assert((GPIOA->odr & RED_PIN) == ((t >= 100 && t < 300) || t >= 500 ? 0 : RED_PIN));
#endif
    }
    assert(delay_calls == 0);
#if LAB2_ACTIVE_EXERCISE >= 8
    /* Busy foreground: periodic clock events accumulate, scanning skips backlog. */
    ticks(500, 0);
    lab2_poll();
    assert(hour == 15 && minute == 9 && second == 0);
    assert(enabled_digit() == 0);
    assert(GPIOA->odr & DOT_PIN);
#endif
#if LAB2_ACTIVE_EXERCISE >= 7
    hour = 23; minute = 59; second = 59;
    ticks(100, 1);
    assert(hour == 0 && minute == 0 && second == 0);
#endif
#if LAB2_ACTIVE_EXERCISE == 9
    uint8_t fixed[8]; memcpy(fixed, matrix_buffer, 8);
    ticks(200, 1); assert(memcmp(fixed, matrix_buffer, 8) == 0);
#elif LAB2_ACTIVE_EXERCISE == 10
    uint8_t previous[8]; memcpy(previous, matrix_buffer, 8);
    ticks(50, 1);
    for (int col = 0; col < 8; ++col) assert(matrix_buffer[col] == previous[(col + 1) % 8]);
#endif
#endif
    assert(!irq_mask);
    printf("Exercise %d PASS: timing, scanning, ghosting prevention, timer/clock/matrix checks.\n", LAB2_ACTIVE_EXERCISE);
    return 0;
}
