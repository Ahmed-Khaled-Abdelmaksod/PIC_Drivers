
#include"MCAL_interrupt_manage.h"
/**
 * 0 -> go from low to high
 * 1 -> go from high to low
 */
static volatile uint8 r4_flag = 0;
static volatile uint8 r5_flag = 0;
static volatile uint8 r6_flag = 0;
static volatile uint8 r7_flag = 0;
#if (INTERRUPT_FEATURE_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE)

void __interrupt() high_priority_func()
{
    if((INTERRUPT_ENABLE == PIE1bits.ADIE)&&(INTERRUPT_OCCUR == PIR1bits.ADIF))
    {
        ADC_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE)&&(INTERRUPT_OCCUR == INTCONbits.TMR0IF))
    {
        TMR0_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == T1CONbits.TMR1ON)&&(INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TMR1_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE)&&(INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
        TMR2_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE )&&(INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TMR3_ISR();
    }
    else{/*NOTHING*/}
    
    
    if((INTERRUPT_ENABLE ==  PIE1bits.CCP1IE)&&(INTERRUPT_OCCUR == PIR1bits.CCP1IF))
    {
        CCP1_ISR();
    }
    else{/*NOTHING*/}
    
    
    if((INTERRUPT_ENABLE ==  PIE2bits.CCP2IE)&&(INTERRUPT_OCCUR == PIR2bits.CCP2IF))
    {
        CCP2_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{/*NOTHING*/}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB4 == HIGH)&&(r4_flag==0))
    {
        r4_flag = 1;
        RB4_LOW_TO_HIGH_ISR();    
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB4 == LOW)&&(r4_flag==1))
    {
        r4_flag = 0;
        RB4_HIGH_TO_LOW_ISR();    
    }
    else{/*NOTHING*/}
    
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB5 == HIGH)&&(r5_flag==0))
    {
        r5_flag = 1;
        RB5_LOW_TO_HIGH_ISR();    
    }
    else{/*NOTHING*/}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB5 == LOW)&&(r5_flag==1))
    {
        r5_flag = 0;
        RB5_HIGH_TO_LOW_ISR();    
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB6 == HIGH)&&(r6_flag==0))
    {
        r6_flag = 1;
        RB6_LOW_TO_HIGH_ISR();    
    }
    else{/*NOTHING*/}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB6 == LOW)&&(r6_flag==1))
    {
        r6_flag = 0;
        RB6_HIGH_TO_LOW_ISR();    
    }
    else{/*NOTHING*/}
    
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB7 == HIGH)&&(r7_flag==0))
    {
        r7_flag = 1;
        RB7_LOW_TO_HIGH_ISR();    
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB7 == LOW)&&(r7_flag==1))
    {
        r7_flag = 0;
        RB7_HIGH_TO_LOW_ISR();    
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == PIE1bits.TXIE)&&(INTERRUPT_OCCUR == PIR1bits.TXIF))
    {
        EUSART_TX_ISR();  
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == PIE1bits.RCIE)&&(INTERRUPT_OCCUR == PIR1bits.RCIF))
    {
        EUSART_RX_ISR();    
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE)&&(INTERRUPT_OCCUR == PIR1bits.SSPIF))
    {
        SPI_ISR();    
    }
    else{/*NOTHING*/}
    
}
void __interrupt(low_priority) low_priority_func()
{
   if((INTERRUPT_ENABLE == INTCON3bits.INT2IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }else{/*NOTHING*/}
   if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB7 == HIGH)&&(r7_flag==0))
    {
        r7_flag = 1;
        RB7_LOW_TO_HIGH_ISR();    
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB7 == LOW)&&(r7_flag==1))
    {
        r7_flag = 0;
        RB7_HIGH_TO_LOW_ISR();    
    }
    else{/*NOTHING*/}
}

#else
void __interrupt() high_priority_func()
{
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{/*NOTHING*/}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else{/*NOTHING*/}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else{/*NOTHING*/}
    
     if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB4 == HIGH)&&(r4_flag==0))
    {
        r4_flag = 1;
        RB4_LOW_TO_HIGH_ISR();    
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB4 == LOW)&&(r4_flag==1))
    {
        r4_flag = 0;
        RB4_HIGH_TO_LOW_ISR();    
    }
    else{/*NOTHING*/}
    
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB5 == HIGH)&&(r5_flag==0))
    {
        r5_flag = 1;
        RB5_LOW_TO_HIGH_ISR();    
    }
    else{/*NOTHING*/}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB5 == LOW)&&(r5_flag==1))
    {
        r5_flag = 0;
        RB5_HIGH_TO_LOW_ISR();    
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB6 == HIGH)&&(r6_flag==0))
    {
        r6_flag = 1;
        RB6_LOW_TO_HIGH_ISR();    
    }
    else{/*NOTHING*/}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB6 == LOW)&&(r6_flag==1))
    {
        r6_flag = 0;
        RB6_HIGH_TO_LOW_ISR();    
    }
    else{/*NOTHING*/}
    
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB7 == HIGH)&&(r7_flag==0))
    {
        r7_flag = 1;
        RB7_LOW_TO_HIGH_ISR();    
    }
    else{/*NOTHING*/}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE)&&(INTERRUPT_OCCUR == INTCONbits.RBIF)&&(PORTBbits.RB7 == LOW)&&(r7_flag==1))
    {
        r7_flag = 0;
        RB7_HIGH_TO_LOW_ISR();    
    }
    else{/*NOTHING*/}
}
#endif
