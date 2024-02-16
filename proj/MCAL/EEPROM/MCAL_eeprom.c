#include"MCAL_eeprom.h"

/**
 * 
 * @param address
 * @param address
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType EEPROM_write(uint16 address,uint8 data)
{
    Std_ReturnType ret = E_OK;
    uint8 interrupt_state = INTCONbits.GIE;
    EEADR = (uint8)(address & 0xFF);
    EEADRH = (uint8)((address>>8)&0X03);
    EEDATA = data;
    ACCESS_DATA_EEPROM_MEMORY();
    SELECT_FLASH_EEPROM_MEMORYS();
    EEPROM_WRITE_ENABLE();
    INTERRUPT_GLOBAL_INTERRUPT_DISABLE();
    
    EECON2 = 0X55;
    EECON2 = 0XAA;
    EECON1bits.WR = 1;
    while(EECON1bits.WR);
    EEPROM_WRITE_DISABLE();
    INTCONbits.GIE = interrupt_state;
    return ret;
}
/**
 * 
 * @param address
 * @param address
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission
 */
Std_ReturnType EEPROM_read(uint16 address,uint8 *data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == data)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EEADR = (uint8)(address & 0xFF);
        EEADRH = (uint8)((address>>8)&0X03);
        ACCESS_DATA_EEPROM_MEMORY();
        SELECT_FLASH_EEPROM_MEMORYS();
        EECON1bits.RD = 1;
        NOP();
        (*data) = EEDATA; 
        ret = E_OK;
    }
}
