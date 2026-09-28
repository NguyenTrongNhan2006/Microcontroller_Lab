#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

#if LAB1_ACTIVE_EXERCISE == 1
    exercise1_init(); exercise1_run();
#elif LAB1_ACTIVE_EXERCISE == 2
    exercise2_init(); exercise2_run();
#elif LAB1_ACTIVE_EXERCISE == 3
    exercise3_init(); exercise3_run();
#elif LAB1_ACTIVE_EXERCISE == 4
    exercise4_run();
#elif LAB1_ACTIVE_EXERCISE == 5
    exercise5_run();
#elif LAB1_ACTIVE_EXERCISE == 6
    exercise6_init(); exercise6_run();
#elif LAB1_ACTIVE_EXERCISE == 7
    exercise7_run();
#elif LAB1_ACTIVE_EXERCISE == 8
    exercise8_run();
#elif LAB1_ACTIVE_EXERCISE == 9
    exercise9_run();
#elif LAB1_ACTIVE_EXERCISE == 10
    exercise10_run();
#else
#error "LAB1_ACTIVE_EXERCISE must be from 1 to 10"
#endif

    while (1) { }
}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    osc.HSIState = RCC_HSI_ON;
    osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    osc.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&osc) != HAL_OK) Error_Handler();

    clk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                    RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV1;
    clk.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_0) != HAL_OK) Error_Handler();
}

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef gpio = {0};
    const uint16_t clock_pins = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |
        GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
        GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    const uint16_t segment_pins = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
        GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;

    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* PA13..PA15 are used by the lab, so release all JTAG/SWD pins. */
    __HAL_AFIO_REMAP_SWJ_DISABLE();

    /* All LEDs and common-anode segments are active LOW: SET means OFF. */
    HAL_GPIO_WritePin(GPIOA, clock_pins, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, segment_pins, GPIO_PIN_SET);

    gpio.Pin = clock_pins;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpio);

    gpio.Pin = segment_pins;
    HAL_GPIO_Init(GPIOB, &gpio);
}

void Error_Handler(void)
{
    __disable_irq();
    while (1) { }
}
