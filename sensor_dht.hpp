
#ifndef SENSOR_DHT_HPP
#define SENSOR_DHT_HPP

#define DATA_LENGTH         5


class sensor_dht11_class
{
private:
    unsigned char sensor_gpio_num;

    unsigned char p_data [DATA_LENGTH];

public:
    sensor_dht11_class (
            unsigned char gpio_num);

    int get_temperature (
            void);

    unsigned int get_humidity (
            void);

private:
    void do_read (
            void);

    void sensor_setup (
            void);

    void read_data (
            void);

    bool is_data_crc_valid (
            void);
};

#endif // SENSOR_DHT_HPP
