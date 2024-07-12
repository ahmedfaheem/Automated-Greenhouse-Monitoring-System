#ifndef DHT_INTERACE_H_
#define DHT_INTERACE_H_



#define DHT_PIN		DIO_u8PIN3
#define DHT_PORT	DIO_u8PORTA


enum DHT_Status_t
{
	DHT_Ok,
	DHT_Error_Humidity,
	DHT_Error_Temperature,
	DHT_Error_Checksum,
	DHT_Error_Timeout
};


/********************Prototypes****************************/
void DHT_Setup();
enum DHT_Status_t DHT_GetStatus();
enum DHT_Status_t DHT_GetTemperature(uint8 *Temperature);
enum DHT_Status_t DHT_GetHumidity(uint8 *Humidity);
enum DHT_Status_t DHT_Read(uint8 *Temperature, uint8 *Humidity);
enum DHT_Status_t DHT_ReadRaw(uint8 Data[4]);


/***********************************************************/
#endif
