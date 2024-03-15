/******************************************************************************
*
* Module: SYSTICK Driver.
*
* File Name: SYSTICK_interface.h
*
* Description: Driver's APIs' prototypes and typedefs' declaration.
*
* Author: Shaher Shah Abdalla Kamal
*
* Date:	10-03-2024
*
*******************************************************************************/


#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_


/****************************************************************************************/
/*										Includes										*/
/****************************************************************************************/


#include <CFG/SYSTICK_cfg.h>
#include <LIB/std_types.h>




/****************************************************************************************/
/*									Macros Declaration									*/
/****************************************************************************************/


/* SysTick start type options */
#define START_ONE_TIME					(0x00100000UL)
#define START_PERIODIC					(0x00100001UL)



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
	SYSTICK_enuOk = 0,
	/**
	 *@brief : Something went wrong in the function.
	 */
	SYSTICK_enuNotOk,
	/**
	 *@brief : Null pointer is passed to a function as an argument.
	 */
	SYSTICK_enuNullPointer,
	/**
	 *@brief : Unsupported delay time value passed to SYSTICK_SetTime function.
	 */
	SYSTICK_enuInvalidDelayValue
}SYSTICK_enuErrorStatus_t;


typedef void (*sysTickCBF_t)(void);


/****************************************************************************************/
/*									Functions' Declaration								*/
/****************************************************************************************/


/**
 *@brief : Function to start the SysTick timer.
 *@param : Start Type (START_PERIODIC	or	START_ONE_TIME).
 *@return: Error status.
 */
SYSTICK_enuErrorStatus_t SYSTICK_Start(uint32_t start_);


/**
 *@brief : Function to stop the SysTick timer.
 *@param : void.
 *@return: Error status.
 */
SYSTICK_enuErrorStatus_t SYSTICK_Stop(void);


/**
 *@brief : Function to initialize the SysTick with the input value you want.
 *@param : Delay time you want in microseconds (Up to 1,000,000 microseconds (1 second)).
 *@return: Error status.
 */
SYSTICK_enuErrorStatus_t SYSTICK_SetTimeMicroSec(uint32_t DelayTime);


/**
 *@brief : Function to initialize the SysTick with the input value you want.
 *@param : Delay time you want in milliseconds (Up to 8000 milliseconds (8 seconds)).
 *@return: Error status.
 */
SYSTICK_enuErrorStatus_t SYSTICK_SetTimeMilliSec(uint32_t DelayTime);


/**
 *@brief : Function to set the call back function that the user entered.
 *@param : pointer to function that takes a void and returns void.
 *@return: Error status.
 */
SYSTICK_enuErrorStatus_t SYSTICK_SetCallBack(sysTickCBF_t LOC_CallBackFunction);



#endif /* SYSTICK_INTERFACE_H_ */
