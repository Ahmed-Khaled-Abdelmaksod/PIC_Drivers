/* 
 * File:   ECU_button.h
 * Author: Ahmed Khaled
 *
 * Created on 09 ?????, 2023, 04:28 ?
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

#include"../../MCAL/GPIO/MCAL_gpio.h"

typedef enum
{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_state_t;

typedef enum
{
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGH
}button_active_t;

typedef struct 
{
    uint8 port :4;
    uint8 pin  :3;
    button_state_t state;
    button_active_t active;
}button_t;
/**
 * 
 * @param pin
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType button_init(button_t *button);
/**
 * 
 * @param pin
 * @param state
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType button_get_state(button_t *button,uint8 *state);

#endif	/* ECU_BUTTON_H */

