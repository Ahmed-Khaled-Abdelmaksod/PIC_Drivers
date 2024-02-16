/* 
 * File:   MCAL_timer1.h
 * Author: Ahmed Khaled
 *
 * Created on 21 ??????, 2023, 08:25 ?
 */

#ifndef MCAL_TIMER1_H
#define	MCAL_TIMER1_H

/*================ INCLUDES ================*/
#include"../INTERRUPT/MCAL_interrupt_config.h"
#include"../INTERRUPT/MCAL_internal_interrupt.h"
#include"pic18f4620.h"
#include"../MCAL_std_types.h"
#include"../GPIO/MCAL_gpio.h"
/*================ DEFINITIONS ================*/
#define TIMER1_COUNTER_MODE             1U 
#define TIMER1_TIMER_MODE               0U

#define TIMER1_SYN_EXTERNAL_CLK         0U
#define TIMER1_ASYN_EXTERNAL_CLK        1U

#define TIMER1_OSC_ON                   1U
#define TIMER1_OSC_OFF                  0U

#define TIMER1_PRESCALER_DIV_1          0
#define TIMER1_PRESCALER_DIV_2          1
#define TIMER1_PRESCALER_DIV_4          2
#define TIMER1_PRESCALER_DIV_8          3

#define TIMER1_CLK_FROM_TMR1            1U
#define TIMER1_CLK_FROM_OTHER_SRC       0U


#define TIMER1_RW_8BIT_MODE             0U
#define TIMER1_RW_16BIT_MODE            1U
/*================ TYPES DEFINITIONS ================*/


typedef struct 
{
#if(TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    void (*timer1_handler)(void);
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
    uint8 priority :1;
#endif
#endif
uint16 preload_value ;
uint8 prescaler :2;
uint8 timer1_mode :1;
uint8 external_syn_enable:1;
uint8 timer1_osc  :1;
uint8 timer1_rw_mode:1;
uint8 timer1_reserved:2;
}timer1_t;

/*================ MACRO FUNCTIONS ================*/

#define TIMER1_ENABLE()         (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE()        (T1CONbits.TMR1ON = 0)

#define TIMER1_COUNTER_MODE_ENABLE()     (T1CONbits.TMR1CS = 1) 
#define TIMER1_TIMER_MODE_ENABLE()       (T1CONbits.TMR1CS = 0) 

#define TIMER1_SYN_EXTERNAL_CLK_ENABLE()        (T1CONbits.T1SYNC = 0)
#define TIMER1_SYN_EXTERNAL_CLK_DISABLE()       (T1CONbits.T1SYNC = 1)

#define TIMER1_OSC_ENABLE()             (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_DISABLE()            (T1CONbits.T1OSCEN = 0)

#define TIMER1_PRESCALER_VALUE(_CONFIG) (T1CONbits.T1CKPS = _CONFIG)

#define TIMER1_CLK_SRC()                (T1CONbits.T1RUN)

#define TIMER1_RW_8BIT_MODE_ENABLE()    (T1CONbits.RD16 = 0)
#define TIMER1_RW_16BIT_MODE_ENABLE()   (T1CONbits.RD16 = 1)
/*================ SW INTERFACES ================*/


/**
 * 
 * @param _timer1
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer1_init(const timer1_t * _timer1);
/**
 * 
 * @param _timer1
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer1_deinit(const timer1_t * _timer1);
/**
 * 
 * @param _timer1
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer1_read_value(const timer1_t * _timer1,uint16 *result);
/**
 * 
 * @param _timer1
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer1_write_value(const timer1_t * _timer1,uint16 result);




#endif	/* MCAL_TIMER1_H */

