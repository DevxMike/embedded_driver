#include "timers.h"

void write_to_16bit_timer_OCR(uint16_t OCR){
    OCR1AH = (uint8_t)(((OCR & 0xFF00) >> 8));
    OCR1AL = (uint8_t)((OCR & 0x00FF));
}
void set_16bit_timer_prescaler(uint16_t prescaler){
    switch(prescaler){
        case 1: TCCR1B |= 0x01; break;
    }
}
void set_16bit_timer_mode(uint8_t mode){
    switch(mode){
        case CTC: TCCR1B |= (1 << WGM12); TIMSK |= 0x10; break;
    }
}

void init_16bit_timer(uint16_t prescaler, uint16_t OCR, uint8_t mode){
    write_to_16bit_timer_OCR(OCR);
    set_16bit_timer_mode(mode);
    set_16bit_timer_prescaler(prescaler);
}

void write_to_8bit_timer_OCR(uint8_t OCR){
    OCR2 = OCR;
}
void set_8bit_timer_prescaler(uint8_t prescaler){
    TCCR2 |= prescaler;
}
void set_8bit_timer_mode(uint8_t mode){
    switch(mode){
        case CTC: TCCR2 |= (1 << WGM21); TIMSK |= 0x80; break;
    }
}

void init_8bit_timer(uint8_t prescaler, uint8_t OCR, uint8_t mode){
    write_to_8bit_timer_OCR(OCR);
    set_8bit_timer_mode(mode);
    set_8bit_timer_prescaler(prescaler);
}