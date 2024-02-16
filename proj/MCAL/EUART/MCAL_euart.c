/* 
 * File:   MCAL_euart.c
 * Author: Ahmed Khaled
 *
 * Created on 30 ?????, 2024, 05:29 ?
 */

#include"MCAL_euart.h"


static void (*EUSART_TX_PTR)(void);
static void (*EUSART_RX_PTR)(void);
static void (*EUSART_FERR_PTR)(void);
static void (*EUSART_OERR_PTR)(void);



static void baudrate_configuration(uart_t *uart);
static void interrupt_tx_feature_enable(uart_t *uart);
static void interrupt_rx_feature_enable(uart_t *uart);

Std_ReturnType eusart_asyn_init(uart_t *uart)
{
    Std_ReturnType ret = E_NOT_OK;
    if(uart == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(uart->uart_tx.tx_enable == EUSART_TX_ENABLE)
        {
            eusart_tx_asyn_init(uart);
        }
        else if(uart->uart_rx.rx_enable = EUSART_RX_ENABLE)
        {
            eusart_rx_asyn_init(uart);
        }
    }
    return ret;
}


Std_ReturnType eusart_tx_asyn_init(uart_t *uart)
{
    Std_ReturnType ret = E_NOT_OK;
    if(uart == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EUSART_TX_PTR = uart->EUSART_TXHANDLER;
        EUSART_DISABLE();
        baudrate_configuration(uart);
        EUSART_ASYN_MODE_ENABLE();
        if(uart->uart_tx.tx_int_enable == EUSART_TX_INT_ON)
        {
            interrupt_tx_feature_enable(uart);
        }
        if(uart->uart_tx.tx_9bit_enable == EUSART_TX_9BIT_DATA)
        {
            EUSART_TX_9BIT_DATA_ENABLE();
        }
        else 
        {
            EUSART_TX_8BIT_DATA_ENABLE();
        }
        EUSART_TX_ENABLE_FUN();
        EUSART_ENABLE();
        ret = E_OK;
    }
    return ret;
}



Std_ReturnType eusart_rx_asyn_init(uart_t *uart)
{
    Std_ReturnType ret = E_NOT_OK;
    if(uart == NULL)
    {
        ret = E_NOT_OK;
    }
    else
        {
        EUSART_RX_PTR = uart->EUSART_RXHANDLER;
        EUSART_FERR_PTR = uart->EUSART_FRAMINGERRORHANDLER;
        EUSART_OERR_PTR = uart->EUSART_OVERRUNERRORTXHANDLER;
        EUSART_DISABLE();
        baudrate_configuration(uart);
        EUSART_ASYN_MODE_ENABLE();
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        if(uart->uart_rx.rx_int_enable == EUSART_RX_INT_ON)
        {
            interrupt_rx_feature_enable(uart);
        }
        if(uart->uart_rx.rx_9bit_enable == EUSART_RX_9BIT_DATA)
        {
            EUSART_RX_9BIT_DATA_ENABLE();
        }
        else 
        {
            EUSART_RX_8BIT_DATA_ENABLE();
        }

        EUSART_RX_ENABLE_FUN();
        EUSART_ENABLE();
    }
    return ret;
}



