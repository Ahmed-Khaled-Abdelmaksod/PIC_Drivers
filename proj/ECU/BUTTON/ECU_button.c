#include"ECU_button.h"

/**
 * 
 * @param pin
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType button_init(button_t *button)
{
    
    Std_ReturnType ret = E_NOT_OK;
    if(button == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
            .pin = button->pin,
            .port = button->port,
            .direction = INPUT,
        };
        gpio_pin_init(&pin);
    }
    return ret;
}
/**
 * 
 * @param pin
 * @param state
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType button_get_state(button_t *button,uint8 *state)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 logic = LOW;
    if((button == NULL) || (state == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
       pin_config_t pin = {
            .pin = button->pin,
            .port = button->port,
            .direction = INPUT,
        };
       ret = gpio_pin_read_logic(&pin,&logic);
       if(logic == HIGH)
       {
           if(button->state == BUTTON_ACTIVE_HIGH)
           {
               *state = BUTTON_PRESSED;
           }
           else if(button->state == BUTTON_ACTIVE_LOW)
           {
               *state = BUTTON_RELEASED;
           }
       }
       else if(logic == LOW)
       {
           if(button->state == BUTTON_ACTIVE_HIGH)
           {
               *state = BUTTON_RELEASED;
           }
           else if(button->state == BUTTON_ACTIVE_LOW)
           {
               *state = BUTTON_PRESSED;
           }
       }
        
    }
    return ret;
}
