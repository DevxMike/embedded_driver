#include "spi.h"
#include <util/delay.h>

#define MOSI 3
#define OUTPUT_ENABLE 2
#define CLOCK 5
#define LATCH 1


void init_spi(void){
    DDRB |= (1 << MOSI) | (1 << OUTPUT_ENABLE) | (1 << LATCH) | (1 << CLOCK);
    SPCR |= (1 << MSTR) | (1 << SPE) | (1 << DORD) | (1 << SPR1);
}
void transfer_byte_to_register(uint8_t data){
    SPDR = data;
    while(!(SPSR & (1 << SPIF)));
}
void set_register_outputs(uint8_t data){
    PORTB &= ~(1 << LATCH);
    PORTB |= (1 << OUTPUT_ENABLE);
    transfer_byte_to_register(data);
    PORTB &= ~(1 << OUTPUT_ENABLE);
    PORTB |= (1 << LATCH);
}