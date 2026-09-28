#ifndef TEST_HAL_H
#define TEST_HAL_H
#include <stdint.h>
typedef struct { uint16_t odr; } GPIO_TypeDef;
typedef enum { GPIO_PIN_RESET, GPIO_PIN_SET } GPIO_PinState;
typedef struct { void *Instance; } TIM_HandleTypeDef;
extern GPIO_TypeDef test_gpio_a, test_gpio_b;
#define GPIOA (&test_gpio_a)
#define GPIOB (&test_gpio_b)
#define TIM2 ((void *)(uintptr_t)2)
#define GPIO_PIN_0 ((uint16_t)0x0001u)
#define GPIO_PIN_1 ((uint16_t)0x0002u)
#define GPIO_PIN_2 ((uint16_t)0x0004u)
#define GPIO_PIN_3 ((uint16_t)0x0008u)
#define GPIO_PIN_4 ((uint16_t)0x0010u)
#define GPIO_PIN_5 ((uint16_t)0x0020u)
#define GPIO_PIN_6 ((uint16_t)0x0040u)
#define GPIO_PIN_7 ((uint16_t)0x0080u)
#define GPIO_PIN_8 ((uint16_t)0x0100u)
#define GPIO_PIN_9 ((uint16_t)0x0200u)
#define GPIO_PIN_10 ((uint16_t)0x0400u)
#define GPIO_PIN_11 ((uint16_t)0x0800u)
#define GPIO_PIN_12 ((uint16_t)0x1000u)
#define GPIO_PIN_13 ((uint16_t)0x2000u)
#define GPIO_PIN_14 ((uint16_t)0x4000u)
#define GPIO_PIN_15 ((uint16_t)0x8000u)
void HAL_GPIO_WritePin(GPIO_TypeDef *port, uint16_t pins, GPIO_PinState value);
void HAL_GPIO_TogglePin(GPIO_TypeDef *port, uint16_t pins);
void HAL_Delay(uint32_t ms);
uint32_t __get_PRIMASK(void);
void __disable_irq(void);
void __set_PRIMASK(uint32_t value);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif
