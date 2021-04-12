#include "timers.h"
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "spi.h"

volatile uint8_t cycle = 0; 
volatile uint8_t dig = 0;

const uint8_t EEMEM LED_DISP_VALS[10] = {
    0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6
};

volatile uint8_t values[4] = { 1, 2, 3, 4 };

int main(void){

    DDRD = 0x0F;
    PORTD = 0x0F;
    
    init_16bit_timer(0x01, 0x3E7F, CTC);
    init_8bit_timer(0x03, 0x4E, CTC);
    init_spi();
    sei();

    while(1){
        cycle = 0;
        while(!cycle);
    }
}
ISR(TIMER1_COMPA_vect){
    cycle = 1;
}
ISR(TIMER2_COMP_vect){
    PORTD &= ~(1 << dig);
    if(++dig > 3) {
        dig = 0;
    }
    set_register_outputs(
        eeprom_read_byte(&LED_DISP_VALS[values[dig]]) | (dig == 0? 0x01 : 0x00)
    );
    PORTD |= (1 << dig);
}