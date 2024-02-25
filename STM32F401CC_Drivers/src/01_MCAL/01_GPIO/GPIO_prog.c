/******************************************************************************
*
* Module: GPIO Driver
*
* File Name: GPIO_prog.c
*
* Description: Driver's APIs' Implementation and typedefs' declaration.
*
* Author: Shaher Shah Abdalla Kamal
*
* Date: 19-02-2024
*
*******************************************************************************/



/****************************************************************************************/
/*										Includes										*/
/****************************************************************************************/


#include "./GPIO_interface.h"



/****************************************************************************************/
/*									Macros Declaration									*/
/****************************************************************************************/


/* Set Masks */


/* From the right (LSB), first two bits are for the PUPDR, third bit is for OTYPER and the Fourth
 * and the Fifth bit are for the MODER */


#define MODER_Y_SET_MASK					(0x3UL)		/*	Mask for MODERy bits		*/
#define SHAHER_MODER_BITS_MASK				(0b11000UL)
/* Shifting the MODER bits in my mask to be the LSB */
#define SHAHER_MODER_BITS_SHIFT				(3UL)


#define NUM_OF_PIN_S_MODER_BITS				(2UL)
#define NUM_OF_PIN_S_PUPDR_BITS				(2UL)
#define NUM_OF_PIN_S_OSPEEDER_BITS			(2UL)
#define NUM_OF_PIN_S_AFRX_BITS				(4UL)


#define OTYPER_Y_SET_MASK					(0x1UL)		/*	Mask for OTy bits			*/
#define SHAHER_OTYPER_BIT_MASK				(0b00100UL)
/* Shifting the OTYPER bits in my mask to be the LSB */
#define SHAHER_OTYPER_BIT_SHIFT				(2UL)


#define PUPDR_Y_SET_MASK					(0x3UL)		/*	Mask for PUPDRy bits		*/
#define SHAHER_PUPDR_BITS_MASK				(0b00011UL)


#define OSPEEDR_Y_SET_MASK					(0x3UL)		/*	Mask for OSPEEDRy bits		*/

#define AFRX_Y_SET_MASK						(0xFUL)		/*	Mask for AFRxy bits			*/

#define ODR_Y_SET_MASK						(0x1UL)		/*	Mask for ODRy bits			*/
#define BSRR_Y_SET_MASK						(0x1UL)		/*	Mask for BSRRy bits			*/

#define LCKR_Y_SET_MASK						(0x1UL)		/*	Mask for LCKRy bits			*/
/****************************************************************************************/


#define NUM_OF_PORT_S_PINS					(16UL)



/****************************************************************************************/
/*								User-defined types Declaration							*/
/****************************************************************************************/


typedef struct{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
}GPIO_strRegsiters_t;



/****************************************************************************************/
/*									Variables's Declaration								*/
/****************************************************************************************/



/****************************************************************************************/
/*								Static Functions' Declaration							*/
/****************************************************************************************/







/****************************************************************************************/
/*								Functions' Implementation								*/
/****************************************************************************************/


/**
 *@brief : Function to Configure the GPIO' pins.
 *@param : Address of the structure that contains port number, pin number, speed and direction mode.
 *@return: Error status.
 */
