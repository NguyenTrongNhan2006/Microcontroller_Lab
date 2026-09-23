#include "exercises.h"

void clearNumberOnClock(int num)
{
    if (num >= 0 && num < 12) {
        HAL_GPIO_WritePin(GPIOA, (uint16_t)(GPIO_PIN_4 << num), GPIO_PIN_SET);
    }
}

void exercise9_run(void)
{
    while (1) {
        for (int i = 0; i < 12; ++i) setNumberOnClock(i);
        for (int i = 0; i < 12; ++i) {
            clearNumberOnClock(i);
            HAL_Delay(500);
        }
    }
}
