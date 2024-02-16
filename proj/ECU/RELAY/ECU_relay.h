/* 
 * File:   ECU_relay.h
 * Author: Ahmed Khaled
 *
 * Created on 10 ?????, 2023, 06:40 ?
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

#include"../../MCAL/GPIO/MCAL_gpio.h"

typedef enum 
{
    RELAY_OFF,
    RELAY_ON
}relay_state_t;
typedef struct
{
    uint8 port :4;
    uint8 pin :3;
    relay_state_t state;
}relay_t;
/**
 * 
 * @param relay
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType relay_init(relay_t *relay);
/**
 * 
 * @param relay
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType relay_turn_on(relay_t *relay);
/**
 * 
 * @param relay
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType relay_turn_off(relay_t *relay);

#endif	/* ECU_RELAY_H */

