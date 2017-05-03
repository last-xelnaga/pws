#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

#define RELAY_PIN     1


void relay_switch_on (
        void)
{
    digitalWrite (RELAY_PIN, 1);
}

void relay_switch_off (
        void)
{
    digitalWrite (RELAY_PIN, 0);
}

int main (
        void)
{
    if (geteuid () != 0)
    {
        printf ("need to be root to run. exit");
        return -1;
    }

    if (wiringPiSetup () == -1)
    {
        printf ("board setup has failed. exit");
        return -1;
    }

    // setup relay
    pinMode (RELAY_PIN, OUTPUT);
    relay_switch_off ();

    // setup soil sensor
    


    return 0;
}
