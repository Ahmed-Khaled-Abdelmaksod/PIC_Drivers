/* 
 * File:   MCAL_internal_interrupt.h
 * Author: Ahmed Khaled
 *
 * Created on 07 ??????, 2023, 08:41 ?
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H


/* _____________________________ INCLUDES SECTION  ______________________________*/
#include"MCAL_interrupt_config.h"
/* _____________________________ DEFINITIONS SECTION  ______________________________*/
/* _____________________________ MACRO FUNCTIONS SECTION  ______________________________*/
/***************** ADC ************************ */
#if (ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define ADC_INTERRUPT_CLEAR_FLAG()  (PIR1bits.ADIF = 0)

#define ADC_INTERRUPT_ENABLE()      (PIE1bits.ADIE = 1)
#define ADC_INTERRUPT_DISABLE()     (PIE1bits.ADIE = 0)


#if (INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define ADC_INTERRUPT_PRIORITY_HIGH() (IPR1bits.ADIP = 1)
#define ADC_INTERRUPT_PRIORITY_LOW()  (IPR1bits.ADIP = 0)


#endif
#endif
/***************************************************************************/
/***************** TIMER0 ************************ */
#if(TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define TIMER0_INTERRUPT_ENABLE()   (INTCONbits.TMR0IE = 1)
#define TIMER0_INTERRUPT_DISABLE()  (INTCONbits.TMR0IE = 0)

#define TIMER0_INTERRUPT_CLEAR_FLAG() (INTCONbits.TMR0IF = 0)
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define TIMER0_INTERRUPT_HIGH_PRIORITY()    (INTCON2bits.TMR0IP = 1) 
#define TIMER0_INTERRUPT_LOW_PRIORITY()     (INTCON2bits.TMR0IP = 0)
#endif
#endif


/***************************************************************************/
/***************** TIMER1 ************************ */
#if(TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define TIMER1_INTERRUPT_ENABLE()   (PIE1bits.TMR1IE = 1)
#define TIMER1_INTERRUPT_DISABLE()  (PIE1bits.TMR1IE = 0)

#define TIMER1_INTERRUPT_CLEAR_FLAG() (PIR1bits.TMR1IF = 0)
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define TIMER1_INTERRUPT_HIGH_PRIORITY()    (IPR1bits.TMR1IP = 1) 
#define TIMER1_INTERRUPT_LOW_PRIORITY()     (IPR1bits.TMR1IP = 0)
#endif
#endif





/***************************************************************************/
/***************** TIMER2 ************************ */
#if(TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define TIMER2_INTERRUPT_ENABLE()   (PIE1bits.TMR2IE = 1)
#define TIMER2_INTERRUPT_DISABLE()  (PIE1bits.TMR2IE = 0)

#define TIMER2_INTERRUPT_CLEAR_FLAG() (PIR1bits.TMR2IF = 0)
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define TIMER2_INTERRUPT_HIGH_PRIORITY()    (IPR1bits.TMR2IP = 1) 
#define TIMER2_INTERRUPT_LOW_PRIORITY()     (IPR1bits.TMR2IP = 0)
#endif
#endif




/***************************************************************************/
/***************** TIMER3 ************************ */
#if(TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define TIMER3_INTERRUPT_ENABLE()   (PIE2bits.TMR3IE = 1)
#define TIMER3_INTERRUPT_DISABLE()  (PIE2bits.TMR3IE = 0)

#define TIMER3_INTERRUPT_CLEAR_FLAG() (PIR2bits.TMR3IF = 0)
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define TIMER3_INTERRUPT_HIGH_PRIORITY()    (IPR2bits.TMR3IP = 1) 
#define TIMER3_INTERRUPT_LOW_PRIORITY()     (IPR2bits.TMR3IP = 0)
#endif
#endif


/***************************************************************************/
/***************** CCP1 ************************ */
#if(CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define CCP1_INTERRUPT_ENABLE()   (PIE1bits.CCP1IE = 1)
#define CCP1_INTERRUPT_DISABLE()  (PIE1bits.CCP1IE = 0)

#define CCP1_INTERRUPT_CLEAR_FLAG() (PIR1bits.CCP1IF = 0)
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define CCP1_INTERRUPT_HIGH_PRIORITY()    (IPR1bits.CCP1IP = 1) 
#define CCP1_INTERRUPT_LOW_PRIORITY()     (IPR1bits.CCP1IP = 0)
#endif
#endif



/***************************************************************************/
/***************** CCP2 ************************ */
#if(CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define CCP2_INTERRUPT_ENABLE()   (PIE2bits.CCP2IE = 1)
#define CCP2_INTERRUPT_DISABLE()  (PIE2bits.CCP2IE = 0)

#define CCP2_INTERRUPT_CLEAR_FLAG() (PIR2bits.CCP2IF = 0)
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define CCP2_INTERRUPT_HIGH_PRIORITY()    (IPR2bits.CCP2IP = 1) 
#define CCP2_INTERRUPT_LOW_PRIORITY()     (IPR2bits.CCP2IP = 0)
#endif
#endif


/***************** UART TX************************ */
#if(EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define EUSART_TX_INTERRUPT_ENABLE()   (PIE1bits.TXIE = 1)
#define EUSART_TX_INTERRUPT_DISABLE()  (PIE1bits.TXIE = 0)

#define EUSART_TX_READ_INTERRUPT_FLAG() (PIR1bits.TXIF)
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define EUSART_TX_INTERRUPT_HIGH_PRIORITY()    (IPR1bits.TXIP = 1) 
#define EUSART_TX_INTERRUPT_LOW_PRIORITY()     (IPR1bits.TXIP = 0)
#endif
#endif

/***************** UART RX************************ */
#if(EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define EUSART_RX_INTERRUPT_ENABLE()   (PIE1bits.RCIE = 1)
#define EUSART_RX_INTERRUPT_DISABLE()  (PIE1bits.RCIE = 0)

#define EUSART_RX_READ_INTERRUPT_FLAG() (PIR1bits.RCIF)
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define EUSART_RX_INTERRUPT_HIGH_PRIORITY()    (IPR1bits.RCIP = 1) 
#define EUSART_RX_INTERRUPT_LOW_PRIORITY()     (IPR1bits.RCIP = 0)
#endif
#endif

/***************** SPI ************************ */
#if(SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define SPI_INTERRUPT_ENABLE()   (PIE1bits.SSPIE = 1)
#define SPI_INTERRUPT_DISABLE()  (PIE1bits.SSPIE = 0)

#define SPI_READ_INTERRUPT_FLAG() (PIR1bits.SSPIF)
#define SPI_CLEAR_INTERRUPT_FLAG() (PIR1bits.SSPIF = 0)
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
#define SPI_INTERRUPT_HIGH_PRIORITY()    (IPR1bits.SSPIP = 1) 
#define SPI_INTERRUPT_LOW_PRIORITY()     (IPR1bits.SSPIP = 0)
#endif
#endif



/* _____________________________ INTERFACES SECTION  ______________________________*/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

