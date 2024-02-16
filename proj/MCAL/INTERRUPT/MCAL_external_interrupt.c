#include"MCAL_external_interrupt.h"
/*================== Helper Functions =====================*/
static uint8 r4_flag = 0;
static uint8 r5_flag = 0;
static uint8 r6_flag = 0;
static uint8 r7_flag = 0;
/*================== ptr to function ptrs =====================*/
static ptr_ISR INT0_PTR = NULL;
static ptr_ISR INT1_PTR = NULL;
static ptr_ISR INT2_PTR = NULL;


static ptr_ISR R4_HIGH_TO_LOW_PTR = NULL;
static ptr_ISR R4_LOW_TO_HIGH_PTR = NULL;
static ptr_ISR R5_HIGH_TO_LOW_PTR = NULL;
static ptr_ISR R5_LOW_TO_HIGH_PTR = NULL;
static ptr_ISR R6_HIGH_TO_LOW_PTR = NULL;
static ptr_ISR R6_LOW_TO_HIGH_PTR = NULL;
static ptr_ISR R7_HIGH_TO_LOW_PTR = NULL;
static ptr_ISR R7_LOW_TO_HIGH_PTR = NULL;
/*================== helper functions for intx=====================*/
static void interrupt_INTX_interrupt_enable(const intx_interrupt_t *intx);
static void interrupt_INTX_interrupt_disable(const intx_interrupt_t *intx);
static void interrupt_INTX_priority_init(const intx_interrupt_t *intx);
static void interrupt_INTX_edge_init(const intx_interrupt_t *intx);
static void interrupt_INTX_pin_init(const intx_interrupt_t *intx);
static void interrupt_INTX_clear_flag(const intx_interrupt_t *intx);
static void interrupt_int0_set_handler(ptr_ISR ptr);
static void interrupt_int1_set_handler(ptr_ISR ptr);
static void interrupt_int2_set_handler(ptr_ISR ptr);
static void interrupt_intx_set_handler(const intx_interrupt_t *intx);

/*================== helper functions for PORTB =====================*/
static void interrupt_rx_interrupt_enable();
static void interrupt_rx_set_high_to_low_handler(const rx_interrupt_t *rx_obj);

static void interrupt_r4_set_high_to_low_handler(ptr_ISR ptr);
static void interrupt_r5_set_high_to_low_handler(ptr_ISR ptr);
static void interrupt_r6_set_high_to_low_handler(ptr_ISR ptr);
static void interrupt_r7_set_high_to_low_handler(ptr_ISR ptr);

static void interrupt_rx_set_low_to_high_handler(const rx_interrupt_t *rx_obj);


static void interrupt_r4_set_low_to_high_handler(ptr_ISR ptr);
static void interrupt_r5_set_low_to_high_handler(ptr_ISR ptr);
static void interrupt_r6_set_low_to_high_handler(ptr_ISR ptr);
static void interrupt_r7_set_low_to_high_handler(ptr_ISR ptr);