GPIO_enuErrorStatus_t GPIO_enuInitPin(GPIO_strPinConfig_t* Add_strPinConfig)
{
	GPIO_enuErrorStatus_t LOC_enuErrorStatus = GPIO_enuOk;

	/* First, check that the passed pointer is not a NULL pointer */
	if (Add_strPinConfig == NULL_PTR)
	{
		/* The passed pointer is a NULL pointer, We cannot access it, return error */
		LOC_enuErrorStatus = GPIO_enuNotOk;
	}
	else
	{
		/* The passed pointer is not pointing to NULL, so We can access it */

		/* We should check on the passed parameters that it is in the range */
		if (((Add_strPinConfig->GPIO_port >= GPIO_PORTA) && (Add_strPinConfig->GPIO_port <= GPIO_PORTH))\
				/* The compiler will generate the following warning:
				 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
				 * ignore it */
			&& ((Add_strPinConfig->GPIO_pin >= GPIO_PIN0) && (Add_strPinConfig->GPIO_pin <= GPIO_PIN15))\
			/* The compiler will generate the following warning:
			 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
			 * ignore it */
			&& ((Add_strPinConfig->GPIO_speed >= GPIO_SPEED_LOW) && (Add_strPinConfig->GPIO_speed <= GPIO_SPEED_VERY_HIGH))\
			/* The compiler will generate the following warning:
			 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
			 * ignore it */
			&& ((Add_strPinConfig->GPIO_mode >= GPIO_MODE_INPUT_FLOAT) && (Add_strPinConfig->GPIO_mode <= GPIO_MODE_ANALOG)))
		{
			/* Seems that all the parameters are passed correctly in the range, let's assign */

			/* Create a local variable as an image of the real register */
			uint32_t LOC_u32LocMODER = ((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->MODER;
			uint32_t LOC_u32LocOTYPER = ((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->OTYPER;
			uint32_t LOC_u32LocPUPDR = ((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->PUPDR;
			uint32_t LOC_u32LocOSPEEDR = ((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->OSPEEDR;

			/* First step is to assign the passed mode in the MODER register */

			/* Clean the bits before assigning in it */
			LOC_u32LocMODER &= ~(MODER_Y_SET_MASK << (NUM_OF_PIN_S_MODER_BITS * Add_strPinConfig->GPIO_pin));

			/* Assign the passed values in the local variable */
			LOC_u32LocMODER |= (((Add_strPinConfig->GPIO_mode & SHAHER_MODER_BITS_MASK) >> SHAHER_MODER_BITS_SHIFT) << (NUM_OF_PIN_S_MODER_BITS * Add_strPinConfig->GPIO_pin));

			/* As We finish the configurations, We can assign directly in the
			 * real register */
			((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->MODER = LOC_u32LocMODER;


			/* Second step is to assign the passed Type in the OTYPER register */
			/* Clean the bits before assigning in it */
			LOC_u32LocOTYPER &= ~(OTYPER_Y_SET_MASK << (Add_strPinConfig->GPIO_pin));

			/* Assign the passed values in the local variable */
			LOC_u32LocOTYPER |= (((Add_strPinConfig->GPIO_mode & SHAHER_OTYPER_BIT_MASK) >> SHAHER_OTYPER_BIT_SHIFT) << (Add_strPinConfig->GPIO_pin));

			/* As We finish the configurations, We can assign directly in the
			 * real register */
			((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->OTYPER = LOC_u32LocOTYPER;


			/* Third step is to assign the passed PUPDR choice in the PUPDR register */
			/* Clean the bits before assigning in it */
			LOC_u32LocPUPDR &= ~(PUPDR_Y_SET_MASK << (NUM_OF_PIN_S_PUPDR_BITS * Add_strPinConfig->GPIO_pin));

			/* Assign the passed values in the local variable */
			LOC_u32LocPUPDR |= ((Add_strPinConfig->GPIO_mode & SHAHER_PUPDR_BITS_MASK) << (NUM_OF_PIN_S_PUPDR_BITS * Add_strPinConfig->GPIO_pin));

			/* As We finish the configurations, We can assign directly in the
			 * real register */
			((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->PUPDR = LOC_u32LocPUPDR;


			/* Fourth step is to assign the passed speed choice in the OSPEEDR register */
			/* Clean the bits before assigning in it */
			LOC_u32LocOSPEEDR &= ~(OSPEEDR_Y_SET_MASK << (NUM_OF_PIN_S_OSPEEDER_BITS * Add_strPinConfig->GPIO_pin));

			/* Assign the passed values in the local variable */
			LOC_u32LocOSPEEDR |= ((Add_strPinConfig->GPIO_speed) << (NUM_OF_PIN_S_OSPEEDER_BITS * Add_strPinConfig->GPIO_pin));

			/* As We finish the configurations, We can assign directly in the
			 * real register */
			((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->OSPEEDR = LOC_u32LocOSPEEDR;
		}
		else
		{
			/* Seems that one or more input parameter is not in the specified range, return error */
			LOC_enuErrorStatus = GPIO_enuNotOk;
		}
	}

	return LOC_enuErrorStatus;
}



/**
 *@brief : Function to Configure the GPIO' pins to an alternate function.
 *@param : 	Address of the structure that contains port number, pin number, speed and direction mode.
 *@param 	alternate function choice. options: GPIO_AF0 ~ GPIO_AF15.
 *@return: Error status.
 */
GPIO_enuErrorStatus_t GPIO_enuInitPinAlterFun(GPIO_strPinConfig_t* Add_strPinConfig, uint32_t Copy_u32AFx)
{
	GPIO_enuErrorStatus_t LOC_enuErrorStatus = GPIO_enuOk;

	/* First, check that the passed pointer is not a NULL pointer */
	if (Add_strPinConfig == NULL_PTR)
	{
		/* The passed pointer is a NULL pointer, We cannot access it, return error */
		LOC_enuErrorStatus = GPIO_enuNotOk;
	}
	else
	{
		/* The passed pointer is not pointing to NULL, so We can access it */

		/* We should check on the passed parameters that it is in the range */
		if (((Add_strPinConfig->GPIO_port >= GPIO_PORTA) && (Add_strPinConfig->GPIO_port <= GPIO_PORTH))\
				/* The compiler will generate the following warning:
				 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
				 * ignore it */
			&& ((Add_strPinConfig->GPIO_pin >= GPIO_PIN0) && (Add_strPinConfig->GPIO_pin <= GPIO_PIN15))\
			/* The compiler will generate the following warning:
			 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
			 * ignore it */
			&& ((Add_strPinConfig->GPIO_speed >= GPIO_SPEED_LOW) && (Add_strPinConfig->GPIO_speed <= GPIO_SPEED_VERY_HIGH))\
			&& ((Add_strPinConfig->GPIO_mode >= GPIO_MODE_AF_PP) && (Add_strPinConfig->GPIO_mode <= GPIO_MODE_AF_OD_PD))\
			/* The compiler will generate the following warning:
			 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
			 * ignore it */
			&& ((Copy_u32AFx >= GPIO_AF0) && (Copy_u32AFx <= GPIO_AF15)))
		{
			/* Seems that all the parameters are passed correctly in the range, let's assign */

			/* Create a local variable as an image of the real register */
			uint32_t LOC_u32LocMODER = ((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->MODER;
			uint32_t LOC_u32LocOTYPER = ((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->OTYPER;
			uint32_t LOC_u32LocPUPDR = ((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->PUPDR;
			uint32_t LOC_u32LocOSPEEDR = ((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->OSPEEDR;

			/* First step is to assign the passed mode in the MODER register */

			/* Clean the bits before assigning in it */
			LOC_u32LocMODER &= ~(MODER_Y_SET_MASK << (NUM_OF_PIN_S_MODER_BITS * Add_strPinConfig->GPIO_pin));

			/* Assign the passed values in the local variable */
			LOC_u32LocMODER |= (((Add_strPinConfig->GPIO_mode & SHAHER_MODER_BITS_MASK) >> SHAHER_MODER_BITS_SHIFT) << (NUM_OF_PIN_S_MODER_BITS * Add_strPinConfig->GPIO_pin));

			/* As We finish the configurations, We can assign directly in the
			 * real register */
			((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->MODER = LOC_u32LocMODER;


			/* Second step is to assign the passed Type in the OTYPER register */
			/* Clean the bits before assigning in it */
			LOC_u32LocOTYPER &= ~(OTYPER_Y_SET_MASK << (Add_strPinConfig->GPIO_pin));

			/* Assign the passed values in the local variable */
			LOC_u32LocOTYPER |= (((Add_strPinConfig->GPIO_mode & SHAHER_OTYPER_BIT_MASK) >> SHAHER_OTYPER_BIT_SHIFT) << (Add_strPinConfig->GPIO_pin));

			/* As We finish the configurations, We can assign directly in the
			 * real register */
			((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->OTYPER = LOC_u32LocOTYPER;


			/* Third step is to assign the passed PUPDR choice in the PUPDR register */
			/* Clean the bits before assigning in it */
			LOC_u32LocPUPDR &= ~(PUPDR_Y_SET_MASK << (NUM_OF_PIN_S_PUPDR_BITS * Add_strPinConfig->GPIO_pin));

			/* Assign the passed values in the local variable */
			LOC_u32LocPUPDR |= ((Add_strPinConfig->GPIO_mode & SHAHER_PUPDR_BITS_MASK) << (NUM_OF_PIN_S_PUPDR_BITS * Add_strPinConfig->GPIO_pin));

			/* As We finish the configurations, We can assign directly in the
			 * real register */
			((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->PUPDR = LOC_u32LocPUPDR;


			/* Fourth step is to assign the passed speed choice in the OSPEEDR register */
			/* Clean the bits before assigning in it */
			LOC_u32LocOSPEEDR &= ~(OSPEEDR_Y_SET_MASK << (NUM_OF_PIN_S_OSPEEDER_BITS * Add_strPinConfig->GPIO_pin));

			/* Assign the passed values in the local variable */
			LOC_u32LocOSPEEDR |= ((Add_strPinConfig->GPIO_speed) << (NUM_OF_PIN_S_OSPEEDER_BITS * Add_strPinConfig->GPIO_pin));

			/* As We finish the configurations, We can assign directly in the
			 * real register */
			((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->OSPEEDR = LOC_u32LocOSPEEDR;

			/* Final step is to assign the passed alternate function choice in the AFxy register */
			if(Add_strPinConfig->GPIO_pin <= GPIO_PIN7)
			{
				/* Create a local variable as an image of the real register */
				uint32_t LOC_u32LocAFL = ((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->AFRL;

				/* Clean the bits before assigning in it */
				LOC_u32LocAFL &= ~(AFRX_Y_SET_MASK << (NUM_OF_PIN_S_AFRX_BITS * Add_strPinConfig->GPIO_pin));

				/* Assign the passed values in the local variable */
				LOC_u32LocAFL |= ((Copy_u32AFx) << (NUM_OF_PIN_S_AFRX_BITS * Add_strPinConfig->GPIO_pin));

				/* As We finish the configurations, We can assign directly in the
				 * real register */
				((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->AFRL = LOC_u32LocAFL;
			}
			else
			{
				/* Create a local variable as an image of the real register */
				uint32_t LOC_u32LocAFH = ((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->AFRH;

				/* Clean the bits before assigning in it */
				LOC_u32LocAFH &= ~(AFRX_Y_SET_MASK << (NUM_OF_PIN_S_AFRX_BITS * Add_strPinConfig->GPIO_pin));

				/* Assign the passed values in the local variable */
				LOC_u32LocAFH |= ((Copy_u32AFx) << (NUM_OF_PIN_S_AFRX_BITS * Add_strPinConfig->GPIO_pin));

				/* As We finish the configurations, We can assign directly in the
				 * real register */
				((GPIO_strRegsiters_t*)(Add_strPinConfig->GPIO_port))->AFRH = LOC_u32LocAFH;
			}
		}
		else
		{
			/* Seems that one or more input parameter is not in the specified range, return error */
			LOC_enuErrorStatus = GPIO_enuNotOk;
		}
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief  : Function to Set a pin's value to be Logic HIGH  or Logic LOW.
 *@param  : Port Number, Pin Number, Pin's value (HIGH/LOW).
 *@return : Error status.
 */
GPIO_enuErrorStatus_t GPIO_enuSetPinVal(uint32_t Copy_u32PortNum, uint32_t Copy_u32PinNum,\
										uint32_t Copy_enuPinVal)
{
	GPIO_enuErrorStatus_t LOC_enuErrorStatus = GPIO_enuOk;

	/* We should check on the passed parameters that it is in the range */
	if (((Copy_u32PortNum >= GPIO_PORTA) && (Copy_u32PortNum <= GPIO_PORTH))\
			/* The compiler will generate the following warning:
			 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
			 * ignore it */
		&& ((Copy_u32PinNum >= GPIO_PIN0) && (Copy_u32PinNum <= GPIO_PIN15))\
		/* The compiler will generate the following warning:
		 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
		 * ignore it */
		&& ((Copy_enuPinVal >= GPIO_PIN_VAL_LOW) && (Copy_enuPinVal <= GPIO_PIN_VAL_HIGH)))
	{
		/* Seems that all the parameters are passed correctly in the range, let's assign */

		/* switch on the passed value, if 0 then we will use the reset bits in the BSRR,
		 * if 1 then We will use the set bits in the BSRR */
		switch (Copy_enuPinVal)
		{
		case GPIO_PIN_VAL_LOW:
			/* Write 1 in the specified bit in the reset bits in the BSRR (31:16) */
			((GPIO_strRegsiters_t*)(Copy_u32PortNum))->BSRR = 1 <<(Copy_u32PinNum + NUM_OF_PORT_S_PINS);
			break;
		case GPIO_PIN_VAL_HIGH:
			/* Write 1 in the specified bit in the set bits in the BSRR (15:0) */
			((GPIO_strRegsiters_t*)(Copy_u32PortNum))->BSRR = 1 <<(Copy_u32PinNum);
			break;
		default:
			/* DO NOTHING (The code will never reach this point, as we checked on the passed values already) */
			break;
		}
	}
	else
	{
		/* Seems that one or more input parameter is not in the specified range, return error */
		LOC_enuErrorStatus = GPIO_enuNotOk;
	}


	return LOC_enuErrorStatus;
}

/**
 *@brief  : Function to Read the Logic State of the Pin (Is it HIGH or LOW).
 *@param  : Port Number,Pin Number, Pointer to return the value of pin state.
 *@return : Error status.
 */
GPIO_enuErrorStatus_t GPIO_enuGetPinVal(uint32_t Copy_u32PortNum, uint32_t Copy_u32PinNum,\
										uint32_t* Add_Pu32PinVal)
{
	GPIO_enuErrorStatus_t LOC_enuErrorStatus = GPIO_enuOk;

	/* We should check on the passed parameters that it is in the range */
	if (((Copy_u32PortNum >= GPIO_PORTA) && (Copy_u32PortNum <= GPIO_PORTH))\
			/* The compiler will generate the following warning:
			 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
			 * ignore it */
		&& ((Copy_u32PinNum >= GPIO_PIN0) && (Copy_u32PinNum <= GPIO_PIN15))\
		&& (Add_Pu32PinVal != NULL_PTR))
	{
		/* Seems that all the parameters are passed correctly in the range, let's go */

		/* Assign the value in the bit corresponding to the passed pin inside the passed pointer */
		*Add_Pu32PinVal = ((GPIO_strRegsiters_t*)(Copy_u32PortNum))->IDR & (1 << Copy_u32PinNum);
	}
	else
	{
		/* Seems that one or more input parameter is not in the specified range, return error */
		LOC_enuErrorStatus = GPIO_enuNotOk;
	}

	return LOC_enuErrorStatus;
}