Std_ReturnType eusart_asyn_writeChar_blocking(char data)
{
    Std_ReturnType ret = E_OK;
    while(EUSART_TX_READ_TSR_STATUS() == EUSART_TX_TSR_FULL);
    EUSART_TX_INTERRUPT_ENABLE();
    TXREG = data;
    return ret;
}
Std_ReturnType eusart_asyn_writestr_blocking(char *data,uint16 length){
    Std_ReturnType ret = E_NOT_OK;
    uint16 counter = 0;
    if(data == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(counter = 0; counter<length;counter++)
        {
            eusart_asyn_writeChar_blocking(data[counter]);
        }
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType eusart_asyn_writeChar_nonblocking(char data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(EUSART_TX_READ_TSR_STATUS() == EUSART_TX_TSR_EMPTY)
    {
        TXREG = data;
        ret = E_OK;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}


Std_ReturnType eusart_asyn_readChar_blocking(char *data){
    Std_ReturnType ret = E_NOT_OK;
    while(!EUSART_RX_READ_INTERRUPT_FLAG());
    *data = RCREG;
    ret = E_OK;
    return ret;
    
}

Std_ReturnType eusart_asyn_readChar_nonblocking(char *data){
    Std_ReturnType ret = E_NOT_OK;
    if(1 == PIR1bits.RCIF){
        *data = RCREG;
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}


Std_ReturnType EUSART_ASYNC_RX_Restart(void){
    Std_ReturnType ret = E_OK;
    RCSTAbits.CREN = 0; /* Disables receiver */
    RCSTAbits.CREN = 1; /* Enables receiver */
    return ret;
}


/****************************** STATIC FUNCTIONS *******************************/
static void baudrate_configuration(uart_t *uart)
{
    float temp = 0;
    switch(uart->baud_rate_config)
    {
        case EUSART_BAUDRATE_ASYN_8BIT_LOW_SPEED_CONFIG :
            EUSART_ASYN_MODE_ENABLE();
            EUSART_8BIT_BAUDRATE_ENABLE();
            EUSART_BAUDRATE_GEN_LOW_SPEED_ENABLE();
            temp = ((_XTAL_FREQ/uart->baudrate) / 64) - 1;
            break;
        case EUSART_BAUDRATE_ASYN_8BIT_HIGH_SPEED_CONFIG :

            EUSART_ASYN_MODE_ENABLE();
            EUSART_8BIT_BAUDRATE_ENABLE();
            EUSART_BAUDRATE_GEN_HIGH_SPEED_ENABLE();
            temp = ((_XTAL_FREQ/uart->baudrate) / 16) - 1;
            
            break;
        case EUSART_BAUDRATE_ASYN_16BIT_LOW_SPEED_CONFIG :

            EUSART_ASYN_MODE_ENABLE();
            EUSART_16BIT_BAUDRATE_ENABLE();
            EUSART_BAUDRATE_GEN_LOW_SPEED_ENABLE();
            
            temp = ((_XTAL_FREQ/uart->baudrate) / 16) - 1;
            break;
        case EUSART_BAUDRATE_ASYN_16BIT_HIGH_SPEED_CONFIG :
            
            EUSART_ASYN_MODE_ENABLE();
            EUSART_16BIT_BAUDRATE_ENABLE();
            EUSART_BAUDRATE_GEN_HIGH_SPEED_ENABLE();
            temp = ((_XTAL_FREQ/uart->baudrate) / 4) - 1;
            break;
        case EUSART_BAUDRATE_SYN_8BIT_CONFIG :
            EUSART_SYN_MODE_ENABLE();
            EUSART_8BIT_BAUDRATE_ENABLE();
            temp = ((_XTAL_FREQ/uart->baudrate) / 4) - 1;
            
            break;
        case EUSART_BAUDRATE_SYN_16BIT_CONFIG :
            EUSART_SYN_MODE_ENABLE();
            EUSART_16BIT_BAUDRATE_ENABLE();
            temp = ((_XTAL_FREQ/uart->baudrate) / 4) - 1;
            break;
        default :;
    }
    SPBRG = (uint8)((uint32)temp);
    SPBRGH = (uint8)((uint32)temp >> 8);
}



static void interrupt_tx_feature_enable(uart_t *uart)
{
    EUSART_TX_INTERRUPT_DISABLE();
#if(EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
    #if (INTERRUPT_FEATURE_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE)
        switch(uart->uart_tx.priority)
        {
            case EUSART_HIGH_PRIORITY : 
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                break;
            case EUSART_LOW_PRIORITY :
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                break;
            default :
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();     
        }    
    #else
        INTERRUPT_PERIPHERAL_ENABLE();
    #endif
        INTCONbits.PEIE = 1;
        EUSART_TX_INTERRUPT_ENABLE();
#endif
}


static void interrupt_rx_feature_enable(uart_t *uart)
{
    EUSART_RX_INTERRUPT_DISABLE();
#if(EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
    INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
    #if (INTERRUPT_FEATURE_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE)
        switch(uart->uart_rx.priority)
        {
            case EUSART_HIGH_PRIORITY : 
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                break;
            case EUSART_LOW_PRIORITY :
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                break;
            default :
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();     
        }    
    #else
        INTERRUPT_PERIPHERAL_ENABLE();
    #endif
        INTCONbits.PEIE = 1;
        EUSART_RX_INTERRUPT_ENABLE();
#endif
    
}

/************************* INTERRUPT HANDLERS **********************/
void EUSART_TX_ISR(void)
{
    EUSART_TX_INTERRUPT_DISABLE();
    if(EUSART_TX_PTR)
    {
        EUSART_TX_PTR();
    }
}


void EUSART_RX_ISR(void)
{
    uint8 data = RCREG;
    if(EUSART_RX_PTR)
    {
        EUSART_RX_PTR();
    }
    if(EUSART_FERR_PTR)
    {
        EUSART_FERR_PTR();
    }
    if(EUSART_OERR_PTR)
    {
        EUSART_OERR_PTR();
    }
}
