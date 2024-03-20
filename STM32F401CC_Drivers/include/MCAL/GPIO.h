/******************************************************************************
*
* Module: GPIO Driver.
*
* File Name: GPIO_interface.h
*
* Description: Driver's APIs' prototypes and typedefs' declaration.
*
* Author: Shaher Shah Abdalla Kamal
*
* Date:	19-02-2024
*
*******************************************************************************/

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_




/****************************************************************************************/
/*										Includes										*/
/****************************************************************************************/
/* ِIncluding the .h file that contains typedefs for the primitive data types */
#include <LIB/std_types.h>



/****************************************************************************************/
/*									Macros Declaration									*/
/****************************************************************************************/


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


/* Speed options */

#define GPIO_SPEED_LOW					(0UL)
#define GPIO_SPEED_MEDIUM				(1UL)
#define GPIO_SPEED_HIGH					(2UL)
#define GPIO_SPEED_VERY_HIGH			(3UL)
/****************************************************************************************/


/* Direction Mode options */
/* From the right, first two bits are for the PUPDR, third bit is for OTYPER and the Fourth
 * and the Fifth bit are for the MODER */

#define GPIO_MODE_INPUT_FLOAT			(0b00000UL)
#define GPIO_MODE_INPUT_PU				(0b00001UL)
#define GPIO_MODE_INPUT_PD				(0b00010UL)

#define GPIO_MODE_OUTPUT_PP				(0b01000UL)
#define GPIO_MODE_OUTPUT_PP_PU			(0b01001UL)
#define GPIO_MODE_OUTPUT_PP_PD			(0b01010UL)
#define GPIO_MODE_OUTPUT_OD				(0b01100UL)
#define GPIO_MODE_OUTPUT_OD_PU			(0b01101UL)
#define GPIO_MODE_OUTPUT_OD_PD			(0b01110UL)

#define GPIO_MODE_AF_PP					(0b10000UL)
#define GPIO_MODE_AF_PP_PU				(0b10001UL)
#define GPIO_MODE_AF_PP_PD				(0b10010UL)
#define GPIO_MODE_AF_OD					(0b10100UL)
#define GPIO_MODE_AF_OD_PU				(0b10101UL)
#define GPIO_MODE_AF_OD_PD				(0b10110UL)

#define GPIO_MODE_ANALOG				(0b11000UL)
/****************************************************************************************/


/* Alternate functions value options */

#define	GPIO_AF0				(0UL)
#define GPIO_AF1				(1UL)
#define	GPIO_AF2				(2UL)
#define GPIO_AF3				(3UL)
#define	GPIO_AF4				(4UL)
#define GPIO_AF5				(5UL)
#define	GPIO_AF6				(6UL)
#define GPIO_AF7				(7UL)
#define	GPIO_AF8				(8UL)
#define GPIO_AF9				(9UL)
#define	GPIO_AF10				(10UL)
#define GPIO_AF11				(11UL)
#define	GPIO_AF12				(12UL)
#define GPIO_AF13				(13UL)
#define GPIO_AF14				(14UL)
#define GPIO_AF15				(15UL)
/****************************************************************************************/


/* Pins' value options */

#define	GPIO_PIN_VAL_LOW				(0UL)
#define GPIO_PIN_VAL_HIGH				(1UL)
/****************************************************************************************/



/****************************************************************************************/
/*								User-defined types Declaration							*/
/****************************************************************************************/


/**
 *@brief : The Error List Type
 */
typedef enum
{
	/**
	 *@brief : Everything OK, function had Performed Correctly.
	 */
	GPIO_enuOk = 0,
	/**
	 *@brief : Something went wrong in the function.
	 */
	GPIO_enuNotOk,
	/**
	 *@brief : Null pointer is passed to a function as an argument.
	 */
	GPIO_enuNullPointer
}GPIO_enuErrorStatus_t;


/* Structure that will be passed by address to GPIO_enuInitPin function to set a pin's configuration */
typedef struct {
	uint32_t GPIO_port;
	uint32_t GPIO_pin;
	uint32_t GPIO_speed;
	uint32_t GPIO_mode;
}GPIO_strPinConfig_t;



/****************************************************************************************/
/*									Functions' Declaration								*/
/****************************************************************************************/


/**
 *@brief : Function to Configure the GPIO' pins.
 *@param : Address of the structure that contains port number, pin number, speed and direction mode.
 *@return: Error status.
 */
GPIO_enuErrorStatus_t GPIO_enuInitPin(GPIO_strPinConfig_t* Add_strPinConfig);


/**
 *@brief : Function to Configure the GPIO' pins to an alternate function.
 *@param : 	Address of the structure that contains port number, pin number, speed and direction mode.
 *@param 	alternate function choice. options: GPIO_AF0 ~ GPIO_AF15.
 *@return: Error status.
 */
GPIO_enuErrorStatus_t GPIO_enuInitPinAlterFun(GPIO_strPinConfig_t* Add_strPinConfig, uint32_t Copy_u32AFx);


/**
 *@brief  : Function to Set a pin's value to be Logic HIGH  or Logic LOW.
 *@param  : Port Number, Pin Number, Pin's value (HIGH/LOW).
 *@return : Error status.
 */
GPIO_enuErrorStatus_t GPIO_enuSetPinVal(uint32_t Copy_u32PortNum, uint32_t Copy_u32PinNum,\
										uint32_t Copy_u32PinVal);

/**
 *@brief  : Function to Read the Logic State of the Pin (Is it HIGH or LOW).
 *@param  : Port Number,Pin Number, Pointer to return the value of pin state.
 *@return : Error status.
 */
GPIO_enuErrorStatus_t GPIO_enuGetPinVal(uint32_t Copy_u32PortNum, uint32_t Copy_u32PinNum,\
										uint32_t* Add_Pu32PinVal);



#endif /* GPIO_INTERFACE_H_ */
