#ifndef temperature_h_
#define temperature_h_

#include <avr/io.h>

uint8_t init_temperature_sensor_communication(void);
void write_one_bit_to_temp_sensor(uint8_t bit);
void write_one_byte_to_temp_sensor(uint8_t byte);
uint8_t read_one_bit_from_temp_sensor(void);
uint8_t read_one_byte_from_temp_sensor(void);

#endif