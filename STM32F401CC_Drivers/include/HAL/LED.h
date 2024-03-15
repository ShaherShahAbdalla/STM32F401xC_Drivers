/******************************************************************************
 *
 * Module: LED driver to initialize DIO pins for the connected LEDs, Powering it ON and OFF.
 *
 * File Name: LED.h
 *
 * Description: Driver's APIs' prototypes and typedefs' declaration.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 11-12-2023 (Edited for ARM at 19-02-2024)
 *
 *******************************************************************************/

#ifndef LED_H_
#define LED_H_

/* ِIncluding the .h file that contains typedefs for the primitive data types */
#include <CFG/LED_cfg.h>
#include <LIB/std_types.h>


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
	LED_enuOk = 0,
	/**
	 *@brief : Something is wrong, Function hadn't Performed Correctly.
	 */
	LED_enuNotOk,
	/**
	 *@brief : NULL Pointer is passed.
	 */
	LED_enuNullPointer,
	/**
	 *@brief : .
	 */
	LED_enuWrongActiveState,
	/**
	 *@brief : .
	 */
	LED_enuWrongPowerState

}LED_enuErrorStatus_t;

/**
 *@brief : Active State type
 */
typedef enum
{
	/**
	 *@brief : LED is connected with active low mode, it needs 0 volt / (LOW) to be powered ON.
	 */
	LED_enuActiveLow = 0,
	/**
	 *@brief : LED is connected with active high mode, it needs 3.3 or 5 volt / (high) to be powered ON.
	 */
	LED_enuActiveHigh

}LED_enuConnectionType_t;

/**
 *@brief : LED State type
 */
typedef enum
{
	/**
	 *@brief : LED is powered OFF.
	 */
	LED_enuOFF = 0,
	/**
	 *@brief : LED is powered ON.
	 */
	LED_enuON

}LED_enuInitState_t;


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


/* Structure that will be passed by address to LED_enuInit function to set the configuration of a LED */
typedef struct {
	uint32_t LED_port_number;
	uint32_t LED_pin_number;
	LED_enuConnectionType_t connection_type;
	LED_enuInitState_t init_state;
}LED_strLEDconfig_t;

/********************************************************************************************/
/*									Functions' Declaration									*/
/********************************************************************************************/

/**
 *@brief : Function to Set the pins to which the LEDs is connected to.
 *@param : void.
 *@return: Error State.
 */
LED_enuErrorStatus_t LED_enuInit(void);

/**
 *@brief : Function to power ON the entered LED.
 *@param : Name of the LED you want to power it ON.
 *@return: Error Status.
 */
LED_enuErrorStatus_t LED_enuPowerON(uint8_t copy_LEDname);

/**
 *@brief : Function to power OFF the entered LED.
 *@param : Name of the LED you want to power it OFF.
 *@return: Error Status.
 */
LED_enuErrorStatus_t LED_enuPowerOFF(uint8_t copy_LEDname);


#endif /* LED_H_ */
