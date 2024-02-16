#include"ECU_seven_segement.h"

/**
 * 
 * @param seg
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType seven_segement_init(seven_segement_t *seg)
{
    Std_ReturnType ret = E_NOT_OK;
    if(seg == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_init(&(seg->pin[PIN0]));
        gpio_pin_init(&(seg->pin[PIN1]));
        gpio_pin_init(&(seg->pin[PIN2]));
        gpio_pin_init(&(seg->pin[PIN3]));
    }
    return ret;
}
/**
 * 
 * @param seg
 * @param number
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType seven_segement_write_number(seven_segement_t *seg,uint8 number)
{
    Std_ReturnType ret = E_NOT_OK;
    if((seg == NULL) || (number > 9))
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(seg->pin[PIN0]),(number>>PIN0)&0X01);
        gpio_pin_write_logic(&(seg->pin[PIN1]),(number>>PIN1)&0X01);
        gpio_pin_write_logic(&(seg->pin[PIN2]),(number>>PIN2)&0X01);
        gpio_pin_write_logic(&(seg->pin[PIN3]),(number>>PIN3)&0X01);
    }
    return ret;
}
