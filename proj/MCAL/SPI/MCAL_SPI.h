/* 
 * File:   MCAL_SPI.h
 * Author: Ahmed Khaled
 *
 * Created on 03 ??????, 2024, 07:38 ?
 */

#ifndef MCAL_SPI_H
#define	MCAL_SPI_H

/*================ INCLUDES ================*/
#include"../MCAL_std_types.h"
#include"pic18f4620.h"
#include"../device_config.h"
#include"../INTERRUPT/MCAL_interrupt_config.h"
#include"../INTERRUPT/MCAL_internal_interrupt.h"
#include"../GPIO/MCAL_gpio.h"

/*================ DEFINITIONS ================*/

#define SPI_MASTER_SAMPLE_AT_END            1
#define SPI_MASTER_SAMPLE_AT_MIDDLE         0

#define SPI_CLK_TRANSITION_ACTIVE_TO_IDLE   1
#define SPI_CLK_TRANSITION_IDLE_TO_ACTIVE   0

#define SPI_RECEIVE_COMPLETED               1
#define SPI_RECEIVE_NOT_COMPLETED           0

#define SPI_WCOL_ERROR                      1
#define SPI_NO_COLLISION_ERROR              0


#define SPI_OVERFLOW_ERROR                  1
#define SPI_NO_OVERFLOW_ERROR               0

#define SPI_HIGH_IDLE_STATE                 1
#define SPI_LOW_IDLE_STATE                  0

#define SPI_HIGH_PRIORITY                   1
#define SPI_LOW_PRIORITY                    0


#define SPI_MASTER_MODE_CLK_FOSC_OVER_4         0
#define SPI_MASTER_MODE_CLK_FOSC_OVER_16        1
#define SPI_MASTER_MODE_CLK_FOSC_OVER_64        2   
#define SPI_MASTER_MODE_CLK_TMR2_OUTPUT         3
#define SPI_SLAVE_MODE_SS_ENSABLE               4
#define SPI_SLAVE_MODE_SS_DISABLE_SS_AS_IO      5
/*================ TYPES DEFINITIONS ================*/




typedef struct 
{
    uint8 sampling_position:1;
    uint8 clk_transition:1;
    uint8 clk_polarity:1;
}spi_clk_config_t;
typedef struct {
#if SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*SPI_INTERRUPT_HANDLER)(void);
    uint8 priority;
#endif
    uint8 spi_mode; 
    spi_clk_config_t clk_config;
}spi_t;


/*================ MACRO FUNCTIONS ================*/
#define SPI_RECIEVE_STATE()     (SSPSTATbits.BF)


#define SPT_READ_WRITE_COLLISION_DETECTION()    (SSPCON1bits.WCOL)
#define SPI_CLEAR_WCOL()                        (SSPCON1bits.WCOL = 0)


#define SPT_READ_OVERFLOW_STATUS()              (SSPCON1bits.SSPOV)
#define SPI_CLEAR_OVERFLOW_ERROR()              (SSPCON1bits.SSPOV = 0)

#define SPI_ENABLE()                            (SSPCON1bits.SSPEN = 1)
#define SPI_DISABLE()                           (SSPCON1bits.SSPEN = 0)

#define SPI_SET_HIGH_IDLE_STATE()               (SSPCON1bits.CKP = 1)
#define SPI_SET_LOW_IDLE_STATE()                (SSPCON1bits.CKP = 0)

#define SPI_SET_CLK_TRANSITION_ACTIVE_TO_IDLE() (SSPSTATbits.CKE = 1)
#define SPI_SET_CLK_TRANSITION_IDLE_TO_ACTIVE() (SSPSTATbits.CKE = 0)

#define SPI_SET_MASTER_SAMPLE_AT_END()              (SSPSTATbits.SMP = 1)
#define SPI_SET_MASTER_SAMPLE_AT_MIDDLE()           (SSPSTATbits.SMP = 0)
#define SPI_SET_SLAVE_SAMPLE_CLEAR()                (SSPSTATbits.SMP = 0)

#define SPI_MODE_CONFIG(_CONFIG)                (SSPCON1bits.SSPM = _CONFIG)

/*================ SW INTERFACES ================*/
Std_ReturnType spi_init(spi_t *spi);
Std_ReturnType spi_deInit(spi_t *spi);
Std_ReturnType spi_sendChar(uint8 data);
Std_ReturnType spi_sendString(uint8 *data,uint16 len);
Std_ReturnType spi_readChar(uint8 *data);



#endif	/* MCAL_SPI_H */

