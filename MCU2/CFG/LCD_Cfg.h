/*
 * LCD_Cfg.h
 *
 * Created: 4/23/2024 9:55:38 PM
 *  Author: lenovo
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define		_4_BIT		1
#define		_8_BIT		2

#define		_2_LINE		1
#define		_4_LINE		2


#define		LCD_MODE	_4_BIT
#define		LCD_LINES	_4_LINE

#define  LCD_PORT   PA

#define  D7   PINA6
#define  D6   PINA5
#define  D5   PINA4
#define  D4   PINA3


#define  RS  PINA1
#define  EN  PINA2





#endif /* LCD_CFG_H_ */