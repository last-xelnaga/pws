#include <stdio.h>
#include <unistd.h>
#include "board_setup.hpp"

// gpio for the relays
#define PUMP_RELAY_PIN          4
#define PCF_RELAY_PIN           5

// dry soil threshold
#define DRY_THRESHOLD           500

// how many seconds pump has to work
#define PUMP_ACTIVE_TIME        45

// sleeping time betwean checks, 1 hour by deafault
#define WAIT_FOR_NEXT_CHECK     (60 * 60)


int main (
        void)
{

    board_setup board (PUMP_RELAY_PIN, PCF_RELAY_PIN);

    while (1)
    {
        if (board.is_soil_dry (DRY_THRESHOLD))
            board.switch_the_pump_on (PUMP_ACTIVE_TIME);

        sleep (WAIT_FOR_NEXT_CHECK);
    }

    return 0;
}
