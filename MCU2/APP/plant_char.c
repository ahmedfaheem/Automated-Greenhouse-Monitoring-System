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


plant_char_t max_arr[]={
	{TOMATOES_MAX_HUMIDITY,TOMATOES_MAX_TEMP,TOMATOES_MAX_SOIL_WATER,TOMATOES_MAX_LIGHT},
	{CORN_MAX_HUMIDITY,CORN_MAX_TEMP,CORN_MAX_SOIL_WATER,CORN_MAX_LIGHT},
	{WHEAT_MAX_HUMIDITY,WHEAT_MAX_TEMP,WHEAT_MAX_SOIL_WATER,WHEAT_MAX_LIGHT},
};

plant_char_t min_arr[]={
	{TOMATOES_MIN_HUMIDITY,TOMATOES_MIN_TEMP,TOMATOES_MIN_SOIL_WATER,TOMATOES_MIN_LIGHT},
	{CORN_MIN_HUMIDITY,CORN_MIN_TEMP,CORN_MIN_SOIL_WATER,CORN_MIN_LIGHT},
	{WHEAT_MIN_HUMIDITY,WHEAT_MIN_TEMP,WHEAT_MIN_SOIL_WATER,WHEAT_MIN_LIGHT},
};

plant_char_t  setPlantMax(plants_t plant)
{
	plant_char_t max;
	max.humidity=max_arr[plant-1].humidity;
	max.temp=max_arr[plant-1].temp;
	max.soil_water=max_arr[plant-1].soil_water;
	max.light_intensity=max_arr[plant-1].light_intensity;
	return max;
}

plant_char_t  setPlantMin(plants_t plant)
{
	plant_char_t min;
	min.humidity=min_arr[plant-1].humidity;
	min.temp=min_arr[plant-1].temp;
	min.soil_water=min_arr[plant-1].soil_water;
	min.light_intensity=min_arr[plant-1].light_intensity;
	return min;
}

plant_char_t  setCustom()
{
	plant_char_t data;
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

	data.humidity=num;
	
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
	data.temp=num;
	
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
	
	data.soil_water=num;
	
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
	
	data.light_intensity=num;
	return data;
}

