#include "exercises.h"

static const uint16_t NS_RED = GPIO_PIN_4 | GPIO_PIN_10;
static const uint16_t NS_YELLOW = GPIO_PIN_5 | GPIO_PIN_11;
static const uint16_t NS_GREEN = GPIO_PIN_6 | GPIO_PIN_12;
static const uint16_t EW_RED = GPIO_PIN_7 | GPIO_PIN_13;
static const uint16_t EW_YELLOW = GPIO_PIN_8 | GPIO_PIN_14;
static const uint16_t EW_GREEN = GPIO_PIN_9 | GPIO_PIN_15;

static void show_phase(uint16_t active, int seconds)
{
    HAL_GPIO_WritePin(GPIOA, 0xFFF0u, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, active, GPIO_PIN_RESET);
    for (int remaining = seconds; remaining > 0; --remaining) {
        display7SEG(remaining);
        HAL_Delay(1000);
    }
}

void exercise5_run(void)
{
    while (1) {
        show_phase(NS_GREEN | EW_RED, 3);
        show_phase(NS_YELLOW | EW_RED, 2);
        show_phase(NS_RED | EW_GREEN, 3);
        show_phase(NS_RED | EW_YELLOW, 2);
    }
}
