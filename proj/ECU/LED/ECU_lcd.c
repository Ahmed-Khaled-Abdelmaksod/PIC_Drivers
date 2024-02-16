#include"ECU_led.h"

Std_ReturnType led_init(const led_t *led)
{
    Std_ReturnType state = E_NOT_OK;
    if(led == NULL)
    {
        state = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
          .direction = OUTPUT,
          .pin = led->pin,
          .port = led->port,
          .logic = led->state
        };
        gpio_pin_init(&pin);
        state = E_OK;
    }
    return state;
}
Std_ReturnType led_on(const led_t *led)
{
    Std_ReturnType state = E_NOT_OK;
    if(led == NULL)
    {
        state = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
          .direction = OUTPUT,
          .pin = led->pin,
          .port = led->port,
          .logic = led->state
        };
        gpio_pin_write_logic(&pin,HIGH);
        state = E_OK;
    }
    return state;
}
Std_ReturnType led_off(const led_t *led)
{
    Std_ReturnType state = E_NOT_OK;
    if(led == NULL)
    {
        state = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
          .direction = OUTPUT,
          .pin = led->pin,
          .port = led->port,
          .logic = led->state
        };
        gpio_pin_write_logic(&pin,LOW);
        state = E_OK;
    }
    return state;
}
Std_ReturnType led_toggle(const led_t *led)
{
    Std_ReturnType state = E_NOT_OK;
    if(led == NULL)
    {
        state = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
          .direction = OUTPUT,
          .pin = led->pin,
          .port = led->port,
          .logic = led->state
        };
        gpio_pin_toggle_logic(&pin);
        state = E_OK;
    }
    return state;
}