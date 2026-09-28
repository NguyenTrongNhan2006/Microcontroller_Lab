#include "exercises.h"

void exercise10_run(void)
{
    int hour = 10;
    int minute = 58;
    int second = 0;

    while (1) {
        /* A 12-position display quantizes the hour hand to the current hour. */
        int hour_position = hour % 12;
        int minute_position = minute / 5;
        int second_position = second / 5;

        /* Hands sharing a position share one LED: 1 to 3 distinct LEDs light. */
        clearAllClock();
        setNumberOnClock(hour_position);
        setNumberOnClock(minute_position);
        setNumberOnClock(second_position);
        HAL_Delay(1000);

        if (++second >= 60) {
            second = 0;
            if (++minute >= 60) {
                minute = 0;
                hour = (hour + 1) % 12;
            }
        }
    }
}
