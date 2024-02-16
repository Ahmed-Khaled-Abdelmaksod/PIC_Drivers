/* 
 * File:   ECU_chr_lcd.h
 * Author: Ahmed Khaled
 *
 * Created on 15 ?????, 2023, 09:26 ?
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000UL
#endif

#include"../../MCAL/GPIO/MCAL_gpio.h"

// commands
#define _LCD_CLEAR_DISPLAY_                         (uint8)0x01
#define _LCD_RETURN_HOME_                           (uint8)0x02
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF               (uint8)0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON                (uint8)0x07
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF               (uint8)0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON                (uint8)0x05
#define _LCD_CURSOR_SHIFT_RIGHT                     (uint8)0x14
#define _LCD_CURSOR_SHIFT_LEFT                      (uint8)0x10
#define _LCD_DISPLAY_SHIFT_LEFT                     (uint8)0x18
#define _LCD_DISPLAY_SHIFT_RIGHT                    (uint8)0x1C
#define _LCD_4BIT_MODE_2LINE                        (uint8)0x28
#define _LCD_8BIT_MODE_2LINE                        (uint8)0x38
#define _LCD_DISPLAY_ON_CURSOR_OFF_UNDERLINE_OFF    (uint8)0x0C
#define _LCD_DISPLAY_ON_CURSOR_OFF_UNDERLINE_ON     (uint8)0x0D
#define _LCD_DISPLAY_ON_CURSOR_ON_UNDERLINE_OFF     (uint8)0x0E
#define _LCD_DISPLAY_ON_CURSOR_ON_UNDERLINE_ON      (uint8)0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF_UNDERLINE_OFF   (uint8)0x08
#define _LCD_START_CGRAM_ADR                        (uint8)0x40
#define _LCD_START_DDRAM_ADR                        (uint8)0x80
//lcds' modes
typedef struct 
{
    pin_config_t lcd_rs;
    pin_config_t lcd_e;
    pin_config_t data_pins[8];
}chr_lcd_8bit_t;

typedef struct 
{
    pin_config_t lcd_rs;
    pin_config_t lcd_e;
    pin_config_t data_pins[4];
}chr_lcd_4bit_t;


// interfaces
/**
 * 
 * @param lcd
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_4bit_init(const chr_lcd_4bit_t *lcd);
/**
 * 
 * @param lcd
 * @param cmd
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_4bit_send_cmd(const chr_lcd_4bit_t *lcd,uint8 cmd);
/**
 * 
 * @param lcd
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_4bit_send_data_char(const chr_lcd_4bit_t *lcd,uint8 data);
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
Std_ReturnType chr_lcd_4bit_send_data_char_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data);
/**
 * 
 * @param lcd
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_4bit_send_data_string(const chr_lcd_4bit_t *lcd,uint8 *data);
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
Std_ReturnType chr_lcd_4bit_send_data_string_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 *data);
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
                                            const uint8 _chrs[],uint8 mem_Pos);
/**
 * 
 * @param lcd
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_8bit_init(const chr_lcd_8bit_t *lcd);
/**
 * 
 * @param lcd
 * @param cmd
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_8bit_send_cmd(const chr_lcd_8bit_t *lcd,uint8 cmd);
/**
 * 
 * @param lcd
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_8bit_send_data_char(const chr_lcd_8bit_t *lcd,uint8 data);
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
Std_ReturnType chr_lcd_8bit_send_data_char_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data);
/**
 * 
 * @param lcd
 * @param data
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission 
 */
Std_ReturnType chr_lcd_8bit_send_data_string(const chr_lcd_8bit_t *lcd,uint8 *data);
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
Std_ReturnType chr_lcd_8bit_send_data_string_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 *data);
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
                                            const uint8 _chrs[],uint8 mem_Pos);
#endif	/* ECU_CHR_LCD_H */
/**
 * 
 * @param data
 * @param str
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission  
 */
Std_ReturnType lcd_convert_uint8_to_string(uint8 data,uint8 *str);
/**
 * 
 * @param data
 * @param str
 * @return Std_ReturnType 
 *         E_OK     -> function does its mission 
 *         E_NOT_OK -> function doesn't do its mission  
 */
Std_ReturnType lcd_convert_uint16_to_string(uint16 data,uint8 *str);
