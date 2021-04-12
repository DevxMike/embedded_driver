#ifndef spi_h
#define spi_h
#include <avr/io.h>

void init_spi(void);
void set_register_outputs(uint8_t data);
#endif