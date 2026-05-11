#define _XTAL_FREQ 20000000
#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include <xc.h>

void rpm_convert_ascii(uint16_t rpm, uint8_t *arr)
{
    arr[0] = (rpm / 1000) % 10 + '0';
    arr[1] = (rpm / 100) % 10 + '0';
    arr[2] = (rpm / 10) % 10 + '0';
    arr[3] = (rpm % 10) + '0';
}

int main()
{
//    init_uart();
    init_adc();
    
    init_digital_keypad();

    TRISB = 0x00; // Set RB2 as output, RB3 as input, remaining as output
    PORTB = 0x00;
    init_can();
    

    uint16_t msg_id;
    uint8_t data[9];
    uint8_t len;

    while(1)
    {
        uint16_t rpm = get_rpm();

        IndicatorStatus indicator = process_indicator();
//        indicator=indicator+'0';
        uint8_t rpm_data[5];
        rpm_data[4]='\0';
        rpm_convert_ascii(rpm, rpm_data);


        can_transmit(RPM_MSG_ID, rpm_data, 4);

        __delay_ms(50);
        
        can_transmit(INDICATOR_MSG_ID, &indicator, 1);

        __delay_ms(50);

      
    }
}