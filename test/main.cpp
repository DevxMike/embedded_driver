#include <iostream>
#include <unistd.h> //delay
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
    /*-----------------------------------------*/

    while(true){
        main_output = main_temp_output[main_pc];
        
        if(main_output & 0x01) { /*init, state machine 1*/ }
        if(main_output & 0x02) { /*ROM command*/ }
        if(main_output & 0x04) { /*read volatile memory*/ }
        if(main_output & 0x08) { /*init temp conversion*/ }
        if(main_output & 0x10) { main_timer = 10; }
        if(main_output & 0x20) { conversion_flag = conversion_flag ^ 0xFF; }

        switch(main_temp_statement[main_pc]){
            case 0: main_statement = 0; break;
            case 1: main_statement = !main_timer; break;
            case 2: /*presence*/ break;
            case 3: /*CMD END*/ break;
            case 4: /*READ SUCCESS*/ break;
            case 5: main_statement = conversion_flag; break;
            case 6: /*conversion done*/ break;
        }

        if(main_statement){ ++main_pc; }
        else { main_pc = main_temp_address[main_pc]; }

        if(main_timer) { --main_timer; }
        
        usleep(1000000);
    }
    return 0;
}