#ifndef SOIL_INTERFACE_H
#define SOIL_INTERFACE_H

/*
 * the function has delay inside to get average reading,
 * you can configure the delay for CFG file
 */
uint16 SOIL_u16GetMoisture(uint16 Copy_u8ACD_Ch, uint8 Copy_u8Reading_num);
#endif
