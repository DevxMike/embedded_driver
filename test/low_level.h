#ifndef low_level
#define low_level

#include <stdint.h>

uint8_t init_temp_sensor_communication(void);
uint8_t send_rom_cmd_to_temp_sensor(uint8_t cmd);
uint8_t send_volatile_memory_cmd(uint8_t cmd);

#endif