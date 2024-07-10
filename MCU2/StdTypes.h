

#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char   u8;


typedef enum{
	OK,
	NOK,
	INPROGRESS,
	NULL_PTR,
	OUT_OF_RANGE
	}error_t;

#define SET_BIT(value,bite)   (value=value|(1<<bite))

#endif /* STDTYPES_H_ */