#ifndef timers_hpp
#define timers_hpp
#include <avr/io.h>

enum Modes{
    CTC = 0
};

void init_16bit_timer(uint16_t prescaler, uint16_t OCR, uint8_t mode);
void init_8bit_timer(uint8_t prescaler, uint8_t OCR, uint8_t mode);
#endif