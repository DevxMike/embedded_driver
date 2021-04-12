#include "tests.h"
#include <iostream>

void print_init_status(uint8_t code){
    if(code){ std::cout << "init done\n"; }
    else { std::cout << "init in progress\n"; }
}

void print_rom_cmd_status(uint8_t code){
    if(code) { std::cout << "rom cmd successfully sent\n"; }
    else { std::cout << "rom cmd in progress\n"; }
}

void print_volatile_cmd_status(uint8_t code){
    if(code) { std::cout << "temperature acquired\n"; }
    else { std::cout << "in progress\n"; }
}

void print_conversion_status(uint8_t code){
    if(code) { std::cout << "convertion done\n"; }
    else { std::cout << "convertion in progress\n"; }
}