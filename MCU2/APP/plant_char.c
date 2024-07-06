/*
* plant_char.c
*
* Created: 7/6/2024 1:26:06 AM
*  Author: khaled
*/
#include "StdTypes.h"
#include "plant_char.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"
plant_char_t char_arr[]={
	{TOMATOES_HUMIDITY,TOMATOES_TEMP,TOMATOES_SOIL_WATER,TOMATOES_LIGHT},
	{CORN_HUMIDITY,CORN_TEMP,CORN_SOIL_WATER,CORN_LIGHT},
	{WHEAT_HUMIDITY,WHEAT_TEMP,WHEAT_SOIL_WATER,WHEAT_LIGHT},
};

plant_char_t  setPlantChar(plants_t plant)
{
	plant_char_t plantChar;
	plantChar.humidity=char_arr[plant-1].humidity;
	plantChar.temp=char_arr[plant-1].temp;
	plantChar.soil_water=char_arr[plant-1].soil_water;
	plantChar.light_intensity=char_arr[plant-1].light_intensity;
	return plantChar;
}

plant_char_t  setCustom()
{
	plant_char_t plantChar;
	u8 num,digit;
	LCD_Clear();
	LCD_WriteString("The humidity: ");
	num=0;
	digit=KEYPAD_GetKey();
	while(digit!='=')
	{
		digit=KEYPAD_GetKey();

		if (digit>='0'&&digit<='9')
		{
			LCD_WriteChar(digit);
			num = num * 10 + digit - '0';
		}
		
	}

	plantChar.humidity=num;
	
	LCD_Clear(); 
	LCD_WriteString("The Temp: ");
	num=0;
	digit=KEYPAD_GetKey();
	while(digit!='=')
	{
		digit=KEYPAD_GetKey();
		if (digit>='0'&&digit<='9')
		{
			LCD_WriteChar(digit);
			num = num * 10 + digit - '0';
		}
	}
	plantChar.temp=num;
	
	LCD_Clear();
	LCD_WriteString("Soil water: ");
	num=0;
	digit=KEYPAD_GetKey();
	while(digit!='=')
	{
		digit=KEYPAD_GetKey();
		if (digit>='0'&&digit<='9')
		{
			LCD_WriteChar(digit);
			num = num * 10 + digit - '0';
		}
	}
	
	plantChar.soil_water=num;
	
	LCD_Clear();
	LCD_WriteString("Light intensity: ");
	LCD_SetCursor(1,0);
	num=0;
	digit=KEYPAD_GetKey();
	while(digit!='=')
	{
		digit=KEYPAD_GetKey();
		if (digit>='0'&&digit<='9')
		{
			LCD_WriteChar(digit);
			num = num * 10 + digit - '0';
		}
	}
	
	plantChar.light_intensity=num;
	return plantChar;
}

