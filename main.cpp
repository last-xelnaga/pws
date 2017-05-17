#include <stdio.h>
#include <unistd.h>
#include "settings.hpp"
#include "board_setup.hpp"


int main (
        void)
{
    board_setup_class board;

    while (1)
    {
        if (board.is_time_for_watering ())
            board.activate_pump ();

        sleep (settings_class::get_instance ().get_wait_for_next_check ());
    }

    return 0;
}
