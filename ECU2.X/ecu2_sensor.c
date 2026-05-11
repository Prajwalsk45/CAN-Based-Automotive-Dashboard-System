#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

uint16_t get_rpm()
{
    unsigned short adc_val = read_adc(CHANNEL4);
    adc_val=adc_val * 6.85;
    
    if(adc_val>7000) adc_val=7000;
    return (adc_val );
}

IndicatorStatus process_indicator()
{
    static IndicatorStatus flag = e_ind_off;
    static int toggle = 0;

    toggle = !toggle;

    char key = read_digital_keypad(STATE_CHANGE);

    if(key == SWITCH1)
        flag = e_ind_left;
    else if(key == SWITCH2)
        flag = e_ind_right;
    else if(key == SWITCH3)
        flag = e_ind_off;

    if(flag == e_ind_left)
    {
        if(toggle)
            LEFT_IND_ON();
        else
            LEFT_IND_OFF();

        RIGHT_IND_OFF();
    }
    else if(flag == e_ind_right)
    {
        if(toggle)
            RIGHT_IND_ON();
        else
            RIGHT_IND_OFF();

        LEFT_IND_OFF();
    }
    else
    {
        LEFT_IND_OFF();
        RIGHT_IND_OFF();
    }

    return flag;
}