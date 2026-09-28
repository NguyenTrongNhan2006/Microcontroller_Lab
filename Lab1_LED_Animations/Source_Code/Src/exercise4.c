#include "exercises.h"

void display7SEG(int num)
{
    /* Bit 0..6 = a..g. A 1 in this table means that the segment is ON. */
    static const uint8_t digits[10] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66,
        0x6D, 0x7D, 0x07, 0x7F, 0x6F
    };
    const uint16_t all = 0x007Fu;
    uint16_t on_mask;

    if (num < 0 || num > 9) {
        HAL_GPIO_WritePin(GPIOB, all, GPIO_PIN_SET);
        return;
    }

    on_mask = digits[num];
    HAL_GPIO_WritePin(GPIOB, all, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, on_mask, GPIO_PIN_RESET);
}

void exercise4_run(void)
{
    int counter = 0;
    while (1) {
        display7SEG(counter);
        counter = (counter + 1) % 10;
        HAL_Delay(1000);
    }
}
