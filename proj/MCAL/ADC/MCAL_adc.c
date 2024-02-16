#include"MCAL_adc.h"
/*HELPER FUNCTIONS */
static void ADC_format_selection(const adc_t *_adc);
static void ADC_vref_src(const adc_t *_adc);
static void ADC_SET_CHANNEL_AS_INPUT(const adc_t *_adc);

static void (*ADC_handler)(void) = NULL;
/**
 * 
 * @param _adc
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_init(const adc_t *_adc)
{
    
    Std_ReturnType ret = E_OK;
    if(_adc == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*DISABLE THE ADC MODULE */
        ADC_MODULE_DISABLE();
        /*******************************************8*/
        /*INTERRUPT SECTION */
#if (ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)        
        /** implement */
        ADC_INTERRUPT_DISABLE();
        ADC_INTERRUPT_CLEAR_FLAG();
        #if (INTERRUPT_FEATURE_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE)
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_PRIORITY_ENABLE();
            switch(_adc->priority)
            {
                case HIGH_PRIORITY :
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    ADC_INTERRUPT_PRIORITY_HIGH();
                    break;
                case LOW_PRIORITY :
                    break;
                    INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                    ADC_INTERRUPT_PRIORITY_LOW();
                default :
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    ADC_INTERRUPT_PRIORITY_HIGH();
            }
            
        #else
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_PERIPHERAL_ENABLE();
            
        #endif
            ADC_handler = _adc->adc_handler;
        ADC_INTERRUPT_ENABLE();
#endif     
        /*******************************************8*/
        /** set the default channel as input */
        ADC_SET_CHANNEL_AS_INPUT(_adc);
        
        /** Aqusation time select */
        ADC_AQU_TIME_SELECT(_adc->adc_acq_time);
        
        /* DEAFULT CHANNEL SELECTOR*/
        ADC_CHANNEL_SELECTOR(_adc->adc_channel);
        
        /* FORMAT RESULT */
        ADC_format_selection(_adc);
        
        /* VREF Source */
        ADC_vref_src(_adc);
        
        /* ADC CLK SRC */
        ADC_CLK_SRC(_adc->adc_clk);
        
        /*ENABLE THE ADC MODULE */
        ADC_MODULE_ENABLE();
    }
    return ret ;
}
/**
 * 
 * @param _adc
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_deinit(const adc_t *_adc)
{
    Std_ReturnType ret = E_OK;
    if(_adc == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*******************************************8*/
        /*INTERRUPT SECTION */        
#if (ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)
        ADC_INTERRUPT_DISABLE();
#endif
        /*******************************************8*/
        /** DISABLE ADC MODULE */
        ADC_MODULE_DISABLE();
    }
    return ret ;
}
/**
 * 
 * @param _adc
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_start_conversion(const adc_t *_adc)
{
    Std_ReturnType ret = E_OK;
    if(_adc == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_START_CONVERSTION();
    }
    return ret ;
}
/**
 * 
 * @param _adc
 * @param channel
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_select_channel(const adc_t *_adc,adc_channel_selector_t channel)
{
    Std_ReturnType ret = E_OK;
    if(_adc == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_CHANNEL_SELECTOR(channel);
        ADC_SET_CHANNEL_AS_INPUT(_adc);
    }
    return ret ;
}
/**
 * 
 * @param _adc
 * @param state
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_is_conversion_done(const adc_t *_adc,uint8 *state)
{
    Std_ReturnType ret = E_OK;
    if((_adc == NULL) || (state == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        (*state) = (uint8)(!ADC_GET_CONVERSTION_STATE());
    }
    return ret ;
}
/**
 * 
 * 
 * @param _adc
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_get_result(const adc_t *_adc,uint16 *result)
{
    Std_ReturnType ret = E_OK;
    if((_adc == NULL) || (result == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(_adc->adc_justified)
        {
            case ADC_RIGHT_JUSTIFIED :
                (*result) = (uint16)(256*(ADRESH&0X03)+ADRESL);
                break;
            case ADC_LEFT_JUSTIFIED :
                (*result) = (uint16)(4 * ADRESH+(ADRESL>>6));
                break;
            default :
                (*result) = (uint16)(256*(ADRESH&0X03)+ADRESL);
        }
    }
    return ret ;
}
/**
 * 
 * @param _adc
 * @param result
 * @param channel
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_get_result_blocking(const adc_t *_adc,uint16 *result,adc_channel_selector_t channel)
{
    Std_ReturnType ret = E_OK;
    if((_adc == NULL) || (result == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = ADC_select_channel(_adc,channel);
        ADC_start_conversion(_adc);
        while(ADC_GET_CONVERSTION_STATE());
        ret = ADC_get_result(_adc,result);
    }
    return ret ;
}
/**
 * 
 * @param _adc
 * @param channel
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */

Std_ReturnType ADC_start_conversion_interrupt(const adc_t *_adc,adc_channel_selector_t channel)
{
    Std_ReturnType ret = E_OK;
    if(_adc == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_INTERRUPT_CLEAR_FLAG();
        ADC_select_channel(_adc,channel);
        ADC_start_conversion(_adc); 
    }
    return ret ;
}


static void ADC_format_selection(const adc_t *_adc)
{
    switch(_adc->adc_justified)
    {
        case ADC_RIGHT_JUSTIFIED : 
            ADC_RIGHT_JUSTIFIED_SET();
            break;
        case ADC_LEFT_JUSTIFIED :
            ADC_LEFT_JUSTIFIED_SET();
            break;
        default :     
            ADC_RIGHT_JUSTIFIED_SET();
    }
}


static void ADC_vref_src(const adc_t *_adc)
{
    switch(_adc->vref_src)
    {
        case ADC_VREF_DEAFULT : 
            ADC_DEFAULT_REFERENCE();
            break;
        case ADC_VREF_EXTERNAL :
            ADC_EXTERNAL_REFERENCE();
            break;
        default :     
            ADC_DEFAULT_REFERENCE();
    }
}

static void ADC_SET_CHANNEL_AS_INPUT(const adc_t *_adc)
{
    switch(_adc->adc_channel)
    {
        case ADC_CHANNEL_AN0:   SET_BIT(TRISA,_TRISA_TRISA0_POSN); break;
        case ADC_CHANNEL_AN1:   SET_BIT(TRISA,_TRISA_TRISA1_POSN); break;
        case ADC_CHANNEL_AN2:   SET_BIT(TRISA,_TRISA_TRISA2_POSN); break;
        case ADC_CHANNEL_AN3:   SET_BIT(TRISA,_TRISA_TRISA3_POSN); break;
        case ADC_CHANNEL_AN4:   SET_BIT(TRISA,_TRISA_TRISA5_POSN); break;
        case ADC_CHANNEL_AN5:   SET_BIT(TRISE,_TRISE_TRISE0_POSN); break;
        case ADC_CHANNEL_AN6:   SET_BIT(TRISE,_TRISE_TRISE1_POSN); break;
        case ADC_CHANNEL_AN7:   SET_BIT(TRISE,_TRISE_TRISE2_POSN); break;
        case ADC_CHANNEL_AN8:   SET_BIT(TRISB,_TRISB_TRISB2_POSN); break;
        case ADC_CHANNEL_AN9:   SET_BIT(TRISB,_TRISB_TRISB3_POSN); break;
        case ADC_CHANNEL_AN10:  SET_BIT(TRISB,_TRISB_TRISB1_POSN); break;
        case ADC_CHANNEL_AN11:  SET_BIT(TRISB,_TRISB_TRISB4_POSN); break;
        case ADC_CHANNEL_AN12:  SET_BIT(TRISB,_TRISB_TRISB0_POSN); break;
    }
}
void ADC_ISR(void)
{
    ADC_INTERRUPT_CLEAR_FLAG();
    if(ADC_handler)
    {
        ADC_handler();
    }
}