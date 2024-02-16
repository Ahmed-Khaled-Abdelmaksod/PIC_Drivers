/* 
 * File:   MCAL_adc.h
 * Author: Ahmed Khaled
 *
 * Created on 12 ??????, 2023, 05:56 ?
 */

#ifndef MCAL_ADC_H
#define	MCAL_ADC_H

/*================ INCLUDES ================*/
#include"../MCAL_std_types.h"
#include"../GPIO/MCAL_gpio.h"
#include"pic18f4620.h"
#include"../INTERRUPT/MCAL_interrupt_config.h"
#include"../INTERRUPT/MCAL_internal_interrupt.h"
/*================ DEFINITIONS ================*/
#define ADC_CONVERSATION_DONE           0U
#define ADC_CONVERSATION_IN_PROGRESS    1U

/*********** ANALOG ENABLES ***********/
#define ADC_ALL_CHANNELS_DIGITAL        0x0F
#define ADC_ANO_ENABLE                  0x0E
#define ADC_AN1_ENABLE                  0x0D
#define ADC_AN2_ENABLE                  0x0C
#define ADC_AN3_ENABLE                  0x0B
#define ADC_AN4_ENABLE                  0x0A
#define ADC_AN5_ENABLE                  0x09
#define ADC_AN6_ENABLE                  0x08
#define ADC_AN7_ENABLE                  0x07
#define ADC_AN8_ENABLE                  0x06
#define ADC_AN9_ENABLE                  0x05
#define ADC_AN10_ENABLE                 0x04
#define ADC_AN11_ENABLE                 0x03
#define ADC_AN12_ENABLE                 0x02
#define ADC_ALL_ANALOG                  0x01


#define ADC_RIGHT_JUSTIFIED     1U
#define ADC_LEFT_JUSTIFIED      0U

#define ADC_VREF_DEAFULT    0U
#define ADC_VREF_EXTERNAL   1U

/*================ TYPES DEFINITIONS ================*/
/***********************************************************
 TYPE to select the input channel to the ADC
 ***************************************************************/
typedef enum {
    ADC_CHANNEL_AN0 = 0 ,
    ADC_CHANNEL_AN1 ,
    ADC_CHANNEL_AN2 ,
    ADC_CHANNEL_AN3 ,
    ADC_CHANNEL_AN4 ,
    ADC_CHANNEL_AN5 ,
    ADC_CHANNEL_AN6 ,
    ADC_CHANNEL_AN7 ,
    ADC_CHANNEL_AN8 ,
    ADC_CHANNEL_AN9 ,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,
}adc_channel_selector_t;
/**
 * NOTE : TAD MIN = 0.7 US MAX 25US  VREF >3
 */
typedef enum {
    ADC_ACQUISITION_TIME_0TAD = 0,
    ADC_ACQUISITION_TIME_2TAD ,
    ADC_ACQUISITION_TIME_4TAD ,
    ADC_ACQUISITION_TIME_6TAD ,
    ADC_ACQUISITION_TIME_8TAD ,
    ADC_ACQUISITION_TIME_12TAD ,
    ADC_ACQUISITION_TIME_16TAD ,
    ADC_ACQUISITION_TIME_20TAD ,       
}adc_acquisition_time_selector_t;

typedef enum {
    ADC_CLK_FOSC_DIV_2 = 0,
    ADC_CLK_FOSC_DIV_8,
    ADC_CLK_FOSC_DIV_32,
    ADC_CLK_FOSC_RC_OSCILLATOR,
    ADC_CLK_FOSC_DIV_4,
    ADC_CLK_FOSC_DIV_16,
    ADC_CLK_FOSC_DIV_64,   
}adc_clk_selector_t;

typedef struct {
#if (ADC_INTERRUPT_FEATURE_ENABLE  == INTERRUPT_FEATURE_ENABLE)
    void (*adc_handler)(void);
    #if (INTERRUPT_FEATURE_PRIORITY_ENABLE  == INTERRUPT_FEATURE_ENABLE)
        uint8 priority;
    #endif
#endif
    adc_channel_selector_t adc_channel;
    adc_acquisition_time_selector_t adc_acq_time;
    adc_clk_selector_t adc_clk;
    uint8 adc_justified ;
    uint8 vref_src ;
}adc_t;
/*================ MACRO FUNCTIONS ================*/
#define ADC_MODULE_ENABLE()         (ADCON0bits.ADON = 1)
#define ADC_MODULE_DISABLE()        (ADCON0bits.ADON = 0)

#define ADC_START_CONVERSTION()     (ADCON0bits.GO_nDONE = 1)
#define ADC_GET_CONVERSTION_STATE() (ADCON0bits.GO_nDONE)

#define ADC_DEFAULT_REFERENCE()   (ADCON1bits.VCFG0 = 0) ; \
                                  (ADCON1bits.VCFG1 = 0) ; 

#define ADC_EXTERNAL_REFERENCE()  (ADCON1bits.VCFG0 = 1) ; \
                                  (ADCON1bits.VCFG1 = 1) ; 
                                  
#define ADC_CHANNEL_SELECTOR(_CONFIG)  (ADCON0bits.CHS = _CONFIG)
#define ADC_CHANNEL_ANALOG_ENABLE(_CONFIG)  (ADCON1bits.PCFG = _CONFIG)
#define ADC_CLK_SRC(_CONFIG)  (ADCON2bits.ADCS = _CONFIG)
#define ADC_AQU_TIME_SELECT(_CONFIG)  (ADCON2bits.ACQT = _CONFIG)

#define ADC_RIGHT_JUSTIFIED_SET() (ADCON2bits.ADFM = 1)
#define ADC_LEFT_JUSTIFIED_SET()  (ADCON2bits.ADFM = 0)
/*================ SW INTERFACES ================*/
/**
 * 
 * @param _adc
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_init(const adc_t *_adc);
/**
 * 
 * @param _adc
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_deinit(const adc_t *_adc);
/**
 * 
 * @param _adc
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_start_conversion(const adc_t *_adc);
/**
 * 
 * @param _adc
 * @param channel
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_select_channel(const adc_t *_adc,adc_channel_selector_t channel);
/**
 * 
 * @param _adc
 * @param state
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_is_conversion_done(const adc_t *_adc,uint8 *state);
/**
 * 
 * 
 * @param _adc
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_get_result(const adc_t *_adc,uint16 *result);
/**
 * 
 * @param _adc
 * @param result
 * @param channel
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_get_result_blocking(const adc_t *_adc,uint16 *result,adc_channel_selector_t channel);
/**
 * 
 * @param _adc
 * @param result
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType ADC_start_conversion_interrupt(const adc_t *_adc,adc_channel_selector_t channel);
#endif	/* MCAL_ADC_H */

