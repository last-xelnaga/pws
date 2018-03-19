
#include "sensor_dht.hpp"
#include "wiringPi.h"

#include <stdio.h>
#include <unistd.h>

#define RETRY_COUNT             3


void sensor_dht11_class::do_read (
        void)
{
    int retry_count = RETRY_COUNT;

    //while (true)
    //{
        read_data ();

        //if (is_data_crc_valid ())
        //    break;

        //if (-- retry_count < 0)
        //{
        //    for (int i = 0; i < DATA_LENGTH; i ++)
        //        p_data[i] = 0;
        //    break;
        //}

        //sleep (1);
    //}
}

void sensor_dht11_class::sensor_setup (
        void)
{
    pinMode (sensor_gpio_num, OUTPUT);

    // pull the bus high. this one will show to sensor
    // that it could stay in low-power-consumption mode
    digitalWrite (sensor_gpio_num, HIGH);
}

void sensor_dht11_class::read_data (
        void)
{
    // send 'start' command
    // pull the bus down
    digitalWrite (sensor_gpio_num, LOW);
    // and wait at least 18ms
    delay (30);

    // now pull the bus up
    digitalWrite (sensor_gpio_num, HIGH);
    // and wait for response (20 - 40 ms)
    delayMicroseconds (30);

    // at this point the sensor should start to react
    // on our 'start' command
    pinMode (sensor_gpio_num, INPUT);
    // sensor has to lower the bus, so wait for it
    while (digitalRead (sensor_gpio_num) == HIGH);
    // he has to keep low level for 80 ms
    delayMicroseconds (80);
    // and than put it high again. wait for it as well
    while (digitalRead (sensor_gpio_num) == LOW);
    // it will keep hight level for 80 ms, so skip them
    delayMicroseconds (80);

    // and it's ready to send 40 bits of data
    for (unsigned int i = 0; i < DATA_LENGTH; i ++)
    {
        // receive temperature and humidity data, the parity bit is not considered
        unsigned char byte = 0;
        for (int bit = 0; bit < 8; bit ++)
        {
            // wait for low bus. indicates that the transmission has started
            while (digitalRead (sensor_gpio_num) == HIGH);
            // wait for 50 ms of the low level. skip it
            while (digitalRead (sensor_gpio_num) == LOW);

            // now the sensor has switched the bus to high level
            // wait for 30 ms to check the bus level again
            delayMicroseconds (30);

            // check the bus again
            if (digitalRead (sensor_gpio_num) == HIGH)
            {
                // high bus after 30 ms means that we got '1',
                // since '1' requires 70 ms of high bus.
                // '0' should be finished within 26-28 ms.
                byte |= (1 << (7 - bit));
            }
        }
        p_data [i] = byte;
    }

    pinMode (sensor_gpio_num, OUTPUT);

    // pull the bus high. this one will show to sensor
    // that it could stay in low-power-consumption mode
    digitalWrite (sensor_gpio_num, HIGH);
}

bool sensor_dht11_class::is_data_crc_valid (
        void)
{
    bool result = true;

    // check the crc of the data buffer
    if ((p_data[0] + p_data[2]) - p_data[4] != 0)
    {
        result = false;
        printf("%s temp %i.%i, hum %i.%i, crc %i\n", "dht11", p_data[0], p_data[1], p_data[2], p_data[3], p_data[4]);
    }

    return result;
}

sensor_dht11_class::sensor_dht11_class (
        unsigned char gpio_num)
{
    sensor_gpio_num = gpio_num;

    sensor_setup ();
}

int sensor_dht11_class::get_temperature (
        void)
{
    do_read ();

    int temperature = p_data[2];
    temperature *= 10;
    temperature += p_data[3];

    return temperature;
}

unsigned int sensor_dht11_class::get_humidity (
        void)
{
    do_read ();

    unsigned int humidity = p_data[0];
    humidity *= 10;
    humidity += p_data[1];

    return humidity;
}
