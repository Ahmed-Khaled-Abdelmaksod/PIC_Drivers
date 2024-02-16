#include"ECU_dc_motor.h"

/**
 * 
 * @param motor
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType dc_motor_init(dc_motor_t *motor)
{
    Std_ReturnType ret = E_NOT_OK;
    if(motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_init(&(motor->pins[0]));
        ret = gpio_pin_init(&(motor->pins[1]));
    }
    return ret;
}
/**
 * 
 * @param motor
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission  
 */
Std_ReturnType dc_motor_move_right(dc_motor_t *motor)
{
     Std_ReturnType ret = E_NOT_OK;
    if(motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(motor->pins[0]),HIGH);
        gpio_pin_write_logic(&(motor->pins[1]),LOW);
    }
    return ret;
}
/**
 * 
 * @param motor
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType dc_motor_move_left(dc_motor_t *motor)
{
     Std_ReturnType ret = E_NOT_OK;
    if(motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        gpio_pin_write_logic(&(motor->pins[0]),LOW);
        gpio_pin_write_logic(&(motor->pins[1]),HIGH);
    }
    return ret;
}
/**
 * 
 * @param motor
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType dc_motor_stop(dc_motor_t *motor)
{
     Std_ReturnType ret = E_NOT_OK;
    if(motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        gpio_pin_write_logic(&(motor->pins[0]),LOW);
        gpio_pin_write_logic(&(motor->pins[1]),LOW);
    }
    return ret;
}




