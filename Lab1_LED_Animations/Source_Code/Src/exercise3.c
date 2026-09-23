#include "exercises.h"

/* N: PA4/5/6, E: PA7/8/9, S: PA10/11/12, W: PA13/14/15 (R/Y/G). */
static const uint16_t NS_RED = GPIO_PIN_4 | GPIO_PIN_10;
static const uint16_t NS_YELLOW = GPIO_PIN_5 | GPIO_PIN_11;
static const uint16_t NS_GREEN = GPIO_PIN_6 | GPIO_PIN_12;
static const uint16_t EW_RED = GPIO_PIN_7 | GPIO_PIN_13;
static const uint16_t EW_YELLOW = GPIO_PIN_8 | GPIO_PIN_14;
static const uint16_t EW_GREEN = GPIO_PIN_9 | GPIO_PIN_15;

static void four_way_set(uint16_t active)
{
    HAL_GPIO_WritePin(GPIOA, 0xFFF0u, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, active, GPIO_PIN_RESET);
}

void exercise3_init(void)
{
    HAL_GPIO_WritePin(GPIOA, 0xFFF0u, GPIO_PIN_SET);
}

void exercise3_run(void)
{
    while (1) {
        four_way_set(NS_GREEN | EW_RED);    HAL_Delay(3000);
        four_way_set(NS_YELLOW | EW_RED);   HAL_Delay(2000);
        four_way_set(NS_RED | EW_GREEN);    HAL_Delay(3000);
        four_way_set(NS_RED | EW_YELLOW);   HAL_Delay(2000);
    }
}
