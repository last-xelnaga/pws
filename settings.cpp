
#include <fstream>
#include <sstream>
#include "settings.hpp"

// gpio for the relays and sensors
#define PUMP_RELAY_PIN          2
#define CHECKER_RELAY_PIN       5
#define TERMO_DHT_PIN           4
#define STATUS_LED_PIN          3

// dry soil threshold
#define DRY_THRESHOLD           500

// how many seconds pump has to work
#define PUMP_ACTIVE_TIME        90

// sleeping time betwean checks, 1 day by deafault
#define WAIT_FOR_NEXT_CHECK     (60 * 60 * 24)

// name of the file with settings (optional)
#define SETTINGS_FILE_NAME      "settings.cfg"


// private methods
settings_class::settings_class (
        void)
{
    relay_pump_gpio_num = PUMP_RELAY_PIN;
    relay_checker_gpio_num = CHECKER_RELAY_PIN;
    dht_termo_gpio_num = TERMO_DHT_PIN;
    status_led_gpio_num = STATUS_LED_PIN;

    soil_dry_threshold = DRY_THRESHOLD;

    pump_active_time = PUMP_ACTIVE_TIME;

    wait_for_next_check = WAIT_FOR_NEXT_CHECK;

    is_file_processed = 0;
}

void settings_class::read_config_file (
        void)
{
    if (is_file_processed)
        return;

    std::ifstream file (SETTINGS_FILE_NAME);
    if (!file)
        return;

    std::stringstream buffer;
    buffer << file.rdbuf ();
    file.close ();

    std::string line;
    while (std::getline (buffer, line))
    {
        std::istringstream is_line (line);

        std::string key, value;
        if (std::getline (is_line, key, '='))
        {
            if (std::getline (is_line, value))
                init_key (key, value);
        }
    }

    is_file_processed = 1;
}

void settings_class::init_key (
        std::string key,
        std::string value)
{
    unsigned int number = std::stoi (value);

    if (key == "relay_pump_gpio_num")
    {
        relay_pump_gpio_num = number;
    }
    else if (key == "relay_checker_gpio_num")
    {
        relay_checker_gpio_num = number;
    }
    else if (key == "dht_termo_gpio_num")
    {
        dht_termo_gpio_num = number;
    }
    else if (key == "status_led_gpio_num")
    {
        status_led_gpio_num = number;
    }
    else if (key == "soil_dry_threshold")
    {
        soil_dry_threshold = number;
    }
    else if (key == "pump_active_time")
    {
        pump_active_time = number;
    }
    else if (key == "wait_for_next_check")
    {
        wait_for_next_check = number;
    }
    else
    {
        printf ("unknown key\n");
    }

    printf ("%s = %d\n", key.c_str (), number);
}

// public methods
unsigned char settings_class::relay_pump_gpio (
        void)
{
    read_config_file ();
    return 2;//relay_pump_gpio_num;
}

unsigned char settings_class::relay_checker_gpio (
        void)
{
    read_config_file ();
    return 5;//relay_checker_gpio_num;
}

unsigned char settings_class::dht_termo_gpio (
        void)
{
    read_config_file ();
    return 7;//dht_termo_gpio_num;
}

unsigned char settings_class::status_led_gpio (
        void)
{
    read_config_file ();
    return 3;//status_led_gpio_num;
}

unsigned int settings_class::get_soil_dry_threshold (
        void)
{
    read_config_file ();
    return soil_dry_threshold;
}

unsigned int settings_class::get_pump_active_time (
        void)
{
    read_config_file ();
    return pump_active_time;
}

unsigned int settings_class::get_wait_for_next_check (
        void)
{
    read_config_file ();
    return wait_for_next_check;
}
