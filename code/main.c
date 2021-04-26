#include "timers.h"
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "spi.h"
#include "main.h"

volatile uint8_t cycle = 0; 
volatile uint8_t dig = 0;

const uint8_t EEMEM LED_DISP_VALS[11] = {
    0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6, 0x00
}; //last value is simply a null sign (nothing to display)

const uint8_t EEMEM temperature_output[] = { 0x00, 0x01, 0x02, 0x00, 0x04, 0x30, 0x08, 0x20 };
const uint8_t EEMEM temperature_statement[] = { 1, 2, 3, 5, 4, 0, 6, 0 };
const uint8_t EEMEM temperature_address[] = { 0, 1, 2, 6, 4, 0, 6, 1 };

volatile uint8_t values[4] = { 10, 2, 3, 5 };

int main(void){
    temperature_vars_t temperature_sensor;
    
    DDRD = 0x0F;
    PORTD = 0x0F;
    
    init_temperature_sensor(&temperature_sensor);
    init_16bit_timer(0x01, 0x3E7F, CTC);
    init_8bit_timer(0x03, 0x4E, CTC);
    init_spi();
    sei();
    
    while(1){
        temperature_sensor.output = eeprom_read_byte(&temperature_output[temperature_sensor.pc]);

        if(temperature_sensor.output & 0x01) { /*init, state machine 1*/ }
        if(temperature_sensor.output & 0x02) { temperature_sensor.command_code = 0xCC; }
        if(temperature_sensor.output & 0x04) { temperature_sensor.command_code = 0xBE; }
        if(temperature_sensor.output & 0x08) { temperature_sensor.command_code = 0x44; }
        if(temperature_sensor.output & 0x10) { temperature_sensor.timer = 1000; }
        if(temperature_sensor.output & 0x20) { temperature_sensor.conversion_flag ^= 0xFF; }

        switch(eeprom_read_byte(&temperature_statement[temperature_sensor.pc])){
            case 0: temperature_sensor.statement = 0; break;
            case 1: temperature_sensor.statement = !temperature_sensor.timer; break;
            case 2: /*init communication*/ break;
            case 3: /*send rom cmd*/ break;
            case 4: /*volatile rom cmd*/ break;
            case 5: temperature_sensor.statement = temperature_sensor.conversion_flag; break;
            case 6: /*volatile rom cmd*/  break;
        }
        
        if(temperature_sensor.statement){ 
            ++temperature_sensor.pc; 
        }
        else { 
            temperature_sensor.pc = eeprom_read_byte(&temperature_address[temperature_sensor.pc]); 
        }

        if(temperature_sensor.timer) { --temperature_sensor.timer; }
    
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
        eeprom_read_byte(&LED_DISP_VALS[values[dig]]) | (dig == 2? 0x01 : 0x00)
    );
    PORTD |= (1 << dig);
}