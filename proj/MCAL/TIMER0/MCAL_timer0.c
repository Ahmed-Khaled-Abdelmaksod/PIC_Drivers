

#include"MCAL_timer0.h"
void (*timer0_handle)(void);
static uint16 preloaded = 0;
static void timer0_clk_set(const timer0_t * _timer0);
static void timer0_prescaler_set(const timer0_t * _timer0);
static void timer0_mode_set(const timer0_t * _timer0);
static void timer0_edge_set(const timer0_t * _timer0);
static void timer0_prescaler_value_set(const timer0_t * _timer0);
static void timer0_preloaded_value_set(const timer0_t * _timer0);

/**
 * 
 * @param _timer0
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */

Std_ReturnType timer0_init(const timer0_t * _timer0)
{
    Std_ReturnType ret = E_OK;
    if(_timer0 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*disable timer0*/
        TIMER0_DISABLE();
        preloaded = _timer0->preload_value;
        /*handle interrupt */
#if(TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        timer0_handle = _timer0->timer0_handler;
        TIMER0_INTERRUPT_CLEAR_FLAG();
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
        INTERRUPT_PRIORITY_ENABLE() ;
        switch(_timer0->priority)
        {
                case HIGH_PRIORITY:
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    TIMER0_INTERRUPT_HIGH_PRIORITY();
                    break;
                case LOW_PRIORITY:
                    INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                    TIMER0_INTERRUPT_LOW_PRIORITY();
                    break;
                        
                default :
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    TIMER0_INTERRUPT_HIGH_PRIORITY();
        }  
#elif
       INTERRUPT_PERIPHERAL_ENABLE();
#endif
        TIMER0_INTERRUPT_ENABLE();
#endif
        timer0_clk_set(_timer0);
        timer0_prescaler_set(_timer0);
        timer0_mode_set(_timer0);
        timer0_edge_set(_timer0);
        timer0_prescaler_value_set(_timer0);
        timer0_preloaded_value_set(_timer0);
        TIMER0_ENABLE();
    }
    
}
/**
 * 
 * @param _timer0
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer0_deinit(const timer0_t * _timer0)
{
    Std_ReturnType ret = E_OK;
    if(_timer0 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER0_DISABLE();
    #if(TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        TIMER0_INTERRUPT_DISABLE();
    #endif
    }
}
/**
 * 
 * @param _timer0
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer0_read_value(const timer0_t * _timer0,uint16 *result)
{
    Std_ReturnType ret = E_OK;
    uint8 l_low = 0;
    uint8 l_high = 0;
    if((_timer0 == NULL) || (result == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_low = TMR0L;
        l_high = TMR0H;
        (*result) = (uint16)(l_low + (l_high << 8));
    }
}
/**
 * 
 * @param _timer0
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType timer0_write_value(const timer0_t * _timer0,uint16 result)
{
    Std_ReturnType ret = E_OK;
    if(_timer0 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        preloaded = result;
        TMR0L = (uint8)result;
        TMR0H = (uint8)(result>>8);
    }
}

void TMR0_ISR(void)
{
    TIMER0_INTERRUPT_CLEAR_FLAG();
    TMR0L = (uint8)(preloaded);
    TMR0H = (uint8)((preloaded)>>8);
    if(timer0_handle)
    {
        timer0_handle();
    }
}


/********************************* static functions ************************************ */

static void timer0_clk_set(const timer0_t * _timer0)
{
    pin_config_t RA4_pin = {
              .direction = INPUT,
              .logic = LOW,
              .pin = PIN4,
              .port = PORTA_INDEX
            };
    switch(_timer0->clk_src)
    {
        
        case TIMER0_EXTERNAL_CLK_ON : 
            gpio_pin_init(&RA4_pin);
            TIMER0_EXTERNAL_CLK();
            break;
        case TIMER0_INTERNAL_CLK_ON :
            TIMER0_INTERNAL_CLK();
            break;
        default :
            TIMER0_INTERNAL_CLK();
            
    }
}


static void timer0_prescaler_set(const timer0_t * _timer0)
{
    switch(_timer0->prescaler_enable)    
    {
        case TIMER0_PRESCALER_ON :
            TIMER0_PRESCALER_ENABLE();
            break;
        case TIMER0_PRESCALER_OFF :
            TIMER0_PRESCALER_DISABLE();
            break;
        default :
            TIMER0_PRESCALER_DISABLE();
    }
    
}


static void timer0_mode_set(const timer0_t * _timer0)
{
    switch(_timer0->timeer0_mode)    
    {
        case TIMER0_8BIT_MODE_ON :
            TIMER0_8BIT_MODE();
            break;
        case TIMER0_16BIT_MODE_ON :
            TIMER0_16BIT_MODE();
            break;
        default :
            TIMER0_8BIT_MODE();
    }
}


static void timer0_edge_set(const timer0_t * _timer0)
{
    switch(_timer0->edge)    
    {
        case TIMER0_FALLING_EDGE :
            TIMER0_EXT_FALLING_EDGE();
            break;
        case TIMER0_RISING_EDGE :
            TIMER0_EXT_RISING_EDGE();
            break;
        default :
            TIMER0_EXT_RISING_EDGE();
    }
}



static void timer0_prescaler_value_set(const timer0_t * _timer0)
{
    TIMER0_PRESCALER_ASSIGN(_timer0->prescaler);
}


static void timer0_preloaded_value_set(const timer0_t * _timer0)
{
    TMR0L = (uint8)(_timer0->preload_value);
    TMR0H = (uint8)((_timer0->preload_value)>>8);
}