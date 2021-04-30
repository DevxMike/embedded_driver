#ifndef temperature_h_
#define temperature_h_
#include <avr/io.h>
extern const uint8_t SKIP_ROM;
extern const uint8_t INIT_CONVERSION;
extern const uint8_t READ_SCRATCH_PAD;
extern const uint8_t TEMPERATURE_MASK;
#define SKIP_ROM  0xCC
#define INIT_CONVERSION 0x44
#define READ_SCRATCH_PAD  0xBE

uint8_t init_temperature_sensor_communication(void);
void write_one_bit_to_temp_sensor(uint8_t bit);
void write_one_byte_to_temp_sensor(uint8_t byte);
uint8_t read_one_bit_from_temp_sensor(void);
uint8_t read_one_byte_from_temp_sensor(void);

#endif