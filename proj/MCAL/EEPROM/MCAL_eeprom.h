/* 
 * File:   MCAL_eeprom.h
 * Author: Ahmed Khaled
 *
 * Created on 09 ??????, 2023, 07:30 ?
 */

#ifndef MCAL_EEPROM_H
#define	MCAL_EEPROM_H

/*================ INCLUDES ================*/
#include"../MCAL_std_types.h"
#include"pic18f4620.h"
#include"../INTERRUPT/MCAL_external_interrupt.h"

/*================ DEFINITIONS ================*/

/*================ MACRO FUNCTIONS ================*/
#define ACCESS_DATA_EEPROM_MEMORY()         (EECON1bits.EEPGD = 0)
#define ACCESS_FLASH_MEMORY()               (EECON1bits.EEPGD = 1)

#define SELECT_CONFIG_BITS()                (EECON1bits.CFGS = 1)
#define SELECT_FLASH_EEPROM_MEMORYS()       (EECON1bits.CFGS = 0)
#define EEPROM_WRITE_ENABLE()               (EECON1bits.WREN = 1)
#define EEPROM_WRITE_DISABLE()              (EECON1bits.WREN = 0)
/*================ SW INTERFACES ================*/
/**
 * 
 * @param address
 * @param address
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType EEPROM_write(uint16 address,uint8 data);
/**
 * 
 * @param address
 * @param address
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType EEPROM_read(uint16 address,uint8 *data);


#endif	/* MCAL_EEPROM_H */

