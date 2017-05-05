#ifndef BOARD_SETUP_HPP
#define BOARD_SETUP_HPP

#include <string>

class board_setup
{
private:
    unsigned char pump_gpio_num;
    unsigned char pcf_gpio_num;

    int init_board (
            void);

public:
    board_setup (
            unsigned char pump_gpio_num_,
            unsigned char pcf_gpio_num_);

    bool is_soil_dry (
            unsigned int threshold);

    void switch_the_pump_on (
            unsigned int seconds);

    ~board_setup (
            void);
};

#endif // BOARD_SETUP_HPP
