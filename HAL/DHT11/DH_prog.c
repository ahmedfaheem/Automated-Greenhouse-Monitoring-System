#include "DHT_Private.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/STD_TYPES.h"
#define F_CPU 16000000UL

#include <util/delay.h>

#include "DH_Interface.h"

#include "../../MCAL/1- DIO/DIO_interface.h"
enum DHT_Status_t __DHT_STATUS;


/****************Functions*****************/
//Setup sensor.
void DHT_Setup()
{
	_delay_ms(__DHT_Delay_Setup);
	__DHT_STATUS = DHT_Ok;
}

//Get sensor status.
enum DHT_Status_t DHT_GetStatus()
{
	return (__DHT_STATUS);
}

//Read raw buffer from sensor.
 enum DHT_Status_t DHT_ReadRaw(uint8 Data[4])
{
	uint8 Pinval;
	uint8 buffer[5] = {0, 0, 0, 0, 0};
	uint8 retries, i;
	int8_t j;
	__DHT_STATUS = DHT_Ok;
	retries = i = j = 0;

	//----- Step 1 - Start communication -----
	if (__DHT_STATUS == DHT_Ok)
	{
		//Request data

		//DigitalWrite(DHT_Pin, Low);			//DHT_PIN = 0
		DIO_u8SetPinValue(DHT_PORT,DHT_PIN,DIO_u8PIN_LOW);				//DHT_PIN = 0
		DIO_u8SetPinDirection(DHT_PORT,DHT_PIN,DIO_u8PIN_OUTPUT);		//DHT_PIN = Output
		//PinMode(DHT_Pin, Output);			//DHT_PIN = Output
		_delay_ms(__DHT_Delay_Read);

		//Setup DHT_PIN as input with pull-up resistor so as to read data


		//DigitalWrite(DHT_Pin, High);		//DHT_PIN = 1 (Pull-up resistor)
		DIO_u8SetPinValue(DHT_PORT,DHT_PIN,DIO_u8PIN_HIGH);				//DHT_PIN = 1 (Pull-up resistor)


		//PinMode(DHT_Pin, Input);			//DHT_PIN = Input
		DIO_u8SetPinDirection(DHT_PORT,DHT_PIN,DIO_u8PIN_INPUT);		//DHT_PIN = Input
		//Wait for response for 20-40us
		retries = 0;
		DIO_u8ReadPinValue(DHT_PORT,DHT_PIN,&Pinval);
		while (Pinval)
		{
			_delay_us(2);
			retries += 2;
			if (retries > 60)
			{
				__DHT_STATUS = DHT_Error_Humidity;	//Timeout error
				break;
			}
			DIO_u8ReadPinValue(DHT_PORT,DHT_PIN,&Pinval);
		}
	}
	//----------------------------------------

	//----- Step 2 - Wait for response -----
	if (__DHT_STATUS == DHT_Ok)
	{
		//Response sequence began
		//Wait for the first response to finish (low for ~80us)
		retries = 0;
		DIO_u8ReadPinValue(DHT_PORT,DHT_PIN,&Pinval);
		while (!Pinval)
		{
			_delay_us(2);
			retries += 2;
			if (retries > 100)
			{
				__DHT_STATUS = DHT_Error_Timeout;	//Timeout error
				break;
			}
			DIO_u8ReadPinValue(DHT_PORT,DHT_PIN,&Pinval);
		}
		//Wait for the last response to finish (high for ~80us)
		DIO_u8ReadPinValue(DHT_PORT,DHT_PIN,&Pinval);
		while (Pinval)
		{
			_delay_us(2);
			retries += 2;
			if (retries > 100)
			{
				__DHT_STATUS = DHT_Error_Timeout;	//Timeout error
				break;
			}
			DIO_u8ReadPinValue(DHT_PORT,DHT_PIN,&Pinval);
		}
	}
	//--------------------------------------

	//----- Step 3 - Data transmission -----
	if (__DHT_STATUS == DHT_Ok)
	{
		//Reading 5 bytes, bit by bit
		for (i = 0 ; i < 5 ; i++)
		for (j = 7 ; j >= 0 ; j--)
		{
			//There is always a leading low level of 50 us
			retries = 0;
			DIO_u8ReadPinValue(DHT_PORT,DHT_PIN,&Pinval);
			while (!Pinval)
			{
				_delay_us(2);
				retries += 2;
				if (retries > 70)
				{
					__DHT_STATUS = DHT_Error_Timeout;	//Timeout error
					j = -1;								//Break inner for-loop
					i = 5;								//Break outer for-loop
					break;								//Break while loop
				}
				DIO_u8ReadPinValue(DHT_PORT,DHT_PIN,&Pinval);
			}

			if (__DHT_STATUS == DHT_Ok)
			{
				//We read data bit || 26-28us means '0' || 70us means '1'
				_delay_us(35);							//Wait for more than 28us
				DIO_u8ReadPinValue(DHT_PORT,DHT_PIN,&Pinval);
				if (Pinval)			//If HIGH
				SET_BIT(buffer[i], j);				//bit = '1'

				retries = 0;
				DIO_u8ReadPinValue(DHT_PORT,DHT_PIN,&Pinval);
				while (Pinval)
				{
					_delay_us(2);
					retries += 2;
					if (retries > 100)
					{
						__DHT_STATUS = DHT_Error_Timeout;	//Timeout error
						break;
					}
					DIO_u8ReadPinValue(DHT_PORT,DHT_PIN,&Pinval);
				}
			}
		}
	}
	//--------------------------------------


	//----- Step 4 - Check checksum and return data -----
	if (__DHT_STATUS == DHT_Ok)
	{
		if (((uint8)(buffer[0] + buffer[1] + buffer[2] + buffer[3])) != buffer[4])
		{
			__DHT_STATUS = DHT_Error_Checksum;	//Checksum error
		}
		else
		{
			//Build returning array
			//data[0] = Humidity		(int)
			//data[1] = Humidity		(dec)
			//data[2] = Temperature		(int)
			//data[3] = Temperature		(dec)
			//data[4] = Checksum
			for (i = 0 ; i < 4 ; i++)
			Data[i] = buffer[i];
		}
	}
	//---------------------------------------------------

	return DHT_GetStatus();
}

//Read temperature in Celsius.
enum DHT_Status_t DHT_GetTemperature(uint8 *Temperature)
{
	uint8 *waste = 0;
	return DHT_Read(Temperature, waste);
}

//Read humidity percentage.
enum DHT_Status_t DHT_GetHumidity(uint8 *Humidity)
{
	uint8 *waste = 0;
	return DHT_Read(waste, Humidity);
}

//Read temperature and humidity.
enum DHT_Status_t DHT_Read(uint8 *Temperature, uint8 *Humidity)
{
	uint8 data[4] = { 0, 0, 0, 0 };

	//Read data
	enum DHT_Status_t status =  DHT_ReadRaw(data);

	//If read successfully
	if (status == DHT_Ok)
	{
		//Calculate values
		*Temperature =data[2];
		*Humidity = data[0];

		//Check values
		if ((*Temperature < __DHT_Temperature_Min) || (*Temperature > __DHT_Temperature_Max))
		__DHT_STATUS = DHT_Error_Temperature;
		else if ((*Humidity < __DHT_Humidity_Min) || (*Humidity > __DHT_Humidity_Max))
		__DHT_STATUS = DHT_Error_Humidity;
	}

	return DHT_GetStatus();
}
//---------------------------------------------//
