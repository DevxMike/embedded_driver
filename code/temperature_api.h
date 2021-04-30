#ifndef temperature_api_h
#define temperature_api_h

#include "temperature.h"
extern int8_t decimal;
extern uint8_t floating;

uint8_t convert_temperature(void);
uint8_t read_temperature(void);
void prepare_values_to_be_displayed(void);

#endif