/* Host-side behavioral tests: real exercise sources, mocked GPIO and delay. */
#include <assert.h>
#include <limits.h>
#include <setjmp.h>
#include <stdio.h>
#include "exercises.h"

GPIO_TypeDef test_gpio_a, test_gpio_b;
static jmp_buf stop;
static unsigned current, step, limit;
static const uint16_t phases[] = {0x30C0, 0x28A0, 0x8610, 0x4510};
static const unsigned duration[] = {3000, 2000, 3000, 2000};
static const uint8_t digits[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void HAL_GPIO_WritePin(GPIO_TypeDef *port, uint16_t pins, GPIO_PinState value)
{
    assert(port == GPIOA || port == GPIOB);
    if (value == GPIO_PIN_SET) port->odr |= pins;
    else port->odr &= (uint16_t)~pins;
}

void HAL_Delay(uint32_t ms)
{
    uint16_t on = (uint16_t)~GPIOA->odr & 0xFFF0u;
    uint8_t segments = (uint8_t)~GPIOB->odr & 0x7Fu;
    switch (current) {
    case 1:
        assert(ms == 2000 && on == (step % 2 ? 0x40 : 0x20)); break;
    case 2: {
        const uint16_t pins[] = {0x20,0x80,0x40};
        const unsigned times[] = {5000,3000,2000};
        assert(on == pins[step % 3] && ms == times[step % 3]); break;
    }
    case 3:
        assert(on == phases[step % 4] && ms == duration[step % 4]); break;
    case 4:
        assert(ms == 1000 && segments == digits[step % 10]); break;
    case 5: {
        const unsigned phase[] = {0,0,0,1,1,2,2,2,3,3};
        const unsigned remaining[] = {3,2,1,2,1,3,2,1,2,1};
        assert(ms == 1000 && on == phases[phase[step % 10]]);
        assert(segments == digits[remaining[step % 10]]); break;
    }
    case 6:
        assert(ms == 500 && on == (uint16_t)(0x10u << (step % 12))); break;
    case 7:
        assert(ms == 1000 && on == 0); break;
    case 8:
        assert(ms == 500 && on == (uint16_t)(((1u << (step % 12 + 1)) - 1) << 4)); break;
    case 9:
        assert(ms == 500 && on == (uint16_t)(0xFFF0u & ~(((1u << (step % 12 + 1)) - 1) << 4))); break;
    case 10: {
        unsigned t = (10 * 3600 + 58 * 60 + step) % (12 * 3600);
        uint16_t expected = (uint16_t)((0x10u << (t / 3600)) |
            (0x10u << ((t / 60 % 60) / 5)) | (0x10u << ((t % 60) / 5)));
        assert(ms == 1000 && on == expected); break;
    }
    default: assert(0);
    }
    /* No exercise may touch PA0..3 or PB7..15. */
    assert((GPIOA->odr & 0xF) == 0x5);
    assert((GPIOB->odr & 0xFF80) == 0xA580);
    if (++step == limit) longjmp(stop, 1);
}

int main(void)
{
    void (*runs[])(void) = {exercise1_run,exercise2_run,exercise3_run,
        exercise4_run,exercise5_run,exercise6_run,exercise7_run,
        exercise8_run,exercise9_run,exercise10_run};
    GPIOA->odr = 0x0005;
    clearAllClock(); assert(GPIOA->odr == 0xFFF5);
    for (int n = 0; n < 12; ++n) {
        setNumberOnClock(n);
        assert(GPIOA->odr == (uint16_t)(0xFFF5u & ~(0x10u << n)));
        clearNumberOnClock(n); assert(GPIOA->odr == 0xFFF5);
    }
    const int invalid[] = {-1,12,INT_MIN,INT_MAX};
    for (unsigned n = 0; n < sizeof invalid / sizeof invalid[0]; ++n) {
        setNumberOnClock(invalid[n]); clearNumberOnClock(invalid[n]);
        assert(GPIOA->odr == 0xFFF5);
    }
    for (int n = 0; n < 10; ++n) {
        GPIOB->odr = 0xA580; display7SEG(n);
        assert(GPIOB->odr == (uint16_t)(0xA580u | (0x7Fu & ~digits[n])));
    }
    display7SEG(-1); assert(GPIOB->odr == 0xA5FF);
    display7SEG(10); assert(GPIOB->odr == 0xA5FF);
    for (current = 1; current <= 10; ++current) {
        GPIOA->odr = 0xFFF5; GPIOB->odr = 0xA5FF;
        if (current == 1) exercise1_init();
        if (current == 2) exercise2_init();
        if (current == 3) exercise3_init();
        if (current == 6) exercise6_init();
        step = 0; limit = current == 10 ? 43201 : 120;
        if (setjmp(stop) == 0) runs[current - 1]();
        printf("Exercise %u: PASS (%u delay states)\n", current, step);
    }
    puts("PASS: digit patterns, invalid inputs, unrelated GPIO preservation, 12-hour rollover.");
    return 0;
}
