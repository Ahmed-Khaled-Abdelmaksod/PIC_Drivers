/* 
 * File:   MCAL_SPI.h
 * Author: Ahmed Khaled
 *
 */
#include"MCAL_SPI.h"


static void (*INTERRUPT_HANDLER)(void);
static void ctrl_config(spi_t *spi);

static void bits_config(spi_t *spi);
static void spi_interrupt_config(spi_t *spi);
Std_ReturnType spi_init(spi_t *spi)
{
    Std_ReturnType ret = E_NOT_OK;
    if(spi == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        SPI_DISABLE();
        SPI_MODE_CONFIG(spi->spi_mode);
        ctrl_config(spi);
#if SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        spi_interrupt_config(spi);
#endif
        bits_config(spi);
        SPI_ENABLE();
        ret = E_OK;
        
    }
    return ret;
}
Std_ReturnType spi_deInit(spi_t *spi)
{
    Std_ReturnType ret = E_NOT_OK;
    if(spi == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        SPI_DISABLE();
#if SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        SPI_INTERRUPT_DISABLE();
#endif
    }
}
Std_ReturnType spi_sendChar(uint8 data)
{

    SSPBUF = data;
    while(SPI_RECIEVE_STATE() == SPI_RECEIVE_NOT_COMPLETED);
    
    
    
}
Std_ReturnType spi_sendString(uint8 *data,uint16 len)
{
    uint16 counter = 0;
    for(counter = 0;counter < len ; counter++)
    {
        spi_sendChar(data[counter]);
    }
}
Std_ReturnType spi_readChar(uint8 *data)
{
    
    while(SPI_RECIEVE_STATE() == SPI_RECEIVE_NOT_COMPLETED);
    *data = SSPBUF;
    
}




////////////////////////////////


static void ctrl_config(spi_t *spi)
{
    switch(spi->clk_config.clk_polarity)
    {
        case SPI_HIGH_IDLE_STATE :
            SPI_SET_HIGH_IDLE_STATE();
            break;
        case SPI_LOW_IDLE_STATE :
            SPI_SET_LOW_IDLE_STATE();
            break;
        default : 
            SPI_SET_LOW_IDLE_STATE();           
    }
    switch(spi->clk_config.clk_transition)
    {
        case SPI_CLK_TRANSITION_ACTIVE_TO_IDLE:
            SPI_SET_CLK_TRANSITION_ACTIVE_TO_IDLE();
            break;
        case SPI_CLK_TRANSITION_IDLE_TO_ACTIVE:
            SPI_SET_CLK_TRANSITION_IDLE_TO_ACTIVE();
            break;
        default:
            SPI_SET_CLK_TRANSITION_IDLE_TO_ACTIVE();
    }
    if(spi->spi_mode == SPI_SLAVE_MODE_SS_ENSABLE || spi->spi_mode ==SPI_SLAVE_MODE_SS_DISABLE_SS_AS_IO)
    {
        SPI_SET_SLAVE_SAMPLE_CLEAR();
    }
    else
    {
        switch(spi->clk_config.sampling_position)
        {
            case SPI_MASTER_SAMPLE_AT_END:
                SPI_SET_MASTER_SAMPLE_AT_END();
                break;
            case SPI_MASTER_SAMPLE_AT_MIDDLE:
                SPI_SET_MASTER_SAMPLE_AT_MIDDLE();
                break;
            default:
                SPI_SET_MASTER_SAMPLE_AT_MIDDLE();
        }
    }
    
}


static void spi_interrupt_config(spi_t *spi)
{
    INTERRUPT_HANDLER = spi->SPI_INTERRUPT_HANDLER;
    
    
           /*******************************************8*/
        /*INTERRUPT SECTION */
#if (SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)        
        /** implement */
        SPI_INTERRUPT_DISABLE();
        SPI_CLEAR_INTERRUPT_FLAG();
        #if (INTERRUPT_FEATURE_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE)
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_PRIORITY_ENABLE();
            switch(spi->priority)
            {
                case SPI_HIGH_PRIORITY :
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    SPI_INTERRUPT_HIGH_PRIORITY();
                    break;
                case SPI_LOW_PRIORITY :
                    break;
                    INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                    SPI_INTERRUPT_LOW_PRIORITY();
                default :
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    SPI_INTERRUPT_HIGH_PRIORITY();
            }
            
        #else
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_PERIPHERAL_ENABLE();
            
        #endif
        SPI_INTERRUPT_ENABLE();
#endif 
}



static void bits_config(spi_t *spi)
{
    TRISCbits.RC5 = 0;
    TRISCbits.RC4 = 1;

    if(spi->spi_mode == SPI_SLAVE_MODE_SS_ENSABLE || spi->spi_mode ==SPI_SLAVE_MODE_SS_DISABLE_SS_AS_IO)
    {
        
        TRISCbits.RC3 = 1;
    }
    else
    {
        TRISCbits.RC3 = 0;
    }
    TRISAbits.RA5 = 1;
}

void SPI_ISR(void)
{
    SPI_CLEAR_INTERRUPT_FLAG();
    if(INTERRUPT_HANDLER)
    {
        INTERRUPT_HANDLER();
    }
}


