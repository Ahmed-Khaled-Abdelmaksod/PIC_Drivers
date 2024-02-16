/* 
 * File:   MCAL_timer2.h
 * Author: Ahmed Khaled
 *
 * Created on 22 ??????, 2023, 12:38 ?
 */

#ifndef MCAL_TIMER2_H
#define	MCAL_TIMER2_H


/*================ INCLUDES ================*/
#include"../INTERRUPT/MCAL_interrupt_config.h"
#include"../INTERRUPT/MCAL_internal_interrupt.h"
#include"pic18f4620.h"
#include"../MCAL_std_types.h"
#include"../GPIO/MCAL_gpio.h"
/*================ DEFINITIONS ================*/

#define TIMER2_PRESCALER_DIV_1          0
#define TIMER2_PRESCALER_DIV_4          1
#define TIMER2_PRESCALER_DIV_16         2


#define TIMER2_POSTSCALER_DIV_1         0
#define TIMER2_POSTSCALER_DIV_2         1
#define TIMER2_POSTSCALER_DIV_3         2
#define TIMER2_POSTSCALER_DIV_4         3
#define TIMER2_POSTSCALER_DIV_5         4
#define TIMER2_POSTSCALER_DIV_6         5
#define TIMER2_POSTSCALER_DIV_7         6
#define TIMER2_POSTSCALER_DIV_8         7
#define TIMER2_POSTSCALER_DIV_9         8
#define TIMER2_POSTSCALER_DIV_10        9
#define TIMER2_POSTSCALER_DIV_11        10
#define TIMER2_POSTSCALER_DIV_12        11
#define TIMER2_POSTSCALER_DIV_13        12
#define TIMER2_POSTSCALER_DIV_14        13
#define TIMER2_POSTSCALER_DIV_15        14
#define TIMER2_POSTSCALER_DIV_16        15

/*================ TYPES DEFINITIONS ================*/

typedef struct 
{
#if(TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    void (*timer2_handler)(void);
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
    uint8 priority :1;
#endif
#endif
    uint8 preloaded_value;
    uint8 postscaler :4;
    uint8 prescaler :2;
}timer2_t;


/*================ MACRO FUNCTIONS ================*/

#define TIMER2_ENABLE()                  (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE()                 (T2CONbits.TMR2ON = 0)

#define TIMER2_SET_PRESCALER_VALUE(_CONFIG)     (T2CONbits.T2CKPS  = _CONFIG)

#define TIMER2_SET_POSTSCALER_VALUE(_CONFIG)     (T2CONbits.TOUTPS = _CONFIG)


/*================ SW INTERFACES ================*/


/**
 * 
 * @param _timer2
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer2_init(const timer2_t * _timer2);
/**
 * 
 * @param _timer2
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer2_deinit(const timer2_t * _timer2);
/**
 * 
 * @param _timer2
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer2_read_value(const timer2_t * _timer2,uint8 *result);
/**
 * 
 * @param _timer2
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer2_write_value(const timer2_t * _timer2,uint8 result);


#endif	/* MCAL_TIMER2_H */

