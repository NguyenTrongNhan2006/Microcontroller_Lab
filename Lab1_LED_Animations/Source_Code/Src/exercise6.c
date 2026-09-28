#include "exercises.h"

void exercise6_init(void)
{
    HAL_GPIO_WritePin(GPIOA, 0xFFF0u, GPIO_PIN_SET);
}

void exercise6_run(void)
{
    while (1) {
        for (int i = 0; i < 12; ++i) {
            HAL_GPIO_WritePin(GPIOA, 0xFFF0u, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, (uint16_t)(GPIO_PIN_4 << i), GPIO_PIN_RESET);
            HAL_Delay(500);
        }
    }
}
