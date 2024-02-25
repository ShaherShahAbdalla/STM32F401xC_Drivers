/******************************************************************************
 *
 * Module: SWITCH driver to initialize DIO pins for the connected Switches, and getting its state.
 *
 * File Name: SWITCH_cfg.h
 *
 * Description: Configuration file for SWITCH Driver.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 15-12-2023 (Edited for ARM at 21-02-2024)
 *
 *******************************************************************************/

#ifndef SWITCH_CFG_H_
#define SWITCH_CFG_H_

/****************************************************************************************/
/*							Configuration Macros Declaration							*/
/****************************************************************************************/

/* Description: Set the number of connected switches
 * Options:		for ATmega8:				0 ~ 23
 * 		or		for ATmega16 and ATmega32:	0 ~ 32
 * 		or		for ATmega64 and ATmega128:	0 ~ 53		*/
#define	NUM_OF_SWITCHES					2



/* Description: Define EACH of the connected switches and start giving them values in ascending order starting from ZERO
 * examples:	#define	START_MOTOR_SWITCH			0
 * 				#define SOMETHING_SWITCH			1
 * 	and so on ...										*/
#define	ON_SW							0
#define OFF_SW							1

#endif /* SWITCH_CFG_H_ */
