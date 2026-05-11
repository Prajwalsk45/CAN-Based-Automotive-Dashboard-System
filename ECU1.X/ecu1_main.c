#define _XTAL_FREQ 20000000
#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"
//#include "digital_keypad.h"
//#include "clcd.h"

signed char gear = 0;

void speed_convert_ascii(uint16_t speed, unsigned char *arr)
{
    arr[0] = (speed / 100) % 10 + '0';
    arr[1] = (speed / 10) % 10 + '0';
    arr[2] = (speed % 10) + '0';
}

int main()
{
    
    init_adc();
    init_can();
    init_digital_keypad();

    int msg_id;
    char arr[5] = {0};
    int len = 0;

    while(1)
    {
        uint16_t speed = get_speed();
        unsigned char gear_pos = get_gear_pos();

        unsigned char data[4];

        speed_convert_ascii(speed, data);
        data[3]='\0';
        can_transmit(SPEED_MSG_ID, data, 3);
        __delay_ms(50);

        can_transmit(GEAR_MSG_ID, &gear_pos, 1);
        __delay_ms(50);

//        can_receive(&msg_id, arr, &len);
//        
//        arr[len]='\0';
//
//            if(msg_id == GEAR_MSG_ID)
//            {
//                putch(arr[0]);
//            }
//
//            if(msg_id == SPEED_MSG_ID)
//            {
//                puts(arr);
//            }
        
    }
}