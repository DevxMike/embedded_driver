#include "temperature_api.h"



uint8_t convert_temperature(void){
    if(!init_temperature_sensor_communication()){
        write_one_byte_to_temp_sensor(SKIP_ROM);
        write_one_byte_to_temp_sensor(INIT_CONVERSION);
    }
    else{
        return 0x01;
    }
    return 0;
}
uint8_t read_temperature(void){
    if(!init_temperature_sensor_communication()){
        write_one_byte_to_temp_sensor(SKIP_ROM);
        for(uint8_t i = 0; i < 2; ++i){
            read_one_byte_from_temp_sensor();
        }
    }
    else{
        return 0x01;
    }
    return 0x00;
}
void prepare_values_to_be_displayed(void){
    
}