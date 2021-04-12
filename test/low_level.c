#include "low_level.h"

uint8_t init_temp_sensor_communication(void){
    static uint8_t state = 0, timer = 2;
    switch(state){
        case 0: if(timer) { 
            --timer; 
        } 
        else { 
            state = 1; 
        } 
        return 0;
        break;

        case 1:
            state = 0;
            timer = 2;
            return 1;
        break;
    }
}

uint8_t send_rom_cmd_to_temp_sensor(uint8_t cmd){
    static uint8_t state = 0, timer = 1;
    switch(state){
        case 0: if(timer) { 
            --timer; 
        } 
        else { 
            state = 1; 
        } 
        return 0;
        break;

        case 1:
            state = 0;
            timer = 2;
            return 1;
        break;
    }
}

uint8_t send_volatile_memory_cmd(uint8_t cmd){
    static uint8_t state = 0, timer = 1;
    switch(state){
        case 0: if(timer) { 
            --timer; 
        } 
        else { 
            state = 1; 
        } 
        return 0;
        break;

        case 1:
            state = 0;
            timer = 2;
            return 1;
        break;
    }
}