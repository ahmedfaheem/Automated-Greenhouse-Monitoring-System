/*
 * KYPAD_Cfg.h
 *
 * Created: 4/27/2024 7:34:06 PM
 *  Author: lenovo
 */ 


#ifndef KYPAD_CFG_H_
#define KYPAD_CFG_H_

#define  ROWS  4
#define  COLS  4

#define	 FIRST_OUTPUT    PINB4		//rows
#define  FIRST_INPUT     PIND2		//colnums


#if KEYPAD_PRG


const  u8 KeysArr[ROWS][COLS]={ {'7','8','9','/'},
								{'4','5','6','*'},
								{'1','2','3','+'},
								{'c','0','=','-'},
};
#endif 


#endif /* KYPAD_CFG_H_ */