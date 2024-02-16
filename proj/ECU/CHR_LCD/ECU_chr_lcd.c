#include"ECU_chr_lcd.h"


static void chr_lcd_enable_signal(pin_config_t *enable);
static void send_4bit(const chr_lcd_4bit_t *lcd,uint8 data);
static void set_cursor_8bit(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column);
static void set_cursor_4bit(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column);
/**
 * 
 * @param lcd
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_4bit_init(const chr_lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 counter=0;
    if(lcd == NULL)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        
        gpio_pin_init(&(lcd->lcd_rs));
        gpio_pin_init(&(lcd->lcd_e));
        for(counter=0;counter<4;counter++)
        {
            gpio_pin_init(&(lcd->data_pins[counter]));
        }
        __delay_ms(20);
        chr_lcd_4bit_send_cmd(lcd,0x33);
        __delay_ms(5);
        chr_lcd_4bit_send_cmd(lcd,0x33);
        __delay_us(150);
        chr_lcd_4bit_send_cmd(lcd,0x33);
        
        chr_lcd_4bit_send_cmd(lcd,_LCD_CLEAR_DISPLAY_);
        chr_lcd_4bit_send_cmd(lcd,_LCD_RETURN_HOME_);
        chr_lcd_4bit_send_cmd(lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
        chr_lcd_4bit_send_cmd(lcd,_LCD_DISPLAY_ON_CURSOR_OFF_UNDERLINE_OFF);
        chr_lcd_4bit_send_cmd(lcd,_LCD_4BIT_MODE_2LINE);
        chr_lcd_4bit_send_cmd(lcd,_LCD_START_DDRAM_ADR);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param cmd
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_4bit_send_cmd(const chr_lcd_4bit_t *lcd,uint8 cmd)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(lcd == NULL)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        
        gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        send_4bit(lcd,cmd>>4);
        chr_lcd_enable_signal(&(lcd->lcd_e));
        send_4bit(lcd,cmd);
        chr_lcd_enable_signal(&(lcd->lcd_e));
        
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_4bit_send_data_char(const chr_lcd_4bit_t *lcd,uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        send_4bit(lcd,data>>4);
        chr_lcd_enable_signal(&(lcd->lcd_e));
        send_4bit(lcd,data);
        chr_lcd_enable_signal(&(lcd->lcd_e));
        
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_4bit_send_data_char_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        set_cursor_4bit(lcd,row,column);
        chr_lcd_4bit_send_data_char(lcd,data);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_4bit_send_data_string(const chr_lcd_4bit_t *lcd,uint8 *data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        while(*data)
        {
            chr_lcd_4bit_send_data_char(lcd,*data++);
        }
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission  
 */
