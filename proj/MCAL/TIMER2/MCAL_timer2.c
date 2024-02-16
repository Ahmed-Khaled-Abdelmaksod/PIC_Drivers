#include"MCAL_timer2.h"

static void(*timer2_handler)(void) = NULL;
static uint8 preloaded=0;



/**
 * 
 * @param _timer2
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer2_init(const timer2_t * _timer2)
{
    Std_ReturnType ret = E_OK;
    if(_timer2 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER2_DISABLE();
        
        #if(TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        timer2_handler = _timer2->timer2_handler;
        TIMER2_INTERRUPT_CLEAR_FLAG();
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
        INTERRUPT_PRIORITY_ENABLE() ;
        switch(_timer2->priority)
        {
                case HIGH_PRIORITY:
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    TIMER2_INTERRUPT_HIGH_PRIORITY();
                    break;
                case LOW_PRIORITY:
                    INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                    TIMER2_INTERRUPT_LOW_PRIORITY();
                    break;
                        
                default :
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    TIMER2_INTERRUPT_HIGH_PRIORITY();
        }  
#elif
       INTERRUPT_PERIPHERAL_ENABLE();
#endif
        TIMER2_INTERRUPT_ENABLE();
#endif
        TMR2 = _timer2->preloaded_value;
        TIMER2_SET_PRESCALER_VALUE(_timer2->prescaler);
        TIMER2_SET_POSTSCALER_VALUE(_timer2->postscaler);
        TIMER2_ENABLE();
    }
    return ret;
}
/**
 * 
 * @param _timer2
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer2_deinit(const timer2_t * _timer2)
{
    Std_ReturnType ret = E_OK;
    if(_timer2 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER2_DISABLE();
    #if(TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        TIMER2_INTERRUPT_DISABLE();
    #endif
    }
    return ret;
}
/**
 * 
 * @param _timer2
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer2_read_value(const timer2_t * _timer2,uint8 *result)
{
    Std_ReturnType ret = E_OK;
    if((_timer2 == NULL) || (result == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *result = TMR2;
    }
    return ret;
}
/**
 * 
 * @param _timer2
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer2_write_value(const timer2_t * _timer2,uint8 result)
{
    Std_ReturnType ret = E_OK;
    if(_timer2 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR2 = (uint8)(result);
    }
    return ret;
}



/* *************************************** TIMER2 ISR *************************************** */
void TMR2_ISR(void)
{
    TIMER2_INTERRUPT_CLEAR_FLAG();
    TMR2 = preloaded;
    if(timer2_handler)
    {
        timer2_handler();
    }
}