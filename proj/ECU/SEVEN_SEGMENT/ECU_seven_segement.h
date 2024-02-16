/* 
 * File:   ECU_seven_segement.h
 * Author: Ahmed Khaled
 *
 * Created on 11 ?????, 2023, 11:13 ?
 */

#ifndef ECU_SEVEN_SEGEMENT_H
#define	ECU_SEVEN_SEGEMENT_H

#include"../../MCAL/GPIO/MCAL_gpio.h"

typedef enum 
{
    SEVEN_SEGEMENT_COMMON_CATHODE,
    SEVEN_SEGEMENT_COMMON_ANODE
}seven_segement_state;

typedef struct
{
    pin_config_t pin[4];
    seven_segement_state state; 
}seven_segement_t;

/**
 * 
 * @param seg
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType seven_segement_init(seven_segement_t *seg);
/**
 * 
 * @param seg
 * @param number
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType seven_segement_write_number(seven_segement_t *seg,uint8 number);
#endif	/* ECU_SEVEN_SEGEMENT_H */

