
#define  F_CPU   8000000
#include <util/delay.h>
#include "StdTypes.h"

#include "DIO_Int.h"

#include "LCD_Int.h"
#include "LCD_Cfg.h"


#if  LCD_MODE==_8_BIT
void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	
	WriteIns(0x38);
	WriteIns(0x0c);//0x0e,0x0f
	WriteIns(0x01);//clear screen
	_delay_ms(1);
	WriteIns(0x06);
}
#elif LCD_MODE==_4_BIT

void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,GET_BIT(ins,7));
	DIO_WritePin(D6,GET_BIT(ins,6));
	DIO_WritePin(D5,GET_BIT(ins,5));
	DIO_WritePin(D4,GET_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,GET_BIT(ins,3));
	DIO_WritePin(D6,GET_BIT(ins,2));
	DIO_WritePin(D5,GET_BIT(ins,1));
	DIO_WritePin(D4,GET_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void WriteData(u8 ins)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,GET_BIT(ins,7));
	DIO_WritePin(D6,GET_BIT(ins,6));
	DIO_WritePin(D5,GET_BIT(ins,5));
	DIO_WritePin(D4,GET_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,GET_BIT(ins,3));
	DIO_WritePin(D6,GET_BIT(ins,2));
	DIO_WritePin(D5,GET_BIT(ins,1));
	DIO_WritePin(D4,GET_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);
	WriteIns(0x0c);//0x0e,0x0f
	WriteIns(0x01);//clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

#endif








void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}

void LCD_WriteString(c8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
	
}

void LCD_WriteNumber(s32 num)//-150
{
	c8 str[10];
	s8 i=0,j;
	if (num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	if (num<0)
	{
		LCD_WriteChar('-');
		num=-num;
	}
	while(num)
	{
		str[i++]=num%10+'0';
		num/=10;
	}
	for(j=i-1;j>=0;j--)
	{
		LCD_WriteChar(str[j]);
	}
	
}

/* move on LCD*/

void LCD_Clear(void)
{
	WriteIns(0x01);
	_delay_ms(1);
	
}

void LCD_WriteBinary(u8 num)
{
	s8 i;
	for (i=7;i>=0;i--)
	{
		LCD_WriteChar(GET_BIT(num,i)+'0');
	}
	
}

void LCD_WriteHex(u8 num)
{
	u8 HN=num>>4;
	u8 LN=num&0x0f;
	
	if (HN<10)
	{
		LCD_WriteChar(HN+'0');
	}
	else
	{
		LCD_WriteChar(HN+'A'-10);
	}
	if (LN<10)
	{
		LCD_WriteChar(LN+'0');
	}
	else
	{
		LCD_WriteChar(LN+'A'-10);
	}
	
}


/* line 0:1 cell 0:15*/
void LCD_SetCursor(u8 line ,u8 cell)
{
	if (line==0)
	{
		WriteIns(cell+0x80);
	}
	else if (line==1)
	{
		WriteIns(cell+0x40+0x80);
	}
	#if LCD_LINES==_4_LINE
	else if (line==2)
	{
		WriteIns(cell+0x10+0x80);
	}
	else if (line==3)
	{
		WriteIns(cell+0x50+0x80);
	}
	#endif
}

void LCD_ClearCursor(u8 line,u8 cell,u8 NofCells)
{
	LCD_SetCursor(line,cell);
	for (u8 i=0;i<NofCells;i++)
	{
		LCD_WriteChar(' ');
	}
	
}

void LCD_WriteStringCursor(u8 line,u8 cell,c8 *str)
{
	LCD_SetCursor(line,cell);
	LCD_WriteString(str);
}

