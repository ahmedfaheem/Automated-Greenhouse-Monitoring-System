/*
* plant_char.h
*
* Created: 7/6/2024 1:21:27 AM
*  Author: khaled
*/


#ifndef PLANT_CHAR_H_
#define PLANT_CHAR_H_



typedef struct{
	u8 humidity;
	u8 temp;
	u8 soil_water;
	u8 light_intensity;
}plant_char_t;

typedef enum {
	tomatoes=1,corn,wheat,custom
}plants_t;
//MAX VALUES
#define TOMATOES_MAX_HUMIDITY		70
#define TOMATOES_MAX_TEMP		27
#define TOMATOES_MAX_SOIL_WATER		70
#define TOMATOES_MAX_LIGHT		80

#define CORN_MAX_HUMIDITY		60
#define CORN_MAX_TEMP			30
#define CORN_MAX_SOIL_WATER		60
#define CORN_MAX_LIGHT			75

#define WHEAT_MAX_HUMIDITY		70
#define WHEAT_MAX_TEMP			25
#define WHEAT_MAX_SOIL_WATER		40
#define WHEAT_MAX_LIGHT			80


//NIM VALUES
#define TOMATOES_MIN_HUMIDITY		60
#define TOMATOES_MIN_TEMP		21
#define TOMATOES_MIN_SOIL_WATER		50
#define TOMATOES_MIN_LIGHT		60

#define CORN_MIN_HUMIDITY		50
#define CORN_MIN_TEMP			24
#define CORN_MIN_SOIL_WATER		40
#define CORN_MIN_LIGHT			60

#define WHEAT_MIN_HUMIDITY		50
#define WHEAT_MIN_TEMP			10
#define WHEAT_MIN_SOIL_WATER		20
#define WHEAT_MIN_LIGHT			65




plant_char_t  setPlantMin(plants_t plant);
plant_char_t  setPlantMax(plants_t plant);
plant_char_t  setCustom();

#endif /* PLANT_CHAR_H_ */
