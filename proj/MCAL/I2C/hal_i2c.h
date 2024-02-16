/* 
 * File:   hal_i2c.h
 * Author: Ahmed Khaled
 *
 * Created on 12 ??????, 2024, 09:02 ?
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H


/*================ INCLUDES ================*/
#include"../INTERRUPT/MCAL_interrupt_config.h"
#include"../INTERRUPT/MCAL_internal_interrupt.h"
#include"pic18f4620.h"
#include"../MCAL_std_types.h"
#include"../GPIO/MCAL_gpio.h"

/*================ DEFINITIONS ================*/

/**************** Slew Rate Control bit ****************/
/* Slew rate control disabled for Standard Speed mode (100 kHz) */
#define I2C_SLEW_RATE_STANDARD_SPEED_MODE       1
/* Slew rate control enabled for High-Speed mode (400 kHz) */
#define I2C_SLEW_RATE_HIGH_SPEED_MODE           0 

/**************** CKE: SMBus Select bit ****************/
/* Enable SMBus specific inputs */
#define I2C_ENABLE_SMBUS_SPECIFIC_INPUTS        1
/*Disable SMBus specific inputs*/
#define I2C_DISABLE_SMBUS_SPECIFIC_INPUTS       0 
/**************** D/A: Data/Address bit *****************/

#define I2C_LAST_BYTE_IS_DATA                   1
#define I2C_LAST_BYTE_IS_ADDRESS                0

#define I2C_START_BIT_DETECTED                  1
#define I2C_START_BIT_NOT_DETECTED              0


#define I2C_END_BIT_DETECTED                    1
#define I2C_END_BIT_NOT_DETECTED                0

/*================ TYPES DEFINITIONS ================*/

typedef struct {
    uint8 slew_rate:1;
    
}i2c_t;

/*================ MACRO FUNCTIONS ================*/

#define I2C_SLEW_RATE_STANDARD_SPEED_MODE_CFG()                     (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_HIGH_SPEED_MODE_CFG()                         (SSPSTATbits.SMP = 0)

#define I2C_SMBUS_ENABLE()                                          (SSPSTATbits.CKE = 1)
#define I2C_SMBUS_DISABLE()                                         (SSPSTATbits.CKE = 0)
// DATA OR ADDRESS
#define I2C_READ_LAST_BYTE_STATE()                                  (SSPSTATbits.D)

#define I2C_READ_START_BIT_STATE()                                  (SSPSTATbits.S)
#define I2C_READ_END_BIT_STATE()                                    (SSPSTATbits.E)


/*================ SW INTERFACES ================*/
Std_ReturnType i2c_init(i2c_t *obj_i2c);
Std_ReturnType i2c_deInit(i2c_t *obj_i2c);





#endif	/* HAL_I2C_H */