static void interrupt_rx_set_priority(const rx_interrupt_t *rx_obj);
static void interrupt_rx_set_pin(const rx_interrupt_t *rx_obj);
/**
 * 
 * @param intx
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType intx_init(const intx_interrupt_t *intx)
{
    Std_ReturnType ret = E_OK;
    if(intx == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
#if (INTERRUPT_FEATURE_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE)
        INTERRUPT_PRIORITY_ENABLE();
#endif
      
        interrupt_INTX_interrupt_disable(intx);
        interrupt_INTX_clear_flag(intx);
        interrupt_INTX_edge_init(intx);
        interrupt_INTX_pin_init(intx);
        #if (INTERRUPT_FEATURE_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE)
            interrupt_INTX_priority_init(intx);
        #endif
        interrupt_intx_set_handler(intx);
        interrupt_INTX_interrupt_enable(intx);
        
    }
    return ret;
}
/**
 * 
 * @param intx
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType intx_deinit(const intx_interrupt_t *intx)
{
    Std_ReturnType ret = E_OK;
    if(intx == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        interrupt_INTX_interrupt_disable(intx);
    }
    return ret;
}


/**
 * 
 * @param intx
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType rx_init(const rx_interrupt_t *rx)
{
    Std_ReturnType ret = E_OK;
    if(NULL == rx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        #if (INTERRUPT_FEATURE_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE)
            INTERRUPT_PRIORITY_ENABLE();
        #endif
        RX_INTERRUPT_ON_CHANGE_PORTB_DISABLE(); 
        RX_INTERRUPT_ON_CHANGE_CLEAR_FLAG();
        interrupt_rx_set_high_to_low_handler(rx);
        interrupt_rx_set_low_to_high_handler(rx);
        #if (INTERRUPT_FEATURE_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE)
             interrupt_rx_set_priority(rx);
        #endif
       
        interrupt_rx_set_pin(rx);
        interrupt_rx_interrupt_enable();
    }
    
}

/**
 * 
 * @param intx
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType rx_deinit(const rx_interrupt_t *rx)
{
    Std_ReturnType ret = E_OK;
    if(NULL == rx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        RX_INTERRUPT_ON_CHANGE_PORTB_DISABLE();
    }
}

/************************* ISRs *************************************/
void INT0_ISR()
{
    EXT_INT0_CLEAR_FLAG();
    if(INT0_PTR != NULL)
    {
        INT0_PTR();
    }
}

void INT1_ISR()
{
    EXT_INT1_CLEAR_FLAG();
    if(INT1_PTR != NULL)
    {
        INT1_PTR();
    }
}

void INT2_ISR()
{
    
    EXT_INT2_CLEAR_FLAG();
    if(INT2_PTR != NULL)
    {
        INT2_PTR();
    }
}

void RB4_HIGH_TO_LOW_ISR()
{
    RX_INTERRUPT_ON_CHANGE_CLEAR_FLAG();
    if(R4_HIGH_TO_LOW_PTR != NULL)
    {
        R4_HIGH_TO_LOW_PTR();
    }
}


void RB5_HIGH_TO_LOW_ISR()
{
    RX_INTERRUPT_ON_CHANGE_CLEAR_FLAG();
    if(R5_HIGH_TO_LOW_PTR != NULL)
    {
        R5_HIGH_TO_LOW_PTR();
    }
}
void RB6_HIGH_TO_LOW_ISR()
{
    RX_INTERRUPT_ON_CHANGE_CLEAR_FLAG();
    if(R6_HIGH_TO_LOW_PTR != NULL)
    {
        R6_HIGH_TO_LOW_PTR();
    }
}
void RB7_HIGH_TO_LOW_ISR()
{
    RX_INTERRUPT_ON_CHANGE_CLEAR_FLAG();
    if(R7_HIGH_TO_LOW_PTR != NULL)
    {
        R7_HIGH_TO_LOW_PTR();
    }
}

void RB4_LOW_TO_HIGH_ISR()
{
    RX_INTERRUPT_ON_CHANGE_CLEAR_FLAG();
    if(R4_LOW_TO_HIGH_PTR != NULL)
    {
        R4_LOW_TO_HIGH_PTR();
    }
}
void RB5_LOW_TO_HIGH_ISR()
{
    RX_INTERRUPT_ON_CHANGE_CLEAR_FLAG();
    if(R5_LOW_TO_HIGH_PTR != NULL)
    {
        R5_LOW_TO_HIGH_PTR();
    }
}
void RB6_LOW_TO_HIGH_ISR()
{
    RX_INTERRUPT_ON_CHANGE_CLEAR_FLAG();
    if(R6_LOW_TO_HIGH_PTR != NULL)
    {
        R6_LOW_TO_HIGH_PTR();
    }
}
void RB7_LOW_TO_HIGH_ISR()
{
    RX_INTERRUPT_ON_CHANGE_CLEAR_FLAG();
    if(R7_LOW_TO_HIGH_PTR != NULL)
    {
        R7_LOW_TO_HIGH_PTR();
    }
}

