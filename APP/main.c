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
#include  "APP_cfg.h"
#define   F_CPU	16000000UL
#include <util/delay.h>

typedef struct{
	uint8 TempMin;
	uint8 TempMax;
	uint8 LightLevelMin;
	uint8 LightLevelMax;
	uint8 SoilMoistureMin;
	uint8 SoilMoistureMax;
	uint8 HumidityMin;
	uint8 HumidityMax;
}_sUser_cfg_t;



void voidFan(void);
void voidHeater(void);
void voidIrrigation();
void voidLight();
void voidAlert();


static _sUser_cfg_t  sCfg_obj = {21,27,50,80,40,60,60,70};
static uint8  u8TempValue = 0;
static uint8  u8LightLevel = 0;
static uint8 u8SoilMoisture = 0;
static uint8  u8AlertCOD = u8NO_ALERT;
static uint8  u8Humidity = 65;


void main(){

	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();
	//DHT_Setup();

	uint16  Local_u8AdcVal;

	while(1){

		u8TempValue =  LM34_u8GetTempInC(ADC_u8SINGLE_ENDED_ADC0);
		u8LightLevel = LDR_u8GetLightLevel(ADC_u8SINGLE_ENDED_ADC1, 200);
		u8SoilMoisture = SOIL_u16GetMoisture(ADC_u8SINGLE_ENDED_ADC2, 40);
		// DHT_GetHumidity(&Local_u8Humidity);

		CLCD_voidGoToXY(0,0);
		CLCD_u8SendString("T:");
		CLCD_u8SendNumber(u8TempValue);

		CLCD_voidGoToXY(9,0);
		CLCD_u8SendString("L:");
		CLCD_u8SendNumber(u8LightLevel);

		CLCD_voidGoToXY(0,1);
		CLCD_u8SendString("M:");
		CLCD_u8SendNumber(u8SoilMoisture);
		CLCD_u8SendString("%");

		CLCD_voidGoToXY(9,1);
		CLCD_u8SendString("H:");
		CLCD_u8SendNumber(u8Humidity);
		CLCD_u8SendString("%");



		voidFan();
		voidHeater();
		voidIrrigation();
		voidLight();
		voidAlert();
//	    CLCD_voidSendCmd(CLCD_u8CLEAR_LCD);



	}


}

void voidFan(void){

	if(u8TempValue > sCfg_obj.TempMax){
		DIO_u8SetPinValue(u8FAN_PORT,u8FAN_PIN, DIO_u8PIN_HIGH);
	}else{
		DIO_u8SetPinValue(u8FAN_PORT,u8FAN_PIN, DIO_u8PIN_LOW);
	}

}


void voidHeater(void){

	if(u8TempValue < sCfg_obj.TempMin){
		DIO_u8SetPinValue(u8HEATER_PORT,u8HEATER_PIN, DIO_u8PIN_HIGH);
	}else{
		DIO_u8SetPinValue(u8HEATER_PORT,u8HEATER_PIN, DIO_u8PIN_LOW);
	}

}


void voidIrrigation(){

	if(u8SoilMoisture < sCfg_obj.SoilMoistureMin){
		DIO_u8SetPinValue(u8IRRIGATION_PORT,u8IRRIGATION_PIN, DIO_u8PIN_HIGH);
	}else if(u8SoilMoisture > sCfg_obj.SoilMoistureMax){
		DIO_u8SetPinValue(u8IRRIGATION_PORT,u8IRRIGATION_PIN, DIO_u8PIN_LOW);
	}
}


void voidLight(){

	if(u8LightLevel < sCfg_obj.LightLevelMin){
		DIO_u8SetPinValue(u8LIGHT_PORT,u8LIGHT_PIN, DIO_u8PIN_HIGH);
	}else if(u8LightLevel > sCfg_obj.LightLevelMax){
		DIO_u8SetPinValue(u8LIGHT_PORT,u8LIGHT_PIN, DIO_u8PIN_LOW);
	}

}


void voidAlert(){

	if(u8TempValue > sCfg_obj.TempMax || u8TempValue < sCfg_obj.TempMin){
		u8AlertCOD = u8TEMP_ALERT_COD;
	}else if(u8SoilMoisture < sCfg_obj.SoilMoistureMin || u8SoilMoisture > sCfg_obj.SoilMoistureMax){
		u8AlertCOD = u8MOISTURE_ALERT_COD;
	}else if(u8LightLevel < sCfg_obj.LightLevelMin ||  u8LightLevel > sCfg_obj.LightLevelMax){
		u8AlertCOD = u8LIGHT_ALERT_COD;
	}else if(u8Humidity < sCfg_obj.HumidityMin || u8Humidity > sCfg_obj.HumidityMax){
		u8AlertCOD = u8HUMIDITY_ALERT_COD;
	}else{
		u8AlertCOD = u8NO_ALERT;
	}

	if(u8AlertCOD == u8NO_ALERT){
		DIO_u8SetPinValue(u8BUZZER_PORT,u8BUZZER_PIN, DIO_u8PIN_LOW);
	}else{
		DIO_u8SetPinValue(u8BUZZER_PORT,u8BUZZER_PIN, DIO_u8PIN_HIGH);
	}

}


