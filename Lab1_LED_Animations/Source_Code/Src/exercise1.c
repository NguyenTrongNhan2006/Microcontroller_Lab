/**
  ******************************************************************************
  * @file           : exercise1.c
  * @brief          : Exercise 1 - 2 LEDs Alternating Blinky
  *                   Switch status of two LEDs every 2 seconds.
  *                   - LED-RED connected to PA5
  *                   - LED-YELLOW connected to PA6
  *                   (Negative pins connected to STM32 pins -> Active LOW)
  ******************************************************************************
  */

#include "exercises.h"

void exercise1_init(void) {
    // GPIO initialization is handled in MX_GPIO_Init() in main.c
}

void exercise1_run(void) {
    // TODO: Switch state of two LEDs every 2 seconds
    /*
    while (1) {
        // Step 1: LED-RED ON, LED-YELLOW OFF
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
        HAL_Delay(2000);

        // Step 2: LED-RED OFF, LED-YELLOW ON
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
        HAL_Delay(2000);
    }
    */
}
