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

#define TOMATOES_HUMIDITY		20
#define TOMATOES_TEMP			30
#define TOMATOES_SOIL_WATER		40
#define TOMATOES_LIGHT			50

#define CORN_HUMIDITY			20
#define CORN_TEMP				20
#define CORN_SOIL_WATER			20
#define CORN_LIGHT				20

#define WHEAT_HUMIDITY			20
#define WHEAT_TEMP				20
#define WHEAT_SOIL_WATER		20
#define WHEAT_LIGHT				20




plant_char_t  setPlantChar(plants_t plant);
plant_char_t  setCustom();

#endif /* PLANT_CHAR_H_ */