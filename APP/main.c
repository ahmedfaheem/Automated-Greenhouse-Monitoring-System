#include "..\Library\STD_TYPES.h"
#include "..\Library\BIT_MATH.h"
#include "..\MCAL\1- DIO\DIO_interface.h"
#define   F_CPU	16000000UL
#include <util/delay.h>
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
#include "..\MCAL\USART\USART_interface.h"


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

typedef struct{
	uint8 Temp;
	uint8 Level;
	uint8 Soil;
	uint8 Humidity;
	
}sReading_t;



void voidFan(void);
void voidHeater(void);
void voidIrrigation();
void voidLight();
void voidAlert();
void voidSendData();

static _sUser_cfg_t refrence;
static sReading_t     reading;
static uint8  u8AlertCOD = u8NO_ALERT;

void main(){

	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();
	DHT_Setup();
	USART_voidInit();
	uint8 *p;
	uint32 num1,num2;
	num1 = UART_u32ReceiveNumber();
	num2 = UART_u32ReceiveNumber();
	p=&num1;
	refrence.HumidityMax=p[0];
	refrence.TempMax=p[1];
	refrence.SoilMoistureMax=p[2];
	refrence.LightLevelMax=p[3];

	p=&num2;
	refrence.HumidityMin=p[0];
	refrence.TempMin=p[1];
	refrence.SoilMoistureMin=p[2];
	refrence.LightLevelMin=p[3];
	while(1){
		DIO_u8SetPinValue(u8FAN_PORT,u8FAN_PIN, DIO_u8PIN_HIGH);
		while(1)
		{
			
		}
		
		
		reading.Temp=  LM34_u8GetTempInC(ADC_u8SINGLE_ENDED_ADC0);
		reading.Level = LDR_u8GetLightLevel(ADC_u8SINGLE_ENDED_ADC1, 200);
		reading.Soil = SOIL_u16GetMoisture(ADC_u8SINGLE_ENDED_ADC2, 40);
		DHT_GetHumidity(&(reading.Humidity));
		voidSendData();
		CLCD_voidGoToXY(0,0);
		CLCD_u8SendString("T:");
		CLCD_u8SendNumber(reading.Temp);

		CLCD_voidGoToXY(9,0);
		CLCD_u8SendString("L:");
		CLCD_u8SendNumber(reading.Level);

		CLCD_voidGoToXY(0,1);
		CLCD_u8SendString("M:");
		CLCD_u8SendNumber(reading.Soil);
		CLCD_u8SendString("%");

		CLCD_voidGoToXY(9,1);
		CLCD_u8SendString("H:");
		CLCD_u8SendNumber(reading.Humidity);
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

	if(reading.Temp > refrence.TempMax){
		DIO_u8SetPinValue(u8FAN_PORT,u8FAN_PIN, DIO_u8PIN_HIGH);
		}else{
		DIO_u8SetPinValue(u8FAN_PORT,u8FAN_PIN, DIO_u8PIN_LOW);
	}

}

void voidHeater(void){

	if(reading.Temp < refrence.TempMin){
		DIO_u8SetPinValue(u8HEATER_PORT,u8HEATER_PIN, DIO_u8PIN_HIGH);
		}else{
		DIO_u8SetPinValue(u8HEATER_PORT,u8HEATER_PIN, DIO_u8PIN_LOW);
	}

}


void voidIrrigation(){

	if(reading.Soil < refrence.SoilMoistureMin){
		DIO_u8SetPinValue(u8IRRIGATION_PORT,u8IRRIGATION_PIN, DIO_u8PIN_HIGH);
		}else if(reading.Soil > refrence.SoilMoistureMax){
		DIO_u8SetPinValue(u8IRRIGATION_PORT,u8IRRIGATION_PIN, DIO_u8PIN_LOW);
	}
}


void voidLight(){

	if(reading.Level < refrence.LightLevelMin){
		DIO_u8SetPinValue(u8LIGHT_PORT,u8LIGHT_PIN, DIO_u8PIN_HIGH);
		}else if(reading.Level > refrence.LightLevelMax){
		DIO_u8SetPinValue(u8LIGHT_PORT,u8LIGHT_PIN, DIO_u8PIN_LOW);
	}

}


void voidAlert(){

	if(reading.Temp > refrence.TempMax || reading.Temp < refrence.TempMin){
		u8AlertCOD = u8TEMP_ALERT_COD;
		}else if(reading.Soil < refrence.SoilMoistureMin || reading.Soil > refrence.SoilMoistureMax){
		u8AlertCOD = u8MOISTURE_ALERT_COD;
		}else if(reading.Level < refrence.LightLevelMin ||  reading.Level > refrence.LightLevelMax){
		u8AlertCOD = u8LIGHT_ALERT_COD;
		}else if(reading.Humidity < refrence.HumidityMin || reading.Humidity > refrence.HumidityMax){
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

void voidSendData(){
	uint32 num=0;
	uint8 *p=&num;
	p[0]=reading.Humidity;
	p[1]=reading.Temp;
	p[2]=reading.Soil;
	p[3]=reading.Level;
	UART_voidSendNumber(num);
}
