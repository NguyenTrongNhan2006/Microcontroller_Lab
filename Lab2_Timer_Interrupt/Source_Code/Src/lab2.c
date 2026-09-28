#include "exercises.h"
#define EX_FN_INNER(n, suffix) exercise##n##_##suffix
#define EX_FN(n, suffix) EX_FN_INNER(n, suffix)

void lab2_init(void)
{
    timers_reset();
    HAL_GPIO_WritePin(GPIOA, DOT_PIN | RED_PIN | DIGIT_ENABLE_MASK |
                     MATRIX_ENABLE_MASK, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, SEGMENT_MASK | MATRIX_ROW_MASK, GPIO_PIN_SET);
    EX_FN(LAB2_ACTIVE_EXERCISE, init)();
}
void lab2_tick(void) { EX_FN(LAB2_ACTIVE_EXERCISE, tick)(); }
void lab2_poll(void) { EX_FN(LAB2_ACTIVE_EXERCISE, poll)(); }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2) lab2_tick();
}
