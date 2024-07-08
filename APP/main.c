#include "..\Library\STD_TYPES.h"
#include "..\Library\BIT_MATH.h"
#include "..\MCAL\1- DIO\DIO_interface.h"
#include "..\MCAL\2- PORT\PORT_interface.h"
#include "..\MCAL\3- GIE\GIE_interface.h"
#include "..\MCAL\4- EXTI\EXTI_interface.h"
#include "..\MCAL\5- ADC\ADC_interface.h"
#include "..\HAL\LDR\LDR_interface.h"
#include "..\HAL\LED\LED_interface.h"
#include "..\HAL\LM35\LM35_interface.h"
#include "..\HAL\MOTOR\MOTOR_interface.h"
#include "..\HAL\Soil_Moisture\SOIL_interface.h"
#include "..\HAL\DHT11\DH_Interface.h"
#include "..\HAL\CLCD\CLCD_interface.h"

#include <util/delay.h>

void main(){

	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();
	DHT_Setup();
	uint8  Local_u8TempValue = 0;
	uint8  Local_u8LightLevel = 0;
	uint16  Local_u8SoilMoisutre = 0;
	uint8  Local_u8Humidity = 0;
	uint16  Local_u8AdcVal;

	while(1){

	//	Local_u8TempValue =  LM34_u8GetTempInC(ADC_u8SINGLE_ENDED_ADC0);
	//	Local_u8LightLevel = LDR_u8GetLightLevel(ADC_u8SINGLE_ENDED_ADC1, 200);
		ADC_u8StartSingleConversionSynch(ADC_u8SINGLE_ENDED_ADC2, &Local_u8AdcVal);
		Local_u8SoilMoisutre =   SOIL_u16GetMoisture(Local_u8AdcVal);
	 DHT_GetHumidity(&Local_u8Humidity);

      CLCD_voidGoToXY(0,0);
       CLCD_u8SendNumber(DHT_GetStatus());
   // ADC_u8StartSingleConversionSynch(ADC_u8SINGLE_ENDED_ADC0,&read);

	}


}