Std_ReturnType chr_lcd_4bit_send_data_string_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 *data)
{
    Std_ReturnType ret = E_NOT_OK;
    if((lcd == NULL) || (data == NULL))
    {
        ret = E_NOT_OK; 
    }
    else
    {
        
        set_cursor_4bit(lcd,row,column);
        chr_lcd_4bit_send_data_string(lcd,data);
        
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chrs
 * @param mem_Pos
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_4bit_send_custom_chr(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,
                                            const uint8 _chrs[],uint8 mem_Pos)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 counter = 0;
    if(lcd == NULL)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        chr_lcd_4bit_send_cmd(lcd,_LCD_START_CGRAM_ADR + (8*mem_Pos));
        for(counter=0;counter<8;counter++)
        {
            chr_lcd_4bit_send_data_char(lcd,_chrs[counter]);
        }
        chr_lcd_4bit_send_data_char_pos(lcd,row,column,mem_Pos);
       
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_8bit_init(const chr_lcd_8bit_t *lcd)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 counter=0;
    if(lcd == NULL)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        gpio_pin_init(&(lcd->lcd_rs));
        gpio_pin_init(&(lcd->lcd_e));
        for(counter=0;counter<8;counter++)
        {
            gpio_pin_init(&(lcd->data_pins[counter]));
        }
        __delay_ms(20);
        chr_lcd_8bit_send_cmd(lcd,_LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        chr_lcd_8bit_send_cmd(lcd,_LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        chr_lcd_8bit_send_cmd(lcd,_LCD_8BIT_MODE_2LINE);
        
        chr_lcd_8bit_send_cmd(lcd,_LCD_CLEAR_DISPLAY_);
        chr_lcd_8bit_send_cmd(lcd,_LCD_RETURN_HOME_);
        chr_lcd_8bit_send_cmd(lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
        chr_lcd_8bit_send_cmd(lcd,_LCD_DISPLAY_ON_CURSOR_OFF_UNDERLINE_OFF);
        chr_lcd_8bit_send_cmd(lcd,_LCD_START_DDRAM_ADR);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param cmd
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_8bit_send_cmd(const chr_lcd_8bit_t *lcd,uint8 cmd)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 counter=0;
    if(lcd == NULL)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        for(counter=0;counter<8;counter++)
        {   
            ret = gpio_pin_write_logic(&(lcd->data_pins[counter]),(cmd>>counter)&0x01);
        }
        chr_lcd_enable_signal(&(lcd->lcd_e));
        
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_8bit_send_data_char(const chr_lcd_8bit_t *lcd,uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 counter=0;
    if(lcd == NULL)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        for(counter=0;counter<8;counter++)
        {
            gpio_pin_write_logic(&(lcd->data_pins[counter]),(data>>counter) & ((uint8)0x01));
        }
        chr_lcd_enable_signal(&(lcd->lcd_e));
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_8bit_send_data_char_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        set_cursor_8bit(lcd,row,column);
        chr_lcd_8bit_send_data_char(lcd,data);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_8bit_send_data_string(const chr_lcd_8bit_t *lcd,uint8 *data)
{
    Std_ReturnType ret = E_NOT_OK;
    if((lcd == NULL) || (data == NULL))
    {
        ret = E_NOT_OK; 
    }
    else
    {
        while(*data)
        {
            chr_lcd_8bit_send_data_char(lcd,*data++);
            
        }
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_8bit_send_data_string_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 *data)
{
    Std_ReturnType ret = E_NOT_OK;
    if((lcd == NULL)|| (data == NULL))
    {
        ret = E_NOT_OK; 
    }
    else
    {
        set_cursor_8bit(lcd,row,column);
        chr_lcd_8bit_send_data_string(lcd,data);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chrs
 * @param mem_Pos
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_8bit_send_custom_chr(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,
                                            const uint8 _chrs[],uint8 mem_Pos)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 counter =0;
    if(lcd == NULL)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        
        chr_lcd_8bit_send_cmd(lcd,_LCD_START_CGRAM_ADR + (8*mem_Pos));
        for(counter=0;counter<8;counter++)
        {
            chr_lcd_8bit_send_data_char(lcd,_chrs[counter]);
        }
        chr_lcd_8bit_send_data_char_pos(lcd,row,column,mem_Pos);
    }
    return ret;
}

static void chr_lcd_enable_signal(pin_config_t *enable)
{
    gpio_pin_write_logic(enable,HIGH);
    __delay_us(10);
    gpio_pin_write_logic(enable,LOW);
}

static void send_4bit(const chr_lcd_4bit_t *lcd,uint8 data)
{
    uint8 counter =0;
    for(counter=0;counter<4;counter++)
    {
        gpio_pin_write_logic(&(lcd->data_pins[counter]),(data>>counter) & ((uint8)0x01));
    }
}
static void set_cursor_8bit(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column)
{
    column--;
    switch(row)
    {
        case 1 : chr_lcd_8bit_send_cmd(lcd,(0x80 + column)); break;
        case 2 : chr_lcd_8bit_send_cmd(lcd,(0xC0 + column)); break;
        case 3 : chr_lcd_8bit_send_cmd(lcd,(0x94 + column)); break;
        case 4 : chr_lcd_8bit_send_cmd(lcd,(0xD4 + column)); break;     
    }
}
static void set_cursor_4bit(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column)
{
    column--;
    switch(row)
    {
        case 1 : chr_lcd_4bit_send_cmd(lcd,(0x80 + column)); break;
        case 2 : chr_lcd_4bit_send_cmd(lcd,(0xC0 + column)); break;
        case 3 : chr_lcd_4bit_send_cmd(lcd,(0x94 + column)); break;
        case 4 : chr_lcd_4bit_send_cmd(lcd,(0xD4 + column)); break;     
    }
}

/**
 * 
 * @param data
 * @param str
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission  
 */
Std_ReturnType lcd_convert_uint8_to_string(uint8 data,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    uint8 Temp_String[4] = {0};
    uint8 DataCounter = 0;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset(str, ' ', 5);
        str[3] = '\0';
        sprintf((char *)Temp_String, "%i", data);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
}
/**
 * 
 * @param data
 * @param str
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission  
 */
Std_ReturnType lcd_convert_uint16_to_string(uint16 data,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", data);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
}