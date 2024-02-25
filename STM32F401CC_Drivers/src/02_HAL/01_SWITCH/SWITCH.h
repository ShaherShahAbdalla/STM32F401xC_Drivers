/******************************************************************************
 *
 * Module: SWITCH driver to initialize DIO pins for the connected Switches, and getting its state.
 *
 * File Name: SWITCH.h
 *
 * Description: Driver's APIs' prototypes and typedefs' declaration.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 15-12-2023 (Edited for ARM at 21-02-2024)
 *
 *******************************************************************************/

#ifndef SWITCH_H_
#define SWITCH_H_

/* ِIncluding the .h file that contains typedefs for the primitive data types */
#include "../../00_LIB/std_types.h"

/* ِIncluding the .h file that contains all configurations */
#include "./SWITCH_cfg.h"

/****************************************************************************************/
/*								User-defined Declaration								*/
/****************************************************************************************/

/**
 *@brief : The Error List Type
 */
typedef enum
{
	/**
	 *@brief : Everything OK, Function had Performed Correctly.
	 */
	SWITCH_enuOk = 0,
	/**
	 *@brief : Something is wrong, Function hadn't Performed Correctly.
	 */
	SWITCH_enuNotOk,
	/**
	 *@brief : NULL Pointer is passed.
	 */
	SWITCH_enuNullPointer,
	/**
	 *@brief : Wrong Connection Method is entered.
	 */
	SWITCH_enuWrongConnectionMethod,
	/**
	 *@brief : Wrong Switch Name is entered.
	 */
	SWITCH_enuWrongSwitchName

}SWITCH_enuErrorStatus_t;

/**
 *@brief :	Connection method of the switch
 */
typedef enum
{
	/**
	 *@brief : Switch is connected with Internal pull-up method.
	 */
	SWITCH_enuInternalPullUpConnection = 0,
	/**
	 *@brief : Switch is connected with External pull-up method.
	 */
	SWITCH_enuExternalPullUpConnection,
	/**
	 *@brief : Switch is connected with Internal pull-down method.
	 */
	SWITCH_enuInternalPullDownConnection,
	/**
	 *@brief : Switch is connected with External pull-down method.
	 */
	SWITCH_enuExternalPullDownConnection

}SWITCH_enuConnectionMethod_t;

/**
 *@brief :	State of the switch, whether pressed or not
 */
typedef enum
{
	/**
	 *@brief : Switch is not pressed.
	 */
	SWITCH_enuNOT_PRESSED = 0,
	/**
	 *@brief : Switch is pressed.
	 */
	SWITCH_enuIS_PRESSED

}SWITCH_enuSwitchState_t;


/* GPIO ports */

#define GPIO_PORTA						(0x40020000UL)	/* 	GPIOA Base Address			*/
#define GPIO_PORTB						(0x40020400UL)	/* 	GPIOB Base Address			*/
#define GPIO_PORTC						(0x40020800UL)	/* 	GPIOC Base Address			*/
#define GPIO_PORTD						(0x40020C00UL)	/* 	GPIOD Base Address			*/
#define GPIO_PORTE						(0x40021000UL)	/* 	GPIOE Base Address			*/
#define GPIO_PORTH						(0x40021C00UL)	/* 	GPIOH Base Address			*/
/****************************************************************************************/


/* GPIO port's pins */

#define GPIO_PIN0						(0UL)
#define GPIO_PIN1						(1UL)
#define GPIO_PIN2						(2UL)
#define GPIO_PIN3						(3UL)
#define GPIO_PIN4						(4UL)
#define GPIO_PIN5						(5UL)
#define GPIO_PIN6						(6UL)
#define GPIO_PIN7						(7UL)
#define GPIO_PIN8						(8UL)
#define GPIO_PIN9						(9UL)
#define GPIO_PIN10						(10UL)
#define GPIO_PIN11						(11UL)
#define GPIO_PIN12						(12UL)
#define GPIO_PIN13						(13UL)
#define GPIO_PIN14						(14UL)
#define GPIO_PIN15						(15UL)
/****************************************************************************************/


/* Structure that will be passed by address to SWITCH_enumInit function to set the configuration of a Switch */
typedef struct {
	uint32_t SW_port_number;
	uint32_t SW_pin_number;
	SWITCH_enuConnectionMethod_t SW_connection_method;
}SWITCH_strSwitchConfig_t;

/********************************************************************************************/
/*									Functions' Declaration									*/
/********************************************************************************************/

/**
 *@brief : Function to Set the pins to which the switches are connected to.
 *@param : void.
 *@return: Error Status.
 */
SWITCH_enuErrorStatus_t SWITCH_enuInit(void);

/**
 *@brief : Function to check if the switch is pressed or not.
 *@param : Name of the switch you want to check, address of a local variable to assign state of the switch in it.
 *@return: Error Status.
 */
SWITCH_enuErrorStatus_t SWITCH_enuGetSwitchState(uint8_t copy_uint8SwitchName, SWITCH_enuSwitchState_t* Add_enuSwitchState);

#endif /* SWITCH_H_ */
