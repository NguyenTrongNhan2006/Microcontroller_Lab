#include "exercises.h"

void clearAllClock(void)
{
    HAL_GPIO_WritePin(GPIOA, 0xFFF0u, GPIO_PIN_SET);
}

void exercise7_run(void)
{
    while (1) {
        clearAllClock();
        HAL_Delay(1000);
    }
}
