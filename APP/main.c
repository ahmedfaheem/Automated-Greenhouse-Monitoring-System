#include "..\Library\STD_TYPES.h"
#include "..\Library\BIT_MATH.h"
#include "..\MCAL\DIO\DIO_interface.h"
#define   F_CPU	16000000UL
#include <util/delay.h>
#include "..\MCAL\PORT\PORT_interface.h"
#include "..\MCAL\GIE\GIE_interface.h"
#include "..\MCAL\EXTI\EXTI_interface.h"
#include "..\MCAL\ADC\ADC_interface.h"
#include "..\HAL\LDR\LDR_interface.h"
#include "..\HAL\LED\LED_interface.h"
#include "..\HAL\MOTOR\MOTOR_interface.h"
#include "..\HAL\Soil_Moisture\SOIL_interface.h"
#include "..\HAL\DHT11\DH_Interface.h"
#include  "APP_cfg.h"
#include "..\MCAL\USART\USART_interface.h"
#include "..\MCAL\TIMER\TIMER_interface.h"
#include "..\SERVICES\PWM\PWM_interface.h"

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
void RX_INT();
static uint8 constrain(uint16 value, uint16 min, uint16  max);
static _sUser_cfg_t reference={0,255,0,255,0,255,0,255};
static sReading_t     reading;
static uint8  u8AlertCOD = u8NO_ALERT;

void main(){
	PORT_voidInit();
	ADC_voidInit();
	DHT_Setup();
	USART_voidInit();
	GIE_voidEnableGlobal();
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(RX_INT);

	void voidLight() {
		uint8 onTime;
		if (reading.Level < reference.LightLevelMin) {
			onTime=10;
			
			} else if (reading.Level > reference.LightLevelMax) {
			onTime=0;
			} else {
			// Calculate proportional light level
			uint16 range = reference.LightLevelMax - reference.LightLevelMin;
			uint16 adjustedLevel = reading.Level - reference.LightLevelMin;
			onTime = (10 * (range - adjustedLevel)) / range;
			
		}
		onTime = constrain(onTime, 0, 10);
		PWM_u8Set(10, onTime);
		
	}

	


	while(1){
		reading.Level = LDR_u8GetLightLevel(ADC_u8SINGLE_ENDED_ADC1, 100);
		reading.Soil = SOIL_u16GetMoisture(ADC_u8SINGLE_ENDED_ADC2, 40);
		DHT_Read(&(reading.Temp),&(reading.Humidity));
		voidSendData();
		
		voidFan();
		voidHeater();
		voidIrrigation();
		voidLight();
		voidAlert();


		


	}


}

void voidFan(void){

	if(reading.Temp > reference.TempMax){
		DIO_u8SetPinValue(u8FAN_PORT,u8FAN_PIN, DIO_u8PIN_HIGH);
		}else{
		DIO_u8SetPinValue(u8FAN_PORT,u8FAN_PIN, DIO_u8PIN_LOW);
	}

}

void voidHeater(void){

	if(reading.Temp < reference.TempMin){
		DIO_u8SetPinValue(u8HEATER_PORT,u8HEATER_PIN, DIO_u8PIN_HIGH);
		}else{
		DIO_u8SetPinValue(u8HEATER_PORT,u8HEATER_PIN, DIO_u8PIN_LOW);
	}

}


void voidIrrigation(){

	if(reading.Soil < reference.SoilMoistureMin){
		DIO_u8SetPinValue(u8IRRIGATION_PORT,u8IRRIGATION_PIN, DIO_u8PIN_HIGH);
		}else if(reading.Soil > reference.SoilMoistureMax){
		DIO_u8SetPinValue(u8IRRIGATION_PORT,u8IRRIGATION_PIN, DIO_u8PIN_LOW);
	}
}

static uint8 constrain(uint16 value, uint16 min, uint16  max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

void voidLight() {
	uint16 onTime;
	if (reading.Level < reference.LightLevelMin) {
		onTime=1000;
		
		} else if (reading.Level > reference.LightLevelMax) {
		onTime=0;
		} else {
		// Calculate proportional light level
		uint16 range = reference.LightLevelMax - reference.LightLevelMin;
		uint16 adjustedLevel = reading.Level - reference.LightLevelMin;
		onTime = (1000 * (range - adjustedLevel)) / range;
		
	}
	onTime = constrain(onTime, 0, 1000);
	PWM_u8Set(1000, onTime);
	
}

void voidAlert(){

	if(reading.Temp > reference.TempMax || reading.Temp < reference.TempMin){
		u8AlertCOD = u8TEMP_ALERT_COD;
		}else if(reading.Soil < reference.SoilMoistureMin || reading.Soil > reference.SoilMoistureMax){
		u8AlertCOD = u8MOISTURE_ALERT_COD;
		}else if(reading.Level < reference.LightLevelMin ||  reading.Level > reference.LightLevelMax){
		u8AlertCOD = u8LIGHT_ALERT_COD;
		}else if(reading.Humidity < reference.HumidityMin || reading.Humidity > reference.HumidityMax){
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


void RX_INT()
{
	uint32 num1,num2;
	uint8 *p;
	num1 = UART_u32ReceiveNumber();
	num2 = UART_u32ReceiveNumber();
	p=&num1;
	reference.HumidityMax=p[0];
	reference.TempMax=p[1];
	reference.SoilMoistureMax=p[2];
	reference.LightLevelMax=p[3];

	p=&num2;
	reference.HumidityMin=p[0];
	reference.TempMin=p[1];
	reference.SoilMoistureMin=p[2];
	reference.LightLevelMin=p[3];
}