/* 
 * File:   MCAL_gpio.h
 * Author: Ahmed Khaled
 *
 * Created on 30 ?????, 2023, 11:03 ?
 */

#ifndef MCAL_GPIO_H
#define	MCAL_GPIO_H
#define DEBUG_ON  1
#define DEBUG_OFF 0

/*____________________ Include sector ___________________*/
#include<pic18f4620.h>
#include"../MCAL_std_types.h"
#include"../device_config.h"

/*____________________ Definition sector ___________________*/

#define MAX_PORT_PINS 8


typedef enum 
{
    LOW,
    HIGH
}Logic;

typedef enum
{
    OUTPUT,
    INPUT
}pin_direction;

typedef enum 
{
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}Port;

typedef enum
{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
}pin_index;

typedef struct 
{
    uint8 port :3;
    uint8 pin :3;
    uint8 direction :1;
    uint8 logic :1;
}pin_config_t;


/*________________________ Macros Functions Definitions ____________________*/

#define SET_BIT(REGISTER,BIT_POS)       ((REGISTER) |=  (1<<BIT_POS))
#define CLEAR_BIT(REGISTER,BIT_POS)     ((REGISTER) &= ~(1<<BIT_POS))
#define TOGGLE_BIT(REGISTER,BIT_POS)    ((REGISTER) ^=  (1<<BIT_POS))
#define READ_BIT(REGISTER,BIT_POS)      (((REGISTER)>>BIT_POS)&0X01)

/*________________________ Function Declaration _______________________*/

// pin functions
Std_ReturnType gpio_pin_direction_init(const pin_config_t *pin);
Std_ReturnType gpio_pin_get_direction(const pin_config_t *pin,uint8 *direction);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin,uint8 logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin,uint8 *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin);
Std_ReturnType gpio_pin_init(const pin_config_t *pin);

// port function 
Std_ReturnType gpio_port_direction_init(Port port_index,uint8 direction);
Std_ReturnType gpio_port_get_direction(Port port_index,uint8 *direction);
Std_ReturnType gpio_port_write_logic(Port port,uint8 logic);
Std_ReturnType gpio_port_read_logic(Port port,uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(Port port);
        
        
#endif	/* MCAL_GPIO_H */

