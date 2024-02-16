#include"ECU_keypad.h"
// this array should be switched if the keypad changed
uint8 values[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
    {'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'#','0','=','+'}
};
/**
 * 
 * @param keypad
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType keypad_init(keypad_t *keypad)
{
    uint8 counter = 0;
    Std_ReturnType ret = E_NOT_OK;
    if(keypad == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(counter=0;counter<4;counter++)
        {
            ret = gpio_pin_init(&(keypad->rows[counter]));
            ret = gpio_pin_direction_init(&(keypad->columns[counter]));
        }
    }
    return ret;
}
/**
 * 
 * @param keypad
 * @param value
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission  
 */
Std_ReturnType keypad_get_value(keypad_t *keypad,uint8 *value)
{
    uint8 counter1=0;    
    uint8 counter2=0;
    uint8 logic = 0;
    Std_ReturnType ret = E_NOT_OK;
    if(keypad == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(counter1=0;counter1<4;counter1++)
        {
            gpio_pin_write_logic(&(keypad->rows[counter1]),LOW);
        }
        for(counter1=0;counter1<4;counter1++)
        {
            gpio_pin_write_logic(&(keypad->rows[counter1]),HIGH);
            
            for(counter2 =0;counter2<4;counter2++)
            {
                gpio_pin_read_logic(&(keypad->columns[counter2]),&logic);
                if(logic == HIGH)
                {
                    (*value) = values[counter1][counter2];
                    gpio_pin_write_logic(&(keypad->rows[counter1]),LOW);
                }
            }
        }
        ret = E_OK;
    }
    return ret;
}
