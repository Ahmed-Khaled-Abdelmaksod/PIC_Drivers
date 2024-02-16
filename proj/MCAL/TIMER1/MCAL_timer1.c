#include"MCAL_timer1.h"

static void (*timer1_handler)(void) = NULL;
static uint16 preloaded = 0;


/*      STATIC FUNCTIONS(HELPER FUNCTION)               */


static void timer1_mode_set(const timer1_t * _timer1);
static void timer1_syn_set(const timer1_t * _timer1);
static void timer1_osc_set(const timer1_t * _timer1);
static void timer1_rw_set(const timer1_t * _timer1);

/**
 * 
 * @param _timer1
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */

Std_ReturnType timer1_init(const timer1_t * _timer1)
{
    Std_ReturnType ret = E_OK;
    if(_timer1 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER1_DISABLE();
        /***
         interrupt handling
         */
        
        preloaded = _timer1->preload_value;
        /*handle interrupt */
#if(TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        timer1_handler = _timer1->timer1_handler;
        TIMER1_INTERRUPT_CLEAR_FLAG();
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
        INTERRUPT_PRIORITY_ENABLE() ;
        switch(_timer1->priority)
        {
                case HIGH_PRIORITY:
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    TIMER1_INTERRUPT_HIGH_PRIORITY();
                    break;
                case LOW_PRIORITY:
                    INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                    TIMER1_INTERRUPT_LOW_PRIORITY();
                    break;
                        
                default :
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    TIMER1_INTERRUPT_HIGH_PRIORITY();
        }  
#elif
       INTERRUPT_PERIPHERAL_ENABLE();
#endif
        TIMER1_INTERRUPT_ENABLE();
#endif
        
        TMR1H = (uint8)(_timer1->preload_value>>8);
        TMR1L = (uint8)(_timer1->preload_value);
        TIMER1_PRESCALER_VALUE(_timer1->prescaler);
        timer1_mode_set(_timer1);
        timer1_syn_set(_timer1);
        timer1_osc_set(_timer1);
        timer1_rw_set(_timer1);
        TIMER1_ENABLE();
    }
    return ret;
}
/**
 * 
 * @param _timer1
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer1_deinit(const timer1_t * _timer1)
{
    Std_ReturnType ret = E_OK;
    if(_timer1 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER1_DISABLE();
    #if(TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        TIMER1_INTERRUPT_DISABLE();
    #endif
    }
    return ret;
}
/**
 * 
 * @param _timer1
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer1_read_value(const timer1_t * _timer1,uint16 *result)
{
    Std_ReturnType ret = E_OK;
    uint8 l_low = 0;
    uint8 l_high = 0;
    if((_timer1 == NULL) || (result ==  NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        l_low = TMR1L;
        l_high = TMR1H;
        (*result) = (uint16)(l_low + (l_high << 8));
    }
    return ret;
}
/**
 * 
 * @param _timer1
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer1_write_value(const timer1_t * _timer1,uint16 result)
{
    Std_ReturnType ret = E_OK;
    if(_timer1 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        preloaded = result;
        TMR1L = (uint8)result;
        TMR1H = (uint8)(result>>8);
    }
    return ret;
}

/*____________________________ ISR ____________________________*/

void TMR1_ISR(void)
{
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TMR1L = (uint8)(preloaded);
    TMR1H = (uint8)((preloaded)>>8);
    if(timer1_handler)
    {
        timer1_handler();
    }
}



/**************************************************************************/


static void timer1_mode_set(const timer1_t * _timer1)
{
    switch(_timer1->timer1_mode)
    {
        case TIMER1_COUNTER_MODE: 
            TIMER1_COUNTER_MODE_ENABLE();
            break;
        case TIMER1_TIMER_MODE:
            TIMER1_TIMER_MODE_ENABLE();
            break;
        default :
            TIMER1_TIMER_MODE_ENABLE();
    }
}



static void timer1_syn_set(const timer1_t * _timer1)
{
    switch(_timer1->external_syn_enable)
    {
        case TIMER1_SYN_EXTERNAL_CLK:
            TIMER1_SYN_EXTERNAL_CLK_ENABLE();
            break;
            
        case TIMER1_ASYN_EXTERNAL_CLK:
            TIMER1_SYN_EXTERNAL_CLK_DISABLE();
            
            break;
        default:
            TIMER1_SYN_EXTERNAL_CLK_ENABLE();
    }
}





static void timer1_osc_set(const timer1_t * _timer1)
{
    switch(_timer1->timer1_osc)
    {
        case TIMER1_OSC_ON:
            TIMER1_OSC_ENABLE();
            break;
            
        case TIMER1_OSC_OFF: 
            TIMER1_OSC_DISABLE();
            break;
        default : 
            TIMER1_OSC_DISABLE();
    }
}




static void timer1_rw_set(const timer1_t * _timer1)
{
    switch(_timer1->timer1_rw_mode)
    {
        case TIMER1_RW_8BIT_MODE:
            TIMER1_RW_8BIT_MODE_ENABLE();
            break;
            
        case TIMER1_RW_16BIT_MODE: 
            TIMER1_RW_16BIT_MODE_ENABLE();
            break;
        default : 
            TIMER1_RW_16BIT_MODE_ENABLE();
    }
}