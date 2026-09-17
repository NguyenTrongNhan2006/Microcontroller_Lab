/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c
  *                   HCMUT - Microcontroller Lab 1: LED Animations
  *                   Instructor: Dr. Le Trong Nhan
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "exercises.h"

/* Pin definitions */
#define LED_RED_Pin            GPIO_PIN_5
#define LED_RED_GPIO_Port      GPIOA
#define LED_YELLOW_Pin         GPIO_PIN_6
#define LED_YELLOW_GPIO_Port   GPIOA
#define LED_GREEN_Pin          GPIO_PIN_7
#define LED_GREEN_GPIO_Port    GPIOA

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
