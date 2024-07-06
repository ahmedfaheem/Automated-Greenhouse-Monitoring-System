#define F_CPU	8000000UL
#include <util/delay.h>
#include "StdTypes.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"
#include "plant_char.h"


void init()
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
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


void showChar(plant_char_t *plantChar)
{
	LCD_Clear();
	LCD_WriteNumber(plantChar->humidity);
	LCD_SetCursor(1,0);
	LCD_WriteNumber(plantChar->temp);
	LCD_SetCursor(2,0);
	LCD_WriteNumber(plantChar->soil_water);
	LCD_SetCursor(3,0);
	LCD_WriteNumber(plantChar->light_intensity);
}

int main(void)
{
	//init functions
	init();

	//variables
	u8 digit;
	plant_char_t plantChar;
	
	startText();
	
	//choose plant
	digit=KEYPAD_GetKey();
	while(digit>'4'||digit<'1')
	{
		digit=KEYPAD_GetKey();

	}
	if (digit>='1'&&digit<='3')
	{
		plantChar = setPlantChar(digit-'0');

	}
	else
	{
		plantChar = setCustom();
	}
	
	//show characteristic's of planet
	showChar(&plantChar);

	while (1)
	{

	}
}

