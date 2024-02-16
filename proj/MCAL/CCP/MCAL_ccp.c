#include"MCAL_ccp.h"

void (*ccp1_handle)(void) = NULL;
void (*ccp2_handle)(void) = NULL;

void static ccp_clk_set(const ccp_t * ccp);

void static ccp_interrupt_set(const ccp_t * ccp);
/*
// add comp & pwm 
typedef struct
{






}ccp_t;
*/

Std_ReturnType ccp_init(const ccp_t *ccp)
{
    Std_ReturnType ret = E_OK;
    if(ccp == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
         switch(ccp->ccp_selected)
        {
            case CCP1_MODULE:
                CCP1_SET_MODE(CCP_DISABLE_COMPARE_PWM_CAPTURE);
                break;
            case CCP2_MODULE:
                CCP2_SET_MODE(CCP_DISABLE_COMPARE_PWM_CAPTURE);
                break;
                
            default : 
               ret = E_NOT_OK; 
        }
        
        ccp_clk_set(ccp);
        gpio_pin_init(&(ccp->ccp_pin));
        ccp_interrupt_set(ccp);

        switch(ccp->ccp_selected)
        {
            case CCP1_MODULE:
                CCP1_SET_MODE(ccp->inner_mode_selection);
                break;
            case CCP2_MODULE:
                CCP2_SET_MODE(ccp->inner_mode_selection);
                break;
                
            default : 
               ret = E_NOT_OK; 
        }
    }
    return ret;
}
Std_ReturnType ccp_deinit(const ccp_t *ccp)
{
    Std_ReturnType ret = E_OK;
    if(ccp == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
         switch(ccp->ccp_selected)
        {
            case CCP1_MODULE:
                CCP1_SET_MODE(CCP_DISABLE_COMPARE_PWM_CAPTURE);
                break;
            case CCP2_MODULE:
                CCP2_SET_MODE(CCP_DISABLE_COMPARE_PWM_CAPTURE);
                break;
                
            default : 
               ret = E_NOT_OK; 
        }
         
#if(CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
         CCP2_INTERRUPT_DISABLE();
#endif
                  
#if(CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
         CCP1_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}

#if((CCP1_MODE == CCP_CAPTURE_ON) ||(CCP2_MODE == CCP_CAPTURE_ON))
Std_ReturnType ccp_is_captured_done(const ccp_t *ccp,uint8 *capture_state)
{
    Std_ReturnType ret = E_OK;
    if((ccp == NULL) || (capture_state == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        switch(ccp->ccp_selected)
        {
            case CCP1_MODULE:
                if(CCP_CAPTURE_READY == PIR1bits.CCP1IF)
                {
                    *capture_state = CCP_CAPTURE_READY;
                    CCP1_INTERRUPT_CLEAR_FLAG();
                }
                else
                {
                    *capture_state = CCP_CAPTURE_NOT_READY;
                }
                break;
                
                
            case CCP2_MODULE:
                if(CCP_CAPTURE_READY == PIR2bits.CCP2IF)
                {
                    *capture_state = CCP_CAPTURE_READY;
                    CCP2_INTERRUPT_CLEAR_FLAG();
                }
                else
                {
                    *capture_state = CCP_CAPTURE_NOT_READY;
                }
                break;
                
               
                
            default : 
               ret = E_NOT_OK; 
        }
    }
    return ret;
}


Std_ReturnType ccp_read_captured_value(const ccp_t *ccp,uint16 *capture_value)
{
    Std_ReturnType ret = E_OK;
    reg_t var = {0,0};
    if((ccp == NULL) || (capture_value == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(ccp->ccp_selected)
        {
            case CCP1_MODULE:
                var.low = CCPR1L;
                var.high = CCPR1H;
                *capture_value = var.value;
                break;
            case CCP2_MODULE:
                var.low = CCPR2L;
                var.high = CCPR2H;
                *capture_value = var.value;
                break;
                
            default : 
               ret = E_NOT_OK; 
        }
        
    }
    return ret;
}
#endif

/******************** ISRs ************************/
void CCP1_ISR(void)
{
    CCP1_INTERRUPT_CLEAR_FLAG();
    if(ccp1_handle)
    {
        ccp1_handle();
    }
}
void CCP2_ISR(void)
{
    CCP2_INTERRUPT_CLEAR_FLAG();
    if(ccp2_handle)
    {
        ccp2_handle();
    }
}




/*_______________________________ statics functions _______________________________*/


void static ccp_clk_set(const ccp_t * ccp)
{
    switch(ccp->ccp_clk_src)
    {
        case CCPX_TIMER1_CLK_SRC: 
            CCPS_TIMER1_CLK_SRC();
            break;
        case CCP1_TIMER1_SRC_CCP2_TIMER3_SRC:
            CCP1_TIMER1_CLK_SRC_CCP2_TIMER3_CLK_SRC();
            break;
        case CCPX_TIMER3_CLK_SRC:
            CCPS_TIMER3_CLK_SRC();
            break;
        default :
            CCPS_TIMER1_CLK_SRC(); 
    }
}



void static ccp_interrupt_set(const ccp_t * ccp)
{
    if(ccp->ccp_selected == CCP1_MODULE)
    {
        
#if(CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        CCP1_INTERRUPT_DISABLE();
        ccp1_handle = ccp->ccp1_handler;
        CCP1_INTERRUPT_CLEAR_FLAG();
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
        INTERRUPT_PRIORITY_ENABLE() ;
        switch(ccp->ccp1_priority)
        {
                case HIGH_PRIORITY:
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    CCP1_INTERRUPT_HIGH_PRIORITY();
                    break;
                case LOW_PRIORITY:
                    INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                    CCP1_INTERRUPT_LOW_PRIORITY();
                    break;
                        
                default :
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    CCP1_INTERRUPT_HIGH_PRIORITY();
        }  
#elif
       INTERRUPT_PERIPHERAL_ENABLE();
#endif
        CCP1_INTERRUPT_ENABLE();
#endif
    }
        
    if(ccp->ccp_selected == CCP2_MODULE)
    {     
        
#if(CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE)
        CCP1_INTERRUPT_DISABLE();
        ccp2_handle = ccp->ccp2_handler;
        CCP2_INTERRUPT_CLEAR_FLAG();
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
#if(INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
        INTERRUPT_PRIORITY_ENABLE() ;
        switch(ccp->ccp2_priority)
        {
                case HIGH_PRIORITY:
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    CCP2_INTERRUPT_HIGH_PRIORITY();
                    break;
                case LOW_PRIORITY:
                    INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                    CCP2_INTERRUPT_LOW_PRIORITY();
                    break;
                        
                default :
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                    CCP2_INTERRUPT_HIGH_PRIORITY();
        }  
#elif
       INTERRUPT_PERIPHERAL_ENABLE();
#endif
        CCP2_INTERRUPT_ENABLE();
#endif
    }
}