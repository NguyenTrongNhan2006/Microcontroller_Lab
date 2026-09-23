#include "exercises.h"

static void traffic_set(uint16_t on_pin)
{
    const uint16_t all = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_WritePin(GPIOA, all, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, on_pin, GPIO_PIN_RESET);
}

void exercise2_init(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_SET);
}

void exercise2_run(void)
{
    while (1) {
        traffic_set(GPIO_PIN_5); HAL_Delay(5000);
        traffic_set(GPIO_PIN_7); HAL_Delay(3000);
        traffic_set(GPIO_PIN_6); HAL_Delay(2000);
    }
}
