#include"MCAL_timer3.h"




static void (*timer3_handler)(void) = NULL;
static uint16 preloaded = 0;


/*      STATIC FUNCTIONS(HELPER FUNCTION)               */


static void timer3_mode_set(const timer3_t * _timer3);
static void timer3_syn_set(const timer3_t * _timer3);
static void timer3_rw_set(const timer3_t * _timer3);








/**
 * 
 * @param _timer3
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer3_init(const timer3_t * _timer3)
{
    Std_ReturnType ret = E_OK;
    if(_timer3 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        TIMER3_DISABLE();
        /***
         interrupt handling
         */
        
        preloaded = _timer3->preload_value;
        /*handle interrupt */
#if(TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        timer3_handler = _timer3->timer3_handler;
        TIMER3_INTERRUPT_CLEAR_FLAG();
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
        INTERRUPT_PRIORITY_ENABLE() ;
        switch(_timer3->priority)
        {
                case HIGH_PRIORITY:
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    TIMER3_INTERRUPT_HIGH_PRIORITY();
                    break;
                case LOW_PRIORITY:
                    INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                    TIMER3_INTERRUPT_LOW_PRIORITY();
                    break;
                        
                default :
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    TIMER3_INTERRUPT_HIGH_PRIORITY();
        }  
#elif
       INTERRUPT_PERIPHERAL_ENABLE();
#endif
        TIMER3_INTERRUPT_ENABLE();
#endif
        
        TMR3H = (uint8)(_timer3->preload_value>>8);
        TMR3L = (uint8)(_timer3->preload_value);
        TIMER3_PRESCALER_VALUE(_timer3->prescaler);
        timer3_mode_set(_timer3);
        timer3_syn_set(_timer3);
        timer3_rw_set(_timer3);
        TIMER3_ENABLE();
        
        
        ret = E_OK;
    }
    return ret;
}
/**
 * 
 * @param _timer3
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer3_deinit(const timer3_t * _timer3)
{
    Std_ReturnType ret = E_OK;
    if(_timer3 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        TIMER3_DISABLE();
    #if(TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        TIMER3_INTERRUPT_DISABLE();
    #endif
        
        ret = E_OK;
    }
    return ret;
}
/**
 * 
 * @param _timer3
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer3_read_value(const timer3_t * _timer3,uint16 *result)
{
    Std_ReturnType ret = E_OK;
    uint8 l_low = 0;
    uint8 l_high = 0;
    if((_timer3 == NULL) || (result == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_low = TMR3L;
        l_high = TMR3H;
        (*result) = (uint16)(l_low + (l_high << 8));
        
        ret = E_OK;
    }
    return ret;
}
/**
 * 
 * @param _timer3
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer3_write_value(const timer3_t * _timer3,uint16 result)
{
    Std_ReturnType ret = E_OK;
    if(_timer3 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        preloaded = result;
        TMR3L = (uint8)result;
        TMR3H = (uint8)(result>>8);
        
        ret = E_OK;
    }
    return ret;
}



/*____________________________ ISR ____________________________*/

void TMR3_ISR(void)
{
    TIMER3_INTERRUPT_CLEAR_FLAG();
    TMR3L = (uint8)(preloaded);
    TMR3H = (uint8)((preloaded)>>8);
    if(timer3_handler)
    {
        timer3_handler();
    }
}




static void timer3_mode_set(const timer3_t * _timer3)
{
    switch(_timer3->timer3_mode)
    {
        case TIMER3_COUNTER_MODE: 
            TIMER3_COUNTER_MODE_ENABLE();
            break;
        case TIMER3_TIMER_MODE:
            TIMER3_TIMER_MODE_ENABLE();
            break;
        default :
            TIMER3_TIMER_MODE_ENABLE();
    }
}
static void timer3_syn_set(const timer3_t * _timer3)
{
    switch(_timer3->external_syn_enable)
    {
        case TIMER3_SYN_EXTERNAL_CLK:
            TIMER3_SYN_EXTERNAL_CLK_ENABLE();
            break;
            
        case TIMER3_ASYN_EXTERNAL_CLK:
            TIMER3_SYN_EXTERNAL_CLK_DISABLE();
            
            break;
        default:
            TIMER3_SYN_EXTERNAL_CLK_ENABLE();
    }
}
static void timer3_rw_set(const timer3_t * _timer3)
{
    switch(_timer3->timer3_rw_mode)
    {
        case TIMER3_RW_8BIT_MODE:
            TIMER3_RW_8BIT_MODE_ENABLE();
            break;
            
        case TIMER3_RW_16BIT_MODE: 
            TIMER3_RW_16BIT_MODE_ENABLE();
            break;
        default : 
            TIMER3_RW_16BIT_MODE_ENABLE();
    }
}