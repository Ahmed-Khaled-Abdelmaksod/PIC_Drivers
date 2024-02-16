/**
 * @author : Ahmed Khaled
 * @brief : Implementation of gpio.c 
 */
/*
 task -> start the implementation from the first function
 */

#include"MCAL_gpio.h"
#if DEBUG_ON
/*______________________ arrays contains registers ______________________*/
volatile uint8 *PORTS[5] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
volatile uint8 *TRISS[5] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *LATS[5]  = {&LATA,&LATB,&LATC,&LATE,&LATD};
// pin functions
/**
 * @brief used to set the direction of  a pin in a port
 * @param pin
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType gpio_pin_direction_init(const pin_config_t *pin)
{
    Std_ReturnType ret = E_NOT_OK;
    if((pin == NULL) || (pin->port > MAX_PORT_PINS-1) )
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(pin->direction)
        {
            case OUTPUT : 
                CLEAR_BIT(*TRISS[pin->port],pin->pin);
                break;
            case INPUT : 
                SET_BIT(*TRISS[pin->port],pin->pin);
                break;
        }
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param pin
 * @param direction
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType gpio_pin_get_direction(const pin_config_t *pin,uint8 *direction)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if((pin == NULL) || (direction == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction = READ_BIT(*TRISS[pin->port],pin->pin); 
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param pin
 * @param logic
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin,uint8 logic)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if((pin == NULL) || (logic > 1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(logic)
        {
            case HIGH : 
                SET_BIT((*PORTS[pin->port]),pin->pin);
                break;
            case LOW :
                CLEAR_BIT((*PORTS[pin->port]),pin->pin);
                break;
        }
        ret = E_OK;
    }
    return ret ;
}

/**
 * 
 * @param pin
 * @param logic
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin,uint8 *logic)
{
    Std_ReturnType ret = E_NOT_OK;
    if((pin == NULL) || (logic == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        (*logic) = READ_BIT(*PORTS[pin->port],pin->pin);
        ret = E_OK;
    }
    return ret;
}
/**
 * 
 * @param pin
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */

Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin)
{
    Std_ReturnType ret = E_NOT_OK;
    if(pin == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*LATS[pin->port],pin->pin);
        ret = E_OK;
    }
    return ret ;
}
/**
 * 
 * @param pin
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */

Std_ReturnType gpio_pin_init(const pin_config_t *pin)
{
    Std_ReturnType ret = E_NOT_OK;
    if(pin == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        ret = gpio_pin_direction_init(pin);
        ret = gpio_pin_write_logic(pin,pin->logic);
    }
    return ret;
}

// port function
/**
 * 
 * @param port_index
 * @param direction
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType gpio_port_direction_init(Port port_index,uint8 direction)
{
    Std_ReturnType state = E_NOT_OK;
    if((port_index > 4) || (direction > 1))
    {
        state = E_NOT_OK;
    }
    else
    {
        *TRISS[port_index] = direction;
        state = E_OK;
    }
    return state;
}

/**
 * 
 * @param port_index
 * @param direction
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType gpio_port_get_direction(Port port_index,uint8 *direction)
{
    Std_ReturnType state = E_NOT_OK;
    if((port_index > 4) || (direction == NULL))
    {
        state = E_NOT_OK;
    }
    else
    {
        *direction = *TRISS[port_index];
        state = E_OK;
    }
    return state;
}

/**
 * 
 * @param port
 * @param logic
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType gpio_port_write_logic(Port port,uint8 logic)
{
    Std_ReturnType state = E_NOT_OK;
    if((port > 4))
    {
        state = E_NOT_OK;
    }
    else
    {
        (*(PORTS[port])) = (uint8)logic;
        state = E_OK;   
    }
    return state;
    
}

/**
 * 
 * @param port
 * @param logic
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType gpio_port_read_logic(Port port,uint8 *logic)
{
    Std_ReturnType state = E_NOT_OK;
    if((port > 4) || (logic == NULL))
    {
        state = E_NOT_OK; 
    }
    else
    {
        (*logic) = *LATS[port];
        state = E_OK;
    }
    return state;
}

/**
 * 
 * @param port
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType gpio_port_toggle_logic(Port port)
{
    Std_ReturnType state = E_NOT_OK;
    if(port > 4)
    {
        state = E_NOT_OK;
    }
    else
    {
        *LATS[port] ^= 0xFF; 
        state = E_OK;
    }
    return state;
}

#endif