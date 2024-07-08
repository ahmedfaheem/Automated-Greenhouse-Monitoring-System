#include "../../Library/STD_TYPES.h"
#include "../../MCAL/5- ADC/ADC_interface.h"
#include <util/delay.h>
#include "SOIL_interface.h"
#include "SOIL_cfg.h"
#include "SOIL_prv.h"



uint16 SOIL_u16GetMoisture(uint16 Copy_u8ACD_Ch, uint8 Copy_u8Reading_num){

	uint16 Local_u16Reading = 0, Local_u16ADCVal = 0, Local_u16Sum =0;
	uint8 Local_u8Counter = 0;

	for(Local_u8Counter = 0;Local_u8Counter< Copy_u8Reading_num;Local_u8Counter++){

		ADC_u8StartSingleConversionSynch(Copy_u8ACD_Ch, &Local_u16ADCVal);

#if  SOIL_ADC_MODE == SOIL_8BIT_MODE

		Local_u16Sum  += ((Local_u16ADCVal * 100UL)/255UL);


#elif SOIL_ADC_MODE  == SOIL_10BIT_MODE

		Local_u16Sum  = ((Local_u16ADCVal * 100UL)/1023UL);

#else

#error   Erro on congfiguration

#endif

		_delay_ms(SOIL_READING_DELAY);

	}

	Local_u16Reading = Local_u16Sum/Copy_u8Reading_num;

	return Local_u16Reading;

}

