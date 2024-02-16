/* 
 * File:   MCAL_euart.h
 * Author: Ahmed Khaled
 *
 * Created on 30 ?????, 2024, 05:29 ?
 */

#ifndef MCAL_EUART_H
#define	MCAL_EUART_H

/*================ INCLUDES ================*/
#include"../MCAL_std_types.h"
#include"../GPIO/MCAL_gpio.h"
#include"pic18f4620.h"
#include"../device_config.h"
#include"../INTERRUPT/MCAL_interrupt_config.h"
#include"../INTERRUPT/MCAL_interrupt_manage.h"
#include"../INTERRUPT/MCAL_internal_interrupt.h"

/*================ DEFINITIONS ================*/




/****** SYN OR ASYN MODES MACROS ******/
#define EUSART_ASYN_MODE            0
#define EUSART_SYN_MODE             1

/********** High Baud Rate Select bit MACROS **********/
#define EUSART_BAUDRATE_GEN_HIGH_SPEED        1
#define EUSART_BAUDRATE_GEN_LOW_SPEED         0

/*********** Transmit Enable bit Macros *****************/
#define EUSART_TX_ENABLE         1
#define EUSART_TX_DISABLE        0

/********** TX9: 9-Bit Transmit Enable bit ****************/
#define EUSART_TX_8BIT_DATA            0
#define EUSART_TX_9BIT_DATA            1

/********* Transmit Shift Register Status bit **************/

#define EUSART_TX_TSR_EMPTY                 1
#define EUSART_TX_TSR_FULL                  0



/********** RX9: 9-Bit Receiver Enable bit ****************/
#define EUSART_RX_8BIT_DATA            0
#define EUSART_RX_9BIT_DATA            1


/*********** Receiver Enable bit Macros *****************/
#define EUSART_RX_ENABLE         1
#define EUSART_RX_DISABLE        0


    
/*********** ERRORS bit Macros *****************/
#define EUSART_RX_FRAMING_ERROR_HAPPEN           1
#define EUSART_RX_FRAMING_ERROR_NOT_HAPPEN       0

#define EUSART_RX_OVERRUN_ERROR_HAPPEN           1
#define EUSART_RX_OVERRUN_ERROR_NOT_HAPPEN       0

/************** BAUD RATE GENERATION ******************/

#define EUSART_8BIT_BAUDRATE                     0
#define EUSART_16BIT_BAUDRATE                    1

#define EUSART_HIGH_PRIORITY                     1
#define EUSART_LOW_PRIORITY                      0


#define EUSART_TX_INT_ON                         1
#define EUSART_TX_INT_OFF                        0

#define EUSART_RX_INT_ON                         1
#define EUSART_RX_INT_OFF                        0
/*================ Macro INTERFACES ================*/

#define EUSART_ASYN_MODE_ENABLE()                    (TXSTAbits.SYNC = EUSART_ASYN_MODE)
#define EUSART_SYN_MODE_ENABLE()                     (TXSTAbits.SYNC = EUSART_SYN_MODE)

#define EUSART_BAUDRATE_GEN_HIGH_SPEED_ENABLE()         (TXSTAbits.BRGH = EUSART_BAUDRATE_GEN_HIGH_SPEED)
#define EUSART_BAUDRATE_GEN_LOW_SPEED_ENABLE()          (TXSTAbits.BRGH = EUSART_BAUDRATE_GEN_LOW_SPEED)

#define EUSART_TX_ENABLE_FUN()                          (TXSTAbits.TXEN = EUSART_TX_ENABLE)
#define EUSART_TX_DISABLE_FUN()                         (TXSTAbits.TXEN = EUSART_TX_DISABLE)

#define EUSART_TX_8BIT_DATA_ENABLE()                    (TXSTAbits.TX9 = EUSART_TX_8BIT_DATA)
#define EUSART_TX_9BIT_DATA_ENABLE()                    (TXSTAbits.TX9 = EUSART_TX_9BIT_DATA)

