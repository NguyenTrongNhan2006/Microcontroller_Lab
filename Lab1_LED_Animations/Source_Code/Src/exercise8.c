#include "exercises.h"

void setNumberOnClock(int num)
{
    if (num >= 0 && num < 12) {
        HAL_GPIO_WritePin(GPIOA, (uint16_t)(GPIO_PIN_4 << num), GPIO_PIN_RESET);
    }
}

void exercise8_run(void)
{
    while (1) {
        clearAllClock();
        for (int i = 0; i < 12; ++i) {
            setNumberOnClock(i);
            HAL_Delay(500);
        }
    }
}
