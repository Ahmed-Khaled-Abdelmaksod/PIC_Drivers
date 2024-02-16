/* 
 * File:   ECU_keypad.h
 * Author: Ahmed Khaled
 *
 * Created on 13 ?????, 2023, 04:25 ?
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

#include"../../MCAL/GPIO/MCAL_gpio.h"

#define KEYPAD_ROWS    4
#define KEYPAD_COLUMNS 4
#define _XTAL_FREQ 4000000UL
typedef struct
{
    pin_config_t rows[KEYPAD_ROWS];
    pin_config_t columns[KEYPAD_COLUMNS];
}keypad_t;
/**
 * 
 * @param keypad
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType keypad_init(keypad_t *keypad);
/**
 * 
 * @param keypad
 * @param value
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission  
 */
Std_ReturnType keypad_get_value(keypad_t *keypad,uint8 *value);

#endif	/* ECU_KEYPAD_H */

