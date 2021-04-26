#ifndef h_
#define h_
#include <avr/io.h>

typedef struct{
    uint8_t pc;
    uint8_t conversion_flag;
    uint16_t timer;
    uint8_t output;
    uint8_t statement;
    uint8_t command_code;
}temperature_vars_t;

void init_temperature_sensor(temperature_vars_t* temperature_graph){
    temperature_graph->command_code = temperature_graph->conversion_flag
        = temperature_graph->output = temperature_graph->pc 
        = temperature_graph->statement = temperature_graph->timer = 0;
}

#endif