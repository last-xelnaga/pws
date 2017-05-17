#ifndef BOARD_SETUP_HPP
#define BOARD_SETUP_HPP

class board_setup_class
{
private:
    int init_board (
            void);

public:
    board_setup_class (
            void);

    bool is_time_for_watering (
            void);

    void activate_pump (
            void);

    void status_led_signal (
            bool signal = true);

    ~board_setup_class (
            void);
};

#endif // BOARD_SETUP_HPP
