#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"


volatile unsigned char led_state = LED_OFF, status = e_ind_off;


void handle_speed_data(uint8_t *data, uint8_t len)
{
    //Implement the speed function
    clcd_print(data,LINE2(0));
    
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    //Implement the gear function
    clcd_print(data,LINE2(4));
    clcd_print("  ",LINE2(5));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
    clcd_print(data,LINE2(7));
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    //Implement the temperature function
    
}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    
    //Implement the indicator function
    static unsigned char toggle = 0;
        toggle = !toggle;     // change state every loop
    if (*data == 1) {
       if (toggle)
          LEFT_IND_ON();
       else
           LEFT_IND_OFF();
       RIGHT_IND_OFF();
        clcd_print("<  ", LINE2(12));          // Display left arrow
    }
    if (*data == 0) {
        LEFT_IND_OFF();                        // Turn off both indicators
        RIGHT_IND_OFF();
        clcd_print("OFF", LINE2(12));          // Display "OFF"
    }
    if (*data == 2) {
        if (toggle)
            RIGHT_IND_ON();
        else
            RIGHT_IND_OFF();  
        LEFT_IND_OFF();   // Turn on right indicator
        clcd_print("  >", LINE2(12));          // Display right arrow
    }

}

void process_canbus_data() 
{   
    //process the CAN bus data
     uint16_t msg_id=0,len;
    char data[5];
    
    can_receive(&msg_id,data,&len);
    data[len]='\0';
    
    if(msg_id == SPEED_MSG_ID)
    {
         handle_speed_data(data,len);
    }
    else if(msg_id == GEAR_MSG_ID)
    {
         handle_gear_data(data,len);
    }
    else if(msg_id == RPM_MSG_ID)
    {
         handle_rpm_data(data,len);
    }
    else if(msg_id == INDICATOR_MSG_ID)
    {
         handle_indicator_data(data,len);
    }
    
    
}
