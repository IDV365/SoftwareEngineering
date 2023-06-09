#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "temp.c"
#include "logfile.c"
#include "leds.c"

void loop(void);
void check_time(int);

const int LIGHT = 150;

int main()
{
    setup_pins();
    check_time(1);
    while (1)
    {
        loop();
        check_time(0);
    }
}

void loop()
{
    led_indicator(map_to_8(get_temp()));
    return;
}

void check_time(int setup)
{
    static time_t start_time;
    if (setup)
        start_time = time(NULL);

    static time_t current_time;

    current_time = time(NULL); // Get the current time

    if (current_time - start_time >= 10)
    {
        printf("Temp: %.6f\n", get_temp());
        write_log(get_temp(), LIGHT); // Call the task function
        start_time = current_time;    // Update the starting time
    }

    return;
}
