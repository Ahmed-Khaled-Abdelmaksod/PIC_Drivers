/* 
 * File:   ECU_led.h
 * Author: Ahmed Khaled
 *
 * Created on 30 ?????, 2023, 11:06 ?
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

#include"../../MCAL/GPIO/MCAL_gpio.h"

typedef enum
{
    LED_OFF,
    LED_ON
}led_state;


typedef struct 
{
    uint8 port  :4; // one bit for future use
    uint8 pin   :3;
    uint8 state :1;
}led_t;

/*Module functions*/
Std_ReturnType led_init(const led_t *led);
Std_ReturnType led_on(const led_t *led);
Std_ReturnType led_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);

#endif	/* ECU_LED_H */

