/******************************************************************************
 *
 * Module: LED driver to initialize DIO pins for the connected LEDs, Powering it ON and OFF.
 *
 * File Name: LED_cfg.h
 *
 * Description: Configuration file for LEDs Driver.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 11-12-2023 (Edited for ARM at 19-02-2024)
 *
 *******************************************************************************/

#ifndef LED_CFG_H_
#define LED_CFG_H_

/****************************************************************************************/
/*							Configuration Macros Declaration							*/
/****************************************************************************************/

/* Description: Set the number of connected LEDs
 * Options:		for ATmega8:				0 ~ 23
 * 		or		for ATmega16 and ATmega32:	0 ~ 32
 * 		or		for ATmega64 and ATmega128:	0 ~ 53		*/
#define	NUM_OF_LEDS					1

/* Description: Define EACH of the connected LEDs and start giving them values in ascending order starting from ZERO
 * examples:	#define	START_LED			0
 * 				#define SOMETHING_LED		1
 * 	and so on											*/
#define ALARM_LED			0

#endif /* LED_CFG_H_ */
