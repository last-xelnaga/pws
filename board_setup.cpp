
#include <pcf8591.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include "board_setup.hpp"

#define PCF         120


// private methods
int board_setup::init_board (
        void)
{
    int result = 0;

    if (result == 0)
    {
        if (geteuid () != 0)
        {
            printf ("need to be root to run");
            result = -1;
        }
    }

    if (result == 0)
    {
        if (wiringPiSetup () == -1)
        {
            printf ("wiringPiSetup has failed");
            result = -1;
        }
    }

    // Setup pcf8591 on base pin 120, and address 0x48
    if (result == 0)
    {
        pcf8591Setup (PCF, 0x48);
    }

    return result;
}


// public methods
board_setup::board_setup (
        unsigned char pump_gpio_num_,
        unsigned char pcf_gpio_num_)
{
    pump_gpio_num = pump_gpio_num_;
    pcf_gpio_num = pcf_gpio_num_;

    if (init_board () != 0)
    {
        printf ("board setup has failed. quit");
        exit (EXIT_FAILURE);
    }

    pinMode (pump_gpio_num, OUTPUT);
    digitalWrite (pump_gpio_num, 0);

    pinMode (pcf_gpio_num, OUTPUT);
    digitalWrite (pcf_gpio_num, 0);
}

bool board_setup::is_soil_dry (
        unsigned int threshold)
{
    bool result = false;

    digitalWrite (pcf_gpio_num, 1);
    sleep (1);

    unsigned int soil_level = analogRead (PCF + 0);
    if (soil_level > threshold)
        result = true;

    printf("soil_level %d\n", soil_level);

    digitalWrite (pcf_gpio_num, 0);

    return result;
}

void board_setup::switch_the_pump_on (
        unsigned int seconds)
{
    unsigned int water_level = analogRead (PCF + 1);
    if (water_level < 30)
    {
        printf ("there is no water in the tank\n");
        return;
    }

    digitalWrite (pump_gpio_num, 1);

    sleep (seconds);

    digitalWrite (pump_gpio_num, 0);
}

board_setup::~board_setup (
        void)
{
    digitalWrite (pump_gpio_num, 0);
    digitalWrite (pcf_gpio_num, 0);
}
