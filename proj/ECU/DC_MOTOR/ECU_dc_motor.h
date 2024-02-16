/* 
 * File:   ECU_dc_motor.h
 * Author: Ahmed Khaled
 *
 * Created on 11 ?????, 2023, 01:34 ?
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

#include"../../MCAL/GPIO/MCAL_gpio.h"


typedef struct 
{
    pin_config_t pins[2];
}dc_motor_t;
/**
 * 
 * @param motor
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType dc_motor_init(dc_motor_t *motor);
/**
 * 
 * @param motor
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission  
 */
Std_ReturnType dc_motor_move_right(dc_motor_t *motor);
/**
 * 
 * @param motor
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType dc_motor_move_left(dc_motor_t *motor);
/**
 * 
 * @param motor
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType dc_motor_stop(dc_motor_t *motor);

#endif	/* ECU_DC_MOTOR_H */

