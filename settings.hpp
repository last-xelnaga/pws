#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>


class settings_class
{
    private:
        unsigned char relay_pump_gpio_num;
        unsigned char relay_checker_gpio_num;
        unsigned char dht_termo_gpio_num;
        unsigned char status_led_gpio_num;

        unsigned int soil_dry_threshold;

        unsigned int pump_active_time;

        unsigned int wait_for_next_check;

        char is_file_processed;

    private:
        settings_class (
                void);

        void read_config_file (
                void);

        void init_key (
                std::string key,
                std::string value);
    public:
        static settings_class& get_instance (void)
        {
            static settings_class instance;
            return instance;
        }

        unsigned char relay_pump_gpio (
                void);

        unsigned char relay_checker_gpio (
                void);

        unsigned char dht_termo_gpio (
                void);

        unsigned char status_led_gpio (
                void);

        unsigned int get_soil_dry_threshold (
                void);

        unsigned int get_pump_active_time (
                void);

        unsigned int get_wait_for_next_check (
                void);

    public:
        settings_class (settings_class const&) = delete;
        void operator= (settings_class const&) = delete;

};

#endif // SETTINGS_HPP
