/* 
 * File:   MCAL_external_interrupt.h
 * Author: Ahmed Khaled
 *
 * Created on 07 ??????, 2023, 08:40 ?
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* _____________________________ INCLUDES SECTION  ______________________________*/
#include"MCAL_interrupt_config.h"
/* _____________________________ DEFINITIONS SECTION  ______________________________*/
/* _____________________________ MACRO FUNCTIONS SECTION  ______________________________*/

#if (INTERRUPT_FEATURE_INTX_ENABLE==INTERRUPT_FEATURE_ENABLE)
/*INT0 SECTION */
#define EXT_INT0_INTERRUPT_ENABLE() (INTCONbits.INT0IE = 1)
#define EXT_INT0_INTERRUPT_DISABLE() (INTCONbits.INT0IE = 0)
#define EXT_INT0_CLEAR_FLAG() (INTCONbits.INT0IF = 0)
#define EXT_INT0_FALLING_EDGE() (INTCON2bits.INTEDG0 = 0)
#define EXT_INT0_RISING_EDGE() (INTCON2bits.INTEDG0 = 1)

/*INT1 SECTION */

#define EXT_INT1_INTERRUPT_ENABLE() (INTCON3bits.INT1IE = 1)
#define EXT_INT1_INTERRUPT_DISABLE() (INTCON3bits.INT1IE = 0)
#define EXT_INT1_CLEAR_FLAG() (INTCON3bits.INT1IF = 0)
#define EXT_INT1_FALLING_EDGE() (INTCON2bits.INTEDG1 = 0)
#define EXT_INT1_RISING_EDGE() (INTCON2bits.INTEDG1 = 1)


/*INT2 SECTION */

#define EXT_INT2_INTERRUPT_ENABLE() (INTCON3bits.INT2IE = 1)
#define EXT_INT2_INTERRUPT_DISABLE() (INTCON3bits.INT2IE = 0)
#define EXT_INT2_CLEAR_FLAG() (INTCON3bits.INT2IF = 0)
#define EXT_INT2_FALLING_EDGE() (INTCON2bits.INTEDG2 = 0)
#define EXT_INT2_RISING_EDGE() (INTCON2bits.INTEDG2 = 1)

#if (INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define EXT_INT1_HIGH_PRIORITY() (INTCON3bits.INT1P = 1)
#define EXT_INT1_LOW_PRIORITY()  (INTCON3bits.INT1P = 0)
#define EXT_INT2_HIGH_PRIORITY() (INTCON3bits.INT2P = 1)
#define EXT_INT2_LOW_PRIORITY()  (INTCON3bits.INT2P = 0)
#endif



#endif

/************************** PORTB ON CHANGE 4:7*/
#define RX_INTERRUPT_ON_CHANGE_PORTB_ENABLE()   (INTCONbits.RBIE = 1)
#define RX_INTERRUPT_ON_CHANGE_PORTB_DISABLE()  (INTCONbits.RBIE = 0)
#define RX_INTERRUPT_ON_CHANGE_CLEAR_FLAG()     (INTCONbits.RBIF = 0)
#if (INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define RX_INTERRUPT_ON_CHANGE_HIGH_PRIORITY()  (INTCON2bits.RBIP = 1)
#define RX_INTERRUPT_ON_CHANGE_LOW_PRIORITY()   (INTCON2bits.RBIP = 0)
#endif


/* _____________________________ TYPES SECTION  ______________________________*/
typedef void(*ptr_ISR)(void);
typedef enum 
{
    EDGE_FALLING,
    EDGE_RISING
}intx_edge_t;

typedef enum 
{
    INTX_PRIORITY_LOW,
    INTX_PRIORITY_HIGH
}intx_priority_t;

typedef enum 
{
    SRC_INT0,
    SRC_INT1,
    SRC_INT2,
}intx_src_t;

typedef struct 
{
    void (*ptr_ISR)(void);
    pin_config_t pin;
    intx_edge_t edge;
    intx_priority_t priority;
    intx_src_t source;
}intx_interrupt_t;

typedef struct 
{
    ptr_ISR ptr_to_isr_high_to_low;
    ptr_ISR ptr_to_isr_low_to_high;
    pin_config_t pin;
    intx_priority_t priority;
}rx_interrupt_t;



/* _____________________________ INTERFACES SECTION  ______________________________*/
/**
 * 
 * @param intx
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType intx_init(const intx_interrupt_t *intx);
/**
 * 
 * @param intx
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType intx_deinit(const intx_interrupt_t *intx);


/**
 * 
 * @param intx
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType rx_init(const rx_interrupt_t *rx);

/**
 * 
 * @param intx
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType rx_deinit(const rx_interrupt_t *rx);
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

