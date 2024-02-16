/* 
 * File:   MCAL_ccp.h
 * Author: Ahmed Khaled
 *
 * Created on 28 ??????, 2023, 08:33 ?
 */

#ifndef MCAL_CCP_H
#define	MCAL_CCP_H
/*================ INCLUDES ================*/
#include"MCAL_ccp_config.h"
#include"../MCAL_std_types.h"
#include"../GPIO/MCAL_gpio.h"
#include"../TIMER1/MCAL_timer1.h"
#include"../TIMER2/MCAL_timer2.h"
#include"../TIMER3/MCAL_timer3.h"
#include"../INTERRUPT/MCAL_interrupt_config.h"
#include"../INTERRUPT/MCAL_internal_interrupt.h"
/*================ DEFINITIONS ================*/
#define CCP_DISABLE_COMPARE_PWM_CAPTURE                                 (0U)
#define CCP_COMPARE_TOGGLE_OUT_ON_MATCH                                 (2U)
#define CCP_COMPARE_MODE_INIT_CCPX_PIN_LOW_ON_MATCH_IT_GOES_HIGH        (8U) // CCPxIF bit is set
#define CCP_COMPARE_MODE_INIT_CCPX_PIN_HIGH_ON_MATCH_IT_GOES_LOW        (9U) // CCPxIF bit is set
#define CCP_COMPARE_MODE_ON_MATCH_GEN_SW_INTERRUPT                      (10U) //(CCPxIF bit is set, CCPx pin reflects I/O state)
#define CCP_COMPARE_MODE_ON_GEN_SPECIAL_EVENT                           (11U) //CCPx match starts A/D conversion (CCPxIF bit is set)

#define CCP_CAPTURE_MODE_EVERY_FALLING_EDGE                             (4U)
#define CCP_CAPTURE_MODE_EVERY_RISING_EDGE                              (5U)
#define CCP_CAPTURE_MODE_EVERY_4TH_RISING_EDGE                          (6U)
#define CCP_CAPTURE_MODE_EVERY_16TH_RISING_EDGE                         (7U)

#define CCP_PWM_MODE_ON                                                 (12U)

#define CCP_CAPTURE_READY   0X01
#define CCP_CAPTURE_NOT_READY   0X00

/*================ TYPES DEFINITIONS ================*/

typedef union
{
    struct {
        uint8 low;
        uint8 high;
    };
    
    struct {
        uint16 value;
    };
}reg_t;


typedef enum  
{
    COMPARE_MODE = 0,
    CAPTURE_MODE ,
    PWM_MODE
}ccp_mode_t;
typedef enum 
{
    CCP1_MODULE = 0,
    CCP2_MODULE,
            
}ccp_module_t;

typedef enum 
{
    CCPX_TIMER1_CLK_SRC = 0,
    CCP1_TIMER1_SRC_CCP2_TIMER3_SRC,
    CCPX_TIMER3_CLK_SRC             
                 
}ccp_clk_src_t;

// add comp & pwm 
typedef struct
{
    ccp_module_t ccp_selected;
    ccp_mode_t ccp_mode;
    ccp_clk_src_t ccp_clk_src;
    uint8 inner_mode_selection;
    pin_config_t ccp_pin;
#if((CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE) )
    void (*ccp2_handler)(void);
    uint8 ccp2_priority :1;
#endif
#if((CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE) )
    void (*ccp1_handler)(void);
    uint8 ccp1_priority :1;
#endif 
}ccp_t;
/*================ MACRO FUNCTIONS ================*/

#define CCP1_SET_MODE(_CONFIG)     (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)     (CCP2CONbits.CCP2M = _CONFIG)

// CLK SRC FOR CCP MODULES

#define CCPS_TIMER1_CLK_SRC()           \
    do{ \
    T3CONbits.T3CCP1 = 0; \
    T3CONbits.T3CCP2 = 0; \
}while(0)

#define CCP1_TIMER1_CLK_SRC_CCP2_TIMER3_CLK_SRC()           \
    do{ \
    T3CONbits.T3CCP1 = 1; \
    T3CONbits.T3CCP2 = 0; \
}while(0)

#define CCPS_TIMER3_CLK_SRC()           \
    do{ \
    T3CONbits.T3CCP1 = 0; \
    T3CONbits.T3CCP2 = 1; \
}while(0)


/*================ SW INTERFACES ================*/

Std_ReturnType ccp_init(const ccp_t *ccp);
Std_ReturnType ccp_deinit(const ccp_t *ccp);

#if((CCP1_MODE == CCP_CAPTURE_ON) ||(CCP2_MODE == CCP_CAPTURE_ON))
Std_ReturnType ccp_is_captured_done(const ccp_t *ccp,uint8 *capture_state);
Std_ReturnType ccp_read_captured_value(const ccp_t *ccp,uint16 *capture_value);
#endif


#endif	/* MCAL_CCP_H */

