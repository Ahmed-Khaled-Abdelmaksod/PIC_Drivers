/* 
 * File:   MCAL_interrupt_manage.h
 * Author: Ahmed Khaled
 *
 * Created on 07 ??????, 2023, 08:41 ?
 */

#ifndef MCAL_INTERRUPT_MANAGE_H
#define	MCAL_INTERRUPT_MANAGE_H


/* _____________________________ INCLUDES SECTION  ______________________________*/
#include"MCAL_interrupt_config.h"
#include"pic18f4620.h"

/* _____________________________ DEFINITIONS SECTION  ______________________________*/
/* _____________________________ MACRO FUNCTIONS SECTION  ______________________________*/
/* _____________________________ INTERFACES SECTION  ______________________________*/
void INT0_ISR();
void INT1_ISR();
void INT2_ISR();
void RB4_HIGH_TO_LOW_ISR();
void RB5_HIGH_TO_LOW_ISR();
void RB6_HIGH_TO_LOW_ISR();
void RB7_HIGH_TO_LOW_ISR();

void RB4_LOW_TO_HIGH_ISR();
void RB5_LOW_TO_HIGH_ISR();
void RB6_LOW_TO_HIGH_ISR();
void RB7_LOW_TO_HIGH_ISR();

/*
 *****************************************
 INTERNAL INTERRUPTS !!!!!!!!
 *******************************************
*/
void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);
void SPI_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGE_H */