/************************************************************/
/* implementation of static functions*/
static void interrupt_INTX_interrupt_enable(const intx_interrupt_t *intx)
{
    switch(intx->source)
    {
        case SRC_INT0 :
            #if (INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
            #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_ENABLE();
            #endif
            EXT_INT0_INTERRUPT_ENABLE();
            break;
        case SRC_INT1:
            #if (INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
                if(intx->priority == INTX_PRIORITY_HIGH)
                {  
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                }
                else
                {
                    INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                }
            #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_ENABLE();
            #endif
            EXT_INT1_INTERRUPT_ENABLE();
            break;
        case SRC_INT2 :
            #if (INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
                if(intx->priority == INTX_PRIORITY_HIGH)
                {  
                    INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                }
                else
                {
                    INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                }
            #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_ENABLE();
            #endif
            EXT_INT2_INTERRUPT_ENABLE();
            break;
        
    }
}
static void interrupt_INTX_interrupt_disable(const intx_interrupt_t *intx)
{
    switch(intx->source)
    {
        case SRC_INT0 :
            EXT_INT0_INTERRUPT_DISABLE();
            break;
        case SRC_INT1 :
            EXT_INT1_INTERRUPT_DISABLE();
            break;
        case SRC_INT2:
            EXT_INT2_INTERRUPT_DISABLE();
            break;
    }
}
#if (INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
static void interrupt_INTX_priority_init(const intx_interrupt_t *intx)
{
    
    switch(intx->source)
    {
        case SRC_INT1 :
            if(intx->priority == INTX_PRIORITY_LOW)
            {
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                EXT_INT1_LOW_PRIORITY();
            }
                else if (intx->priority == INTX_PRIORITY_HIGH)
            {
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                EXT_INT1_HIGH_PRIORITY();
            }
            else {/* NOTHING */}
            break;
        case SRC_INT2:
            if(intx->priority == INTX_PRIORITY_LOW)
            {
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                EXT_INT2_LOW_PRIORITY();
            }
                else if (intx->priority == INTX_PRIORITY_HIGH)
            {
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                EXT_INT2_HIGH_PRIORITY();
            }
            else {/* NOTHING */}
            break;
    }
}
#endif
static void interrupt_INTX_edge_init(const intx_interrupt_t *intx)
{
    switch(intx->source)
    {
        case SRC_INT0 :
            if(EDGE_FALLING == (intx->edge))
            {
                EXT_INT0_FALLING_EDGE();
            }
            else if(EDGE_RISING == (intx->edge))
            {
                EXT_INT0_RISING_EDGE();
            }
            else{/*NOTHING*/}
             
            break;
        case SRC_INT1 :
            if(EDGE_FALLING == (intx->edge))
            {
                EXT_INT1_FALLING_EDGE();
            }
            else if(EDGE_RISING == (intx->edge))
            {
                EXT_INT1_RISING_EDGE();
            }
            else{/*NOTHING*/}
             
            break;
        case SRC_INT2:
            if(EDGE_FALLING == (intx->edge))
            {
                EXT_INT2_FALLING_EDGE();
            }
            else if(EDGE_RISING == (intx->edge))
            {
                EXT_INT2_RISING_EDGE();
            }
            else{/*NOTHING*/}
             
            break;
    }
}
static void interrupt_INTX_pin_init(const intx_interrupt_t *intx)
{
    gpio_pin_direction_init(&(intx->pin));
}
static void interrupt_INTX_clear_flag(const intx_interrupt_t *intx)
{
    switch(intx->source)
    {
        case SRC_INT0 :
            EXT_INT0_CLEAR_FLAG();
            break;
        case SRC_INT1 :
            EXT_INT1_CLEAR_FLAG();
            break;
        case SRC_INT2:
            EXT_INT2_CLEAR_FLAG();
            break;
    }
}


static void interrupt_int0_set_handler(ptr_ISR ptr)
{
    INT0_PTR = ptr;
}
static void interrupt_int1_set_handler(ptr_ISR ptr)
{
    INT1_PTR = ptr;
}
static void interrupt_int2_set_handler(ptr_ISR ptr)
{
    INT2_PTR = ptr;
}
static void interrupt_intx_set_handler(const intx_interrupt_t *intx)
{
    switch(intx->source)
    {
        case SRC_INT0 :
            interrupt_int0_set_handler(intx->ptr_ISR);
            break;
        case SRC_INT1 :
            interrupt_int1_set_handler(intx->ptr_ISR);
            break;
        case SRC_INT2:
            interrupt_int2_set_handler(intx->ptr_ISR);
            break;
    }
}



/************** static functions for portb on change ************************/

static void interrupt_rx_set_high_to_low_handler(const rx_interrupt_t *rx_obj)
{
    switch(rx_obj->pin.pin)
    {
        case PIN4 :
            interrupt_r4_set_high_to_low_handler(rx_obj->ptr_to_isr_high_to_low);
            break;
        case PIN5 :
            interrupt_r5_set_high_to_low_handler(rx_obj->ptr_to_isr_high_to_low);
            break;
        case PIN6:
            interrupt_r6_set_high_to_low_handler(rx_obj->ptr_to_isr_high_to_low);
            break;
        case PIN7 :
            interrupt_r7_set_high_to_low_handler(rx_obj->ptr_to_isr_high_to_low);
            break;
    }
}

static void interrupt_r4_set_high_to_low_handler(ptr_ISR ptr)
{
    R4_HIGH_TO_LOW_PTR = ptr;
}
static void interrupt_r5_set_high_to_low_handler(ptr_ISR ptr)
{
    R5_HIGH_TO_LOW_PTR = ptr;
}
static void interrupt_r6_set_high_to_low_handler(ptr_ISR ptr)
{
    R6_HIGH_TO_LOW_PTR = ptr;
}
static void interrupt_r7_set_high_to_low_handler(ptr_ISR ptr)
{
    R7_HIGH_TO_LOW_PTR = ptr;
}

static void interrupt_rx_set_low_to_high_handler(const rx_interrupt_t *rx_obj)
{
    switch(rx_obj->pin.pin)
    {
        case PIN4 :
            interrupt_r4_set_low_to_high_handler(rx_obj->ptr_to_isr_high_to_low);
            break;
        case PIN5 :
            interrupt_r5_set_low_to_high_handler(rx_obj->ptr_to_isr_high_to_low);
            break;
        case PIN6:
            interrupt_r6_set_low_to_high_handler(rx_obj->ptr_to_isr_high_to_low);
            break;
        case PIN7 :
            interrupt_r7_set_low_to_high_handler(rx_obj->ptr_to_isr_high_to_low);
            break;
    }
}

static void interrupt_r4_set_low_to_high_handler(ptr_ISR ptr)
{
    R4_LOW_TO_HIGH_PTR = ptr;
}
static void interrupt_r5_set_low_to_high_handler(ptr_ISR ptr)
{
    R5_LOW_TO_HIGH_PTR = ptr;
}
static void interrupt_r6_set_low_to_high_handler(ptr_ISR ptr)
{
    R6_LOW_TO_HIGH_PTR = ptr;
}
static void interrupt_r7_set_low_to_high_handler(ptr_ISR ptr)
{
    R7_LOW_TO_HIGH_PTR = ptr;
}





#if (INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
static void interrupt_rx_set_priority(const rx_interrupt_t *rx_obj)
{
    if(rx_obj->priority == INTX_PRIORITY_HIGH)
    {
        INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
        RX_INTERRUPT_ON_CHANGE_HIGH_PRIORITY();
    }
    else if(rx_obj->priority == INTX_PRIORITY_LOW)
    {
        INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
        RX_INTERRUPT_ON_CHANGE_LOW_PRIORITY();
    }
}
 #endif
static void interrupt_rx_set_pin(const rx_interrupt_t *rx_obj)
{
    gpio_pin_direction_init(&(rx_obj->pin));
}
static void interrupt_rx_interrupt_enable()
{
    #if (INTERRUPT_FEATURE_PRIORITY_ENABLE == INTERRUPT_FEATURE_ENABLE)
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
    #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_ENABLE();
    #endif
    RX_INTERRUPT_ON_CHANGE_PORTB_ENABLE();
}