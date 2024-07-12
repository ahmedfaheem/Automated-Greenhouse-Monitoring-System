/*
 * APP_cfg.h
 *
 *  Created on: Jul 8, 2024
 *      Author: AHMED FAHEEM
 */

#ifndef APP_APP_CFG_H_
#define APP_APP_CFG_H_

#define u8FAN_PORT  DIO_u8PORTC
#define u8FAN_PIN   DIO_u8PIN0

#define u8HEATER_PORT  DIO_u8PORTC
#define u8HEATER_PIN   DIO_u8PIN1

#define u8IRRIGATION_PORT   DIO_u8PORTC
#define u8IRRIGATION_PIN   DIO_u8PIN2

#define u8LIGHT_PORT   DIO_u8PORTC
#define u8LIGHT_PIN    DIO_u8PIN3

#define u8BUZZER_PORT  DIO_u8PORTC
#define u8BUZZER_PIN   DIO_u8PIN4


#define u8TEMP_ALERT_COD   90u
#define u8MOISTURE_ALERT_COD   100u
#define u8LIGHT_ALERT_COD      110u
#define u8HUMIDITY_ALERT_COD      120u
#define u8NO_ALERT   0u


#endif /* APP_APP_CFG_H_ */
