/* 
 * File:   MCAL_timer3.h
 * Author: Ahmed Khaled
 *
 * Created on 22 ??????, 2023, 10:57 ?
 */

#ifndef MCAL_TIMER3_H
#define	MCAL_TIMER3_H

/*================ INCLUDES ================*/
#include"../INTERRUPT/MCAL_interrupt_config.h"
#include"../INTERRUPT/MCAL_internal_interrupt.h"
#include"pic18f4620.h"
#include"../MCAL_std_types.h"
#include"../GPIO/MCAL_gpio.h"
/*================ DEFINITIONS ================*/
#define TIMER3_COUNTER_MODE             1U 
#define TIMER3_TIMER_MODE               0U

#define TIMER3_SYN_EXTERNAL_CLK         0U
#define TIMER3_ASYN_EXTERNAL_CLK        1U


#define TIMER3_PRESCALER_DIV_1          0
#define TIMER3_PRESCALER_DIV_2          1
#define TIMER3_PRESCALER_DIV_4          2
#define TIMER3_PRESCALER_DIV_8          3


#define TIMER3_RW_8BIT_MODE             0U
#define TIMER3_RW_16BIT_MODE            1U
/*================ MACRO FUNCTIONS ================*/

#define TIMER3_ENABLE()         (T3CONbits.TMR3ON = 1)
#define TIMER3_DISABLE()        (T3CONbits.TMR3ON = 0)

#define TIMER3_COUNTER_MODE_ENABLE()     (T3CONbits.TMR3CS = 1) 
#define TIMER3_TIMER_MODE_ENABLE()       (T3CONbits.TMR3CS = 0)


#define TIMER3_SYN_EXTERNAL_CLK_ENABLE()        (T3CONbits.T3SYNC = 0)
#define TIMER3_SYN_EXTERNAL_CLK_DISABLE()       (T3CONbits.T3SYNC = 1)

#define TIMER3_PRESCALER_VALUE(_CONFIG) (T3CONbits.T3CKPS = _CONFIG)


#define TIMER3_RW_8BIT_MODE_ENABLE()    (T3CONbits.RD16 = 0)
#define TIMER3_RW_16BIT_MODE_ENABLE()   (T3CONbits.RD16  = 1)
/*================ TYPES DEFINITIONS ================*/


typedef struct 
{
    uint16 preload_value ;
#if(TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    void (*timer3_handler)(void);
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
    uint8 priority :1;
#endif
#endif

uint8 prescaler :2;
uint8 timer3_mode :1;
uint8 external_syn_enable:1;
uint8 timer3_rw_mode:1;
uint8 reserved :2;
}timer3_t;


/*================ SW INTERFACES ================*/


/**
 * 
 * @param _timer3
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer3_init(const timer3_t * _timer3);
/**
 * 
 * @param _timer3
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer3_deinit(const timer3_t * _timer3);
/**
 * 
 * @param _timer3
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer3_read_value(const timer3_t * _timer3,uint16 *result);
/**
 * 
 * @param _timer3
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer3_write_value(const timer3_t * _timer3,uint16 result);





#endif	/* MCAL_TIMER3_H */

