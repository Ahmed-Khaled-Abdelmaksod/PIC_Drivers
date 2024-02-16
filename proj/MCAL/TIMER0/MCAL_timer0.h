/* 
 * File:   MCAL_timer0.h
 * Author: Ahmed Khaled
 *
 * Created on 18 ??????, 2023, 12:32 ?
 */
/* TEST THE DRIVER ONLY !!!! */
#ifndef MCAL_TIMER0_H
#define	MCAL_TIMER0_H
/*================ INCLUDES ================*/
#include"../INTERRUPT/MCAL_interrupt_config.h"
#include"../INTERRUPT/MCAL_internal_interrupt.h"
#include"pic18f4620.h"
#include"../MCAL_std_types.h"
#include"../GPIO/MCAL_gpio.h"
/*================ DEFINITIONS ================*/
#define TIMER0_PRESCALER_CLK    0U
#define TIMER0_MAIN_CLK         1U

#define TIMER0_EXTERNAL_CLK_ON  1U
#define TIMER0_INTERNAL_CLK_ON  0U

#define TIMER0_PRESCALER_ON     1U
#define TIMER0_PRESCALER_OFF    0U

#define TIMER0_8BIT_MODE_ON     1U
#define TIMER0_16BIT_MODE_ON    0U

#define TIMER0_FALLING_EDGE     1U
#define TIMER0_RISING_EDGE      0U
/*================ TYPES DEFINITIONS ================*/

typedef enum 
{
    TIMER0_PRESCALER_DIV_2 = 0,
    TIMER0_PRESCALER_DIV_4,
    TIMER0_PRESCALER_DIV_8,
    TIMER0_PRESCALER_DIV_16,
    TIMER0_PRESCALER_DIV_32,
    TIMER0_PRESCALER_DIV_64,
    TIMER0_PRESCALER_DIV_128,
    TIMER0_PRESCALER_DIV_256,
}timer0_prescaler_value_t;


typedef struct 
{
    uint16 preload_value ;
#if(TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    void (*timer0_handler)(void);
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
    uint8 priority :1;
#endif
#endif
    uint8 clk_src :1;
    uint8 prescaler_enable :1;
    uint8 timeer0_mode :1;
    uint8 edge :1;
    timer0_prescaler_value_t prescaler ;
    
}timer0_t;
/*================ MACRO FUNCTIONS ================*/



#define TIMER0_ENABLE()         (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()        (T0CONbits.TMR0ON = 0)

#define TIMER0_8BIT_MODE()      (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_MODE()     (T0CONbits.T08BIT = 0)

#define TIMER0_EXTERNAL_CLK()   (T0CONbits.T0CS = 1)
#define TIMER0_INTERNAL_CLK()   (T0CONbits.T0CS = 0)

#define TIMER0_EXT_FALLING_EDGE() (T0CONbits.T0SE = 1)
#define TIMER0_EXT_RISING_EDGE()  (T0CONbits.T0SE = 0)

#define TIMER0_PRESCALER_ENABLE()  (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE() (T0CONbits.PSA = 1)

#define TIMER0_PRESCALER_ASSIGN(_CONFIG)  (T0CONbits.T0PS = _CONFIG)


/*================ SW INTERFACES ================*/
/**
 * 
 * @param _timer0
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer0_init(const timer0_t * _timer0);
/**
 * 
 * @param _timer0
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer0_deinit(const timer0_t * _timer0);
/**
 * 
 * @param _timer0
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer0_read_value(const timer0_t * _timer0,uint16 *result);
/**
 * 
 * @param _timer0
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer0_write_value(const timer0_t * _timer0,uint16 result);


#endif	/* MCAL_TIMER0_H */

