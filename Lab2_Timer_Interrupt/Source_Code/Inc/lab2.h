#ifndef LAB2_H
#define LAB2_H
#include "stm32f1xx_hal.h"
#ifndef LAB2_ACTIVE_EXERCISE
#define LAB2_ACTIVE_EXERCISE 1
#endif
#ifndef LAB2_TIMER_TICK_MS
#define LAB2_TIMER_TICK_MS 10u
#endif
#ifndef LAB2_SCAN_SLOT_MS
#define LAB2_SCAN_SLOT_MS 250u
#endif
#ifndef LAB2_MATRIX_SLOT_MS
#define LAB2_MATRIX_SLOT_MS 10u
#endif
#if LAB2_ACTIVE_EXERCISE < 1 || LAB2_ACTIVE_EXERCISE > 10
#error "LAB2_ACTIVE_EXERCISE must be 1..10"
#endif
#if LAB2_TIMER_TICK_MS < 1 || LAB2_TIMER_TICK_MS > 65
#error "TIM2 tick must be 1..65 ms"
#endif
#if LAB2_SCAN_SLOT_MS < LAB2_TIMER_TICK_MS || LAB2_MATRIX_SLOT_MS < LAB2_TIMER_TICK_MS
#error "Scan slots cannot be shorter than the timer tick"
#endif
#define MAX_LED 4
#define MAX_LED_MATRIX 8
#define DOT_PIN GPIO_PIN_4
#define RED_PIN GPIO_PIN_5
#define SEGMENT_MASK ((uint16_t)0x007Fu)
#define DIGIT_ENABLE_MASK ((uint16_t)0x03C0u) /* EN0..3 = PA6..9, active LOW */
#define MATRIX_ENABLE_MASK ((uint16_t)0xFC0Cu) /* PA2,3,10..15, active LOW */
#define MATRIX_ROW_MASK ((uint16_t)0xFF00u)
extern volatile int led_buffer[MAX_LED];
extern uint8_t matrix_buffer[MAX_LED_MATRIX];
extern int index_led, index_led_matrix;
extern int hour, minute, second;
extern TIM_HandleTypeDef htim2;
void Error_Handler(void);
void lab2_init(void);
void lab2_tick(void);
void lab2_poll(void);
void display7SEG(int num);
void update7SEG(int index);
void disable7SEG(void);
void updateClockBuffer(void);
void clock_init(void);
void clock_advance(uint32_t seconds);
void updateLEDMatrix(int index);
void matrix_init_A(void);
void matrix_shift_left(uint32_t count);
void scan_interrupt_reset(void);
void scan_interrupt_tick(uint32_t slot_ms, unsigned digits, int blink_dot);
void service_clock(int toggle_dot);
void service_display(void);
void service_matrix(void);
#endif
