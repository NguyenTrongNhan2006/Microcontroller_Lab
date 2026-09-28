#include "software_timer.h"
#include <limits.h>
volatile uint32_t timer0_counter;
volatile uint32_t timer0_flag;
typedef struct {
    volatile uint32_t counter, period, pending;
} SoftwareTimer;
static SoftwareTimer timers[TIMER_COUNT];

void timers_reset(void)
{
    uint32_t irq = __get_PRIMASK();
    __disable_irq();
    timer0_counter = timer0_flag = 0;
    for (unsigned i = 0; i < TIMER_COUNT; ++i)
        timers[i].counter = timers[i].period = timers[i].pending = 0;
    __set_PRIMASK(irq);
}

void setTimer0(int duration)
{
    uint32_t irq = __get_PRIMASK();
    __disable_irq();
    timer0_counter = duration > 0 ? (uint32_t)duration / TIMER_CYCLE : 0;
    timer0_flag = 0;
    __set_PRIMASK(irq);
}

int timer0_take(void)
{
    uint32_t irq = __get_PRIMASK();
    __disable_irq();
    int ready = timer0_flag != 0;
    timer0_flag = 0;
    __set_PRIMASK(irq);
    return ready;
}

void timer_set_periodic(unsigned id, uint32_t duration_ms)
{
    if (id >= TIMER_COUNT) return;
    /* Round UP: a nonzero timeout never expires earlier than requested. */
    uint32_t ticks = duration_ms / TIMER_CYCLE +
                     (duration_ms % TIMER_CYCLE != 0);
    uint32_t irq = __get_PRIMASK();
    __disable_irq();
    timers[id].counter = timers[id].period = ticks;
    timers[id].pending = 0;
    __set_PRIMASK(irq);
}

uint32_t timer_take(unsigned id)
{
    if (id >= TIMER_COUNT) return 0;
    uint32_t irq = __get_PRIMASK();
    __disable_irq();
    uint32_t pending = timers[id].pending;
    timers[id].pending = 0;
    __set_PRIMASK(irq);
    return pending;
}

/* Called only by TIM2 ISR; no display writes, division or HAL_Delay here. */
void timer_run(void)
{
    if (timer0_counter > 0 && --timer0_counter == 0) timer0_flag = 1;
    for (unsigned i = 0; i < TIMER_COUNT; ++i) {
        if (timers[i].counter > 0 && --timers[i].counter == 0) {
            if (timers[i].pending != UINT32_MAX) ++timers[i].pending;
            timers[i].counter = timers[i].period;
        }
    }
}
