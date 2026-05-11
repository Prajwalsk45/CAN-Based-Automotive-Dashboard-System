#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
//#include "uart.h"
#include "digital_keypad.h"

//extern signed char gear;
uint16_t get_speed()
{
    // Implement the speed function
    unsigned short speed=read_adc(CHANNEL4);
    
    return speed/10.23;
}

unsigned char get_gear_pos()
{
    // Implement the gear function
    static signed char gear;
    
    char key=read_digital_keypad(STATE_CHANGE);
    
    if(key == SWITCH1)
    {
        if(gear<6)
        gear++;
    }
    else if(key == SWITCH2)
    {
        if(gear>0)
        gear--;
    }
    else if(key==SWITCH3)
    {
        gear=-1;
        
    }
    
    
    if(gear==0) return 'N';
    else if(gear == -1) return 'R';
    else return gear+'0';
    
    
    
}