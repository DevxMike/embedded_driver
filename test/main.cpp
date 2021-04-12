#include <iostream>
#include <unistd.h> //delay

#include "low_level.h"
#include "tests.h"
/*-------------------------var_arr--------------------------*/

const int main_temp_output[]{ 0x00, 0x01, 0x02, 0x00, 0x04, 0x30, 0x08, 0x20 };
const int main_temp_statement[]{ 1, 2, 3, 5, 4, 0, 6, 0 };
const int main_temp_address[]{ 0, 1, 2, 6, 4, 0, 6, 1 };

/*----------------------------------------------------------*/


int main(void){
    /*-------------main graph vars-------------*/
    uint8_t main_pc = 0;
    uint8_t conversion_flag = 0;
    uint8_t main_timer = 0;
    uint8_t main_output = 0;
    uint8_t main_statement = 0;
    uint8_t command_code = 0;
    /*-----------------------------------------*/

    while(true){
        main_output = main_temp_output[main_pc];
        
        if(main_output & 0x01) { /*init, state machine 1*/ }
        if(main_output & 0x02) { command_code = 0xCC; }
        if(main_output & 0x04) { command_code = 0xBE; }
        if(main_output & 0x08) { command_code = 0x44; }
        if(main_output & 0x10) { main_timer = 10; }
        if(main_output & 0x20) { conversion_flag ^= 0xFF; }

        switch(main_temp_statement[main_pc]){
            case 0: main_statement = 0; break;
            case 1: main_statement = !main_timer; break;
            case 2: print_init_status(main_statement = init_temp_sensor_communication()); break;
            case 3: print_rom_cmd_status(main_statement = send_rom_cmd_to_temp_sensor(command_code)); break;
            case 4: print_volatile_cmd_status(main_statement = send_volatile_memory_cmd(command_code)); break;
            case 5: main_statement = conversion_flag; break;
            case 6: print_conversion_status(main_statement = send_volatile_memory_cmd(command_code)); break;
        }

        std::cout << (main_pc + '0') - 48 << std::endl;
        
        if(main_statement){ ++main_pc; }
        else { main_pc = main_temp_address[main_pc]; }

        if(main_timer) { --main_timer; }
        
        usleep(1000000);
    }
    return 0;
}