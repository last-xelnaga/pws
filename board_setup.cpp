
#include <mcp3004.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include "board_setup.hpp"
#include "settings.hpp"

// pin base for the chip. channels will be addressed from base to base + 7
#define MCP_BASE        100
// spi channel that the peripheral is connected to
#define SPI_CHAN        0
// analog channel for the dry soil mesurment
#define SENSOR_CHAN     0


#define HIGH            1
#define LOW             0

// private methods
int board_setup_class::init_board (
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

    // Setup mcp3008
    if (result == 0)
    {
        mcp3004Setup (MCP_BASE, SPI_CHAN);
    }

    return result;
}


// public methods
board_setup_class::board_setup_class (
        void)
{
    if (init_board () != 0)
    {
        printf ("board setup has failed. quit");
        exit (EXIT_FAILURE);
    }

    pinMode (settings_class::get_instance ().relay_pump_gpio (), OUTPUT);
    digitalWrite (settings_class::get_instance ().relay_pump_gpio (), LOW);

    pinMode (settings_class::get_instance ().relay_checker_gpio (), OUTPUT);
    digitalWrite (settings_class::get_instance ().relay_checker_gpio (), LOW);

    pinMode (settings_class::get_instance ().status_led_gpio (), OUTPUT);
    digitalWrite (settings_class::get_instance ().status_led_gpio (), LOW);
}

bool board_setup_class::is_time_for_watering (
        void)
{
    bool result = false;

    digitalWrite (settings_class::get_instance ().relay_checker_gpio (), HIGH);
    sleep (1);

    unsigned int soil_level = analogRead (MCP_BASE + SENSOR_CHAN);
    printf ("soil_level %d\n", soil_level);
    if (soil_level >= settings_class::get_instance ().get_soil_dry_threshold ())
        result = true;

    digitalWrite (settings_class::get_instance ().relay_checker_gpio (), LOW);

    return result;
}

void board_setup_class::activate_pump (
        void)
{
    /*unsigned int water_level = analogRead (PCF + 1);
    if (water_level < 30)
    {
        printf ("there is no water in the tank\n");
        return;
    }*/

    digitalWrite (settings_class::get_instance ().relay_pump_gpio (), HIGH);

    sleep (settings_class::get_instance ().get_pump_active_time ());

    digitalWrite (settings_class::get_instance ().relay_pump_gpio (), LOW);
}

void board_setup_class::status_led_signal (
        bool signal)
{
    int data = HIGH;

    if (signal == false)
        data = LOW;

    digitalWrite (settings_class::get_instance ().status_led_gpio (), data);
}

board_setup_class::~board_setup_class (
        void)
{
    digitalWrite (settings_class::get_instance ().relay_pump_gpio (), LOW);
    digitalWrite (settings_class::get_instance ().relay_checker_gpio (), LOW);
    digitalWrite (settings_class::get_instance ().status_led_gpio (), LOW);
}
