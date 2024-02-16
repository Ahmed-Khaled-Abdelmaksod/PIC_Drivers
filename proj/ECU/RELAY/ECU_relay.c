#include"ECU_relay.h"

/**
 * 
 * @param relay
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType relay_init(relay_t *relay)
{
    Std_ReturnType ret = E_NOT_OK;
    if(relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
          .port = relay->port,
          .pin = relay->pin,
          .direction = OUTPUT,
        };
        ret = gpio_pin_init(&pin);
    }
    return ret;
}
/**
 * 
 * @param relay
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType relay_turn_on(relay_t *relay)
{
    Std_ReturnType ret = E_NOT_OK;
    if(relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
          .port = relay->port,
          .pin = relay->pin,
          .direction = OUTPUT,
        };
        ret = gpio_pin_write_logic(&pin,HIGH);
    }
    return ret;
}
/**
 * 
 * @param relay
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType relay_turn_off(relay_t *relay)
{
    Std_ReturnType ret = E_NOT_OK;
    if(relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
          .port = relay->port,
          .pin = relay->pin,
          .direction = OUTPUT,
        };
       ret = gpio_pin_write_logic(&pin,LOW);
    }
    return ret;
}

