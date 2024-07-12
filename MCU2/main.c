#define F_CPU	8000000UL
#include <util/delay.h>
#include "StdTypes.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"
#include "plant_char.h"
#include "UART_Interface.h"
#include "UART_Service.h"
#include "MemMap.h"
static plant_char_t current;

void RX_INT()
{
	u32 num;
	u8 *p;
	p=&num;
	num = UART_ReceiveNumber();
	current.humidity=p[0];
	current.temp=p[1];
	current.soil_water=p[2];
	current.light_intensity=p[3];
}

void init()
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	UART_Init();
	GLOBAL_ENABLE();
	UART_RX_SetCallBack(RX_INT);
	UART_RX_InterruptEnable();
}


void startText()
{
	LCD_WriteString("Choose the plant");
	_delay_ms(2000);
	LCD_Clear();
	LCD_WriteString("1-tomatoes");
	LCD_SetCursor(1,0);
	LCD_WriteString("2-corn");
	LCD_SetCursor(2,0);
	LCD_WriteString("3-wheat");
	LCD_SetCursor(3,0);
	LCD_WriteString("4-custom");
}



int main(void)
{
	init();//init functions
	
	//variables
	u32 num;
	u8 digit,*p=&num;;
	plant_char_t max,min;
	
	
	startText();
	
	//choose plant
	digit=KEYPAD_GetKey();
	while(digit>'4'||digit<'1')
	{
		digit=KEYPAD_GetKey();

	}
	if (digit>='1'&&digit<='3')
	{
		max = setPlantMax(digit-'0');
		min = setPlantMin(digit-'0');

	}
	else
	{
		LCD_Clear();
		LCD_WriteString("**upper limit**");
		_delay_ms(1000);
		max = setCustom();
		LCD_Clear();
		LCD_WriteString("**lower limit**");
		_delay_ms(1000);
		min = setCustom();
	}
	
	
	//SEND REFERENCE DATA
	//max
	p[0]=max.humidity;
	p[1]=max.temp;
	p[2]=max.soil_water;
	p[3]=max.light_intensity;
	UART_SendNumber(num);
	//min
	p[0]=min.humidity;
	p[1]=min.temp;
	p[2]=min.soil_water;
	p[3]=min.light_intensity;
	UART_SendNumber(num);
	LCD_Clear();
	LCD_WriteString("H:");
	LCD_SetCursor(1,0);
	LCD_WriteString("T:");
	LCD_SetCursor(2,0);
	LCD_WriteString("W:");
	LCD_SetCursor(3,0);
	LCD_WriteString("L:");
	while (1)
	{
		//display current data
		LCD_SetCursor(0,2);
		LCD_WriteNumber(current.humidity);
		LCD_WriteString("   ");
		LCD_SetCursor(0,7);
		if (current.humidity>max.humidity)//humidity
		{
			LCD_WriteString("high!!");
		}
		else if (current.humidity<min.humidity)
		{
			LCD_WriteString("low!! ");
		}
		else{
			LCD_WriteString("      ");
		}
		LCD_SetCursor(1,2);
		LCD_WriteNumber(current.temp);
		LCD_WriteString("   ");
		LCD_SetCursor(1,7);
		if (current.temp>max.temp)//temperature
		{
			LCD_WriteString("high!!");
		}
		else if (current.temp<min.temp)
		{
			LCD_WriteString("low!! ");
		}
		else{
			LCD_WriteString("      ");
		}
		LCD_SetCursor(2,2);
		LCD_WriteNumber(current.soil_water);
		LCD_WriteString("   ");
		LCD_SetCursor(2,7);
		if (current.soil_water>max.soil_water)//soil water
		{
			LCD_WriteString("high!!");
		}
		else if (current.soil_water<min.soil_water)
		{
			LCD_WriteString("low!! ");
		}
		else
		{
			LCD_WriteString("      ");
		}
		LCD_SetCursor(3,2);
		LCD_WriteNumber(current.light_intensity);
		LCD_WriteString("   ");
		if (current.light_intensity>max.light_intensity)//light_intensity
		{
			LCD_WriteString("high!!");
		}
		else if (current.light_intensity<min.light_intensity)
		{
			LCD_WriteString("low!! ");
		}
		else
		{
			LCD_WriteString("      ");
		}
	
	}
}

