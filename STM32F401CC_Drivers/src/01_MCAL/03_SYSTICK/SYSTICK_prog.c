/******************************************************************************
*
* Module: SYSTICK Driver
*
* File Name: SYSTICK_prog.c
*
* Description: Driver's APIs' Implementation and typedefs' declaration.
*
* Author: Shaher Shah Abdalla Kamal
*
* Date: 10-03-2024
*
*******************************************************************************/



/****************************************************************************************/
/*										Includes										*/
/****************************************************************************************/


#include "./SYSTICK_interface.h"



/****************************************************************************************/
/*									Macros Declaration									*/
/****************************************************************************************/


/* SysTick registers Base Address */
#define SYSTICK_BASE_ADDRESS					(0xE000E010UL)

/* STK_CTRL TICKINT bit set mask */
#define STK_CTRL_TICKINT_SET_MASK				(0x00000002UL)
/* STK_CTRL ENABLE bit set mask */
#define STK_CTRL_ENABLE_SET_MASK				(0x00000001UL)

/* Select AHB as the clock source for the SysTick */
#define STK_CTRL_CLKSOURCE_AHB_SET_MASK			(0x00000004UL)
/* Select AHB/8 as the clock source for the SysTick */
#define STK_CTRL_CLKSOURCE_AHB_DIV_8_SET_MASK	(0x00000000UL)

/* Number of microseconds in one second */
#define NUM_OF_US_IN_1_SEC						(1000000)
/* Number of milliseconds in one second */
#define NUM_OF_MS_IN_1_SEC						(1000)

/* Max value for the SysTick ticks */
#define MAX_SYSTICK_VALUE						(0x00FFFFFFUL)


/****************************************************************************************/
/*								User-defined types Declaration							*/
/****************************************************************************************/


typedef struct {
	volatile uint32_t STK_CTRL;
	volatile uint32_t STK_LOAD;
	volatile uint32_t STK_VAL;
	volatile uint32_t STK_CALIB;
}SYSTICK_strRegsiters_t;



/****************************************************************************************/
/*									Variables's Declaration								*/
/****************************************************************************************/


static sysTickCBF_t GLB_CallBackFunction = NULL_PTR;

static SYSTICK_strRegsiters_t* const SYSTICK = (SYSTICK_strRegsiters_t*)(SYSTICK_BASE_ADDRESS);

static uint32_t GLB_StartType = 0;



/****************************************************************************************/
/*								Static Functions' Declaration							*/
/****************************************************************************************/







/****************************************************************************************/
/*								Functions' Implementation								*/
/****************************************************************************************/


/**
 *@brief : Function to start the SysTick timer.
 *@param : Start Type (START_PERIODIC	or	START_ONE_TIME).
 *@return: Error status.
 */
