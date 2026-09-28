#include "lab2.h"
uint8_t matrix_buffer[MAX_LED_MATRIX];
int index_led_matrix;
static const uint16_t column_enable[MAX_LED_MATRIX] = {
    GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_10, GPIO_PIN_11,
    GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15
};

void matrix_init_A(void)
{
    /* Each byte is a COLUMN. Bit 0 is top row (ROW0 = PB8). */
    static const uint8_t rows[8] = {0x18,0x24,0x42,0x42,0x7E,0x42,0x42,0x00};
    for (int col = 0; col < MAX_LED_MATRIX; ++col) {
        matrix_buffer[col] = 0;
        for (int row = 0; row < 8; ++row)
            if (rows[row] & (0x80u >> col))
                matrix_buffer[col] |= (uint8_t)(1u << row);
    }
    index_led_matrix = 0;
}

void updateLEDMatrix(int index)
{
    /* Reference circuit: columns pulled UP; ULN input HIGH shunts them LOW.
       Thus ENM LOW selects the column; rows are active LOW cathodes. */
    HAL_GPIO_WritePin(GPIOA, MATRIX_ENABLE_MASK, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, MATRIX_ROW_MASK, GPIO_PIN_SET);
    if (index < 0 || index >= MAX_LED_MATRIX) return;
    HAL_GPIO_WritePin(GPIOB, (uint16_t)(matrix_buffer[index] << 8), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, column_enable[index], GPIO_PIN_RESET);
}

void matrix_shift_left(uint32_t count)
{
    unsigned offset = count % MAX_LED_MATRIX;
    uint8_t previous[MAX_LED_MATRIX];
    for (int i = 0; i < MAX_LED_MATRIX; ++i) previous[i] = matrix_buffer[i];
    for (unsigned i = 0; i < MAX_LED_MATRIX; ++i)
        matrix_buffer[i] = previous[(i + offset) % MAX_LED_MATRIX];
}