#define EUSART_TX_READ_TSR_STATUS()                     (TXSTAbits.TRMT)

#define EUSART_TX_READ_TX9_BIT()                        (TXSTA1bits.TX9D)
#define EUSART_TX_WRITE_TX9_BIT(_CONFIG)                (TXSTA1bits.TX9D = _CONFIG)

#define EUSART_ENABLE()                                 (RCSTAbits.SPEN = 1)
#define EUSART_DISABLE()                                (RCSTAbits.SPEN = 0)


#define EUSART_RX_8BIT_DATA_ENABLE()                    (RCSTAbits.RX9 = EUSART_RX_8BIT_DATA)
#define EUSART_RX_9BIT_DATA_ENABLE()                    (RCSTAbits.RX9 = EUSART_RX_9BIT_DATA)

#define EUSART_RX_ENABLE_FUN()                          (RCSTAbits.CREN = EUSART_RX_ENABLE)
#define EUSART_RX_DISABLE_FUN()                         (RCSTAbits.CREN = EUSART_RX_DISABLE)

#define EUSART_RX_READ_FRAMING_ERROR_BIT()              (RCSTAbits.FERR)
#define EUSART_RX_READ_OVERRUN_ERROR_BIT()              (RCSTAbits.OERR)

#define EUSART_RX_READ_RX9_BIT()                          (RCSTAbits.RX9D)

#define EUSART_8BIT_BAUDRATE_ENABLE()                     (BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE) 
#define EUSART_16BIT_BAUDRATE_ENABLE()                     (BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE) 



/*================ TYPES DEFINITIONS ================*/
typedef enum 
{
    EUSART_BAUDRATE_ASYN_8BIT_LOW_SPEED_CONFIG = 0,
    EUSART_BAUDRATE_ASYN_8BIT_HIGH_SPEED_CONFIG ,
    EUSART_BAUDRATE_ASYN_16BIT_LOW_SPEED_CONFIG ,
    EUSART_BAUDRATE_ASYN_16BIT_HIGH_SPEED_CONFIG ,
    EUSART_BAUDRATE_SYN_8BIT_CONFIG ,
    EUSART_BAUDRATE_SYN_16BIT_CONFIG ,
}baud_rate_config_t;

typedef struct 
{
    uint8 priority :1;
    uint8 tx_int_enable :1;
    uint8 tx_enable     :1;
    uint8 tx_9bit_enable :1;
}uart_tx_t;


typedef struct 
{
    uint8 priority :1;
    uint8 rx_int_enable :1;
    uint8 rx_enable     :1;
    uint8 rx_9bit_enable :1;
}uart_rx_t;



typedef union
{

    struct 
    {
        uint8 ferr :1;
        uint8 oerr :1;
        uint8 reserved :6;
    };
    uint8 status;
}rx_error_t;

typedef struct 
{
    uint32 baudrate ;
    baud_rate_config_t baud_rate_config; 
    uart_tx_t uart_tx;
    uart_rx_t uart_rx;
    rx_error_t rx_error;
    void (*EUSART_TXHANDLER)(void);
    void (*EUSART_RXHANDLER)(void);
    void (*EUSART_FRAMINGERRORHANDLER)(void);
    void (*EUSART_OVERRUNERRORTXHANDLER)(void);
}uart_t;

/*================ SW INTERFACES ================*/
Std_ReturnType eusart_asyn_init(uart_t *uart);
Std_ReturnType eusart_tx_asyn_init(uart_t *uart);
Std_ReturnType eusart_rx_asyn_init(uart_t *uart);

Std_ReturnType eusart_asyn_writeChar_blocking(char data);
Std_ReturnType eusart_asyn_writestr_blocking(char *data,uint16 length);
Std_ReturnType eusart_asyn_writeChar_nonblocking(char data);
Std_ReturnType EUSART_ASYNC_RX_Restart(void);

Std_ReturnType eusart_asyn_readChar_blocking(char *data);
Std_ReturnType eusart_asyn_readChar_nonblocking(char *data);




#endif	/* MCAL_EUART_H */