SYSTICK_enuErrorStatus_t SYSTICK_Start(uint32_t start_)
{
	SYSTICK_enuErrorStatus_t LOC_enuErrorStatus = SYSTICK_enuOk;

	/* Check that the user entered a valid start type or not */
	if((start_ != START_ONE_TIME) && (start_ != START_PERIODIC))
	{
		/* The user entered an INVALID start options, return error */
		LOC_enuErrorStatus = SYSTICK_enuNotOk;
	}
	else
	{
		/* Seems that the user entered a valid start type, now We can start the SysTick */

		/* Assign the start type which is entered by the user to a global value so that We will
		 * check on it in the SysTick handler */
		GLB_StartType = start_;

		/* Configure the SysTick correctly */

		/* Create a local variable as an image of the real register */
		uint32_t LOC_u32LocalReg = SYSTICK->STK_CTRL;
		/* Clean the bits before assigning in it */
		LOC_u32LocalReg &= ~(STK_CTRL_TICKINT_SET_MASK) & ~(STK_CTRL_ENABLE_SET_MASK);
		/* Assign the passed values in the local variable */
		/* Enable SysTick interrupt, and enable the SysTick itself */
		LOC_u32LocalReg |= (STK_CTRL_TICKINT_SET_MASK) | (STK_CTRL_ENABLE_SET_MASK);
		/* As We finish the configurations, We can assign directly in the real register */
		SYSTICK->STK_CTRL = LOC_u32LocalReg;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to stop the SysTick timer.
 *@param : void.
 *@return: Error status.
 */
SYSTICK_enuErrorStatus_t SYSTICK_Stop(void)
{
	SYSTICK_enuErrorStatus_t LOC_enuErrorStatus = SYSTICK_enuOk;

	/* Clear the ENABLE bit in the STK_CTRL register to disable the SysTick */
	SYSTICK->STK_CTRL &= ~(STK_CTRL_ENABLE_SET_MASK);

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to initialize the SysTick with the input value you want.
 *@param : Delay time you want in microseconds (Up to 1,000,000 microseconds (1 second) with HSI as clock source).
 *@return: Error status.
 */
SYSTICK_enuErrorStatus_t SYSTICK_SetTimeMicroSec(uint32_t DelayTime)
{
	SYSTICK_enuErrorStatus_t LOC_enuErrorStatus = SYSTICK_enuOk;

	/* Select the clock source to be AHB to get smaller tick time */
	SYSTICK->STK_CTRL |= STK_CTRL_CLKSOURCE_AHB_SET_MASK;

	/* Now We will do calculations to get number of tick that should be assigned in STK_LOAD register */
	/* ∵ TickTime = 1/frequency
	 * ∵ DelayTime = TickTime * no. of ticks
	 * ∴ no. of ticks = DelayTime/TickTime
	 * ∴ no. of ticks = DelayTime * frequency */

	/* Remember that the passed value from the user is in microseconds, so we need to divide it be 1,000,000 */
	/* The data sheet told us to subtract 1 from the value We want to assign in the STK_LOAD register */
	uint32_t LOC_NumOfTicks = (DelayTime * (AHB_CLOCK_SOURCE_VALUE/NUM_OF_US_IN_1_SEC)) - 1;

	/* Check that the number of ticks doesn't exceed the max value for the SysTick 24 bits */
	if (LOC_NumOfTicks >= MAX_SYSTICK_VALUE)
	{
		/* Return error */
		LOC_enuErrorStatus = SYSTICK_enuInvalidDelayValue;
	}
	else
	{
		/* Assign the number of ticks in the STK_LOAD register */
		/* Clear STK_LOAD first */
		SYSTICK->STK_LOAD &= ~(MAX_SYSTICK_VALUE);
		/* Assign the Value */
		SYSTICK->STK_LOAD |= LOC_NumOfTicks;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to initialize the SysTick with the input value you want.
 *@param : Delay time you want in milliseconds (Up to 8000 milliseconds (8 seconds) with HSI as clock source).
 *@return: Error status.
 */
SYSTICK_enuErrorStatus_t SYSTICK_SetTimeMilliSec(uint32_t DelayTime)
{
	SYSTICK_enuErrorStatus_t LOC_enuErrorStatus = SYSTICK_enuOk;

	/* Select the clock source to be (AHB/8) to get greater tick time */
	SYSTICK->STK_CTRL |= STK_CTRL_CLKSOURCE_AHB_DIV_8_SET_MASK;

	/* Now We will do calculations to get number of tick that should be assigned in STK_LOAD register */
	/* ∵ TickTime = 1/frequency
	 * ∵ DelayTime = TickTime * no. of ticks
	 * ∴ no. of ticks = DelayTime/TickTime
	 * ∴ no. of ticks = DelayTime * frequency */

	/* Remember that the passed value from the user is in milliseconds, so we need to divide it be 1,000 */
	/* The data sheet told us to subtract 1 from the value We want to assign in the STK_LOAD register */
	uint32_t LOC_NumOfTicks = (DelayTime * ((AHB_CLOCK_SOURCE_VALUE / 8) / NUM_OF_MS_IN_1_SEC)) - 1;

	/* Check that the number of ticks doesn't exceed the max value for the SysTick 24 bits */
	if (LOC_NumOfTicks >= MAX_SYSTICK_VALUE)
	{
		/* Return error */
		LOC_enuErrorStatus = SYSTICK_enuInvalidDelayValue;
	}
	else
	{
		/* Assign the number of ticks in the STK_LOAD register */
		/* Clear STK_LOAD first */
		SYSTICK->STK_LOAD &= ~(MAX_SYSTICK_VALUE);
		/* Assign the Value */
		SYSTICK->STK_LOAD |= LOC_NumOfTicks;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to set the call back function that the user entered.
 *@param : pointer to function that takes a void and returns void.
 *@return: Error status.
 */
SYSTICK_enuErrorStatus_t SYSTICK_SetCallBack(sysTickCBF_t LOC_CallBackFunction)
{
	SYSTICK_enuErrorStatus_t LOC_enuErrorStatus = SYSTICK_enuOk;

	/* Check on the passed pointer whether it a NULL pointer or not */
	if(LOC_CallBackFunction == NULL_PTR)
	{
		/* It seems that the user entered a NULL pointer, We can't deal with it, return error */
		LOC_enuErrorStatus = SYSTICK_enuNullPointer;
	}
	else
	{
		/* Seems that the user entered a pointer that can be accessed */

		/* Assign the entered pointer to function to a global pointer that will be called in the
		 * SysTick handler */
		GLB_CallBackFunction = LOC_CallBackFunction;
	}

	return LOC_enuErrorStatus;
}




void SysTick_Handler (void)
{
	/* Check first on the start type */
	if(GLB_StartType == START_ONE_TIME)
	{
		/* If the user wants the SysTick to run one time only, We need now to disable it */

		/* Disable the SysTick */
		SYSTICK->STK_CTRL &= ~(STK_CTRL_ENABLE_SET_MASK);
	}
	else
	{
		/* Do Nothing */
	}

	/* Check that the global pointer to function is assigned and not a NULL pointer */
	if (GLB_CallBackFunction != NULL_PTR)
	{
		/* Now we need to call the CBF that was entered by the user */
		GLB_CallBackFunction();
	}
	else
	{
		/* Do Nothing, (I think the could shouldn't reach this line) */
	}
}
