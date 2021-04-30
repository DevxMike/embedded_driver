#include "temperature.h"
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t TEMPERATURE_MASK = 0x01;

volatile uint8_t* port = &PORTC;
volatile uint8_t* direction = &DDRC;
volatile uint8_t* pin = &PINC;

uint8_t init_temperature_sensor_communication(void){
    uint8_t response = 0x00;
    uint8_t sreg = SREG;
    
    cli();

    if(!(*port & TEMPERATURE_MASK)) {* port |= TEMPERATURE_MASK; }
    *direction |= TEMPERATURE_MASK;
    *port &= ~TEMPERATURE_MASK;

    _delay_us(600);

    *direction &= ~TEMPERATURE_MASK;

    _delay_us(70);

    response = *pin & TEMPERATURE_MASK;

    _delay_us(200);

    if(!(*port & TEMPERATURE_MASK)) {* port |= TEMPERATURE_MASK; }
    *direction |= TEMPERATURE_MASK;

    _delay_us(600);

    SREG = sreg;
    return response == 0x00;
}
void write_one_bit_to_temp_sensor(uint8_t bit){
    uint8_t sreg = SREG;

    cli();
    if(!(*port & TEMPERATURE_MASK)) {* port |= TEMPERATURE_MASK; }
    *direction |= TEMPERATURE_MASK;
    *port &= ~TEMPERATURE_MASK;

    _delay_us(bit? 10 : 80);

    *port |= TEMPERATURE_MASK;

    _delay_us(bit? 80 : 2);

    SREG = sreg;
}
void write_one_byte_to_temp_sensor(uint8_t byte){
    uint8_t sreg = SREG;

    cli();

    for(uint8_t i = 1; i; i <<= 1){
        write_one_bit_to_temp_sensor(byte & i);
    }
    
    SREG = sreg;
}
uint8_t read_one_bit_from_temp_sensor(void){
    uint8_t sreg = SREG;
    uint8_t bit = 0;

    cli();

    if(!(*port & TEMPERATURE_MASK)) { *port |= TEMPERATURE_MASK; }
    *direction |= TEMPERATURE_MASK;
    *port &= ~TEMPERATURE_MASK;

    _delay_us(2);

    *direction &= ~TEMPERATURE_MASK;

    _delay_us(5);

    bit = *pin & TEMPERATURE_MASK;

    _delay_us(60);
    
    SREG = sreg;

    return bit;
}
uint8_t read_one_byte_from_temp_sensor(void){
    uint8_t sreg = SREG;
    uint8_t byte = 0x00;

    cli();

    for(int i = 1; i; i <<= 1){
        byte |= read_one_bit_from_temp_sensor() << i;
    }

    SREG = sreg;
    return byte;
}