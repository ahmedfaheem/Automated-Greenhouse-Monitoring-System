
#include "StdTypes.h"
#include "MemMap.h"
#include "ADC_Int.h"
#define  F_CPU   8000000
#include <util/delay.h>

static u8 Conversionflag=0;

void ADC_Init(ADC_VREF_t vref,ADC_Prescaler_t scaler)
{
	/* vref*/
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_VCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	/*prescaler*/
	ADCSRA=ADCSRA&0xf8;//0b11111000
	ADCSRA=ADCSRA|scaler;
	/*pins*/
	/*enable ADC*/
	SET_BIT(ADCSRA,ADEN);
	
}

u16 ADC_Read(ADC_Channel_t ch)
{
	/*select channel*/
	ADMUX=ADMUX&0XE0;//0b11100000
	ADMUX=ADMUX|ch;
	/*start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*wait until conversion end*/
	while(GET_BIT(ADCSRA,ADSC));
	
	/* get reading*/
	//adc=ADCH<<8|ADCL;
	return ADC;
}

void ADC_StartConversion(ADC_Channel_t ch)
{
	if (Conversionflag==0)
	{
		/*select channel*/
		ADMUX=ADMUX&0XE0;//0b11100000
		ADMUX=ADMUX|ch;
		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);
		Conversionflag=1;
	}
	
}

u16 ADC_GetRead(void)
{
	/*wait until conversion end*/
	while(GET_BIT(ADCSRA,ADSC));
		/* get reading*/
		//adc=ADCH<<8|ADCL;
		return ADC;
}

error_t ADC_GetReadPerodic(u16*pdata)
{
	if (!GET_BIT(ADCSRA,ADSC))
	{
		*pdata=ADC;
		Conversionflag=0;
		return OK;
	}
	return INPROGRESS;
}




u16 ADC_ReadVolt(ADC_Channel_t ch)
{
	u16 adc=ADC_Read(ch);
	u16 volt;
	volt=((u32)5000*adc)/1023;
	return volt;	
}

u16 ADC_GetReadNoBlock(void)
{

	/* get reading*/
	//adc=ADCH<<8|ADCL;
	return ADC;
}