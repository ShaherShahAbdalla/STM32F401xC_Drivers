/******************************************************************************
*
* Module: Scheduler Driver.
*
* File Name: SCHED_prog.c
*
* Description: Driver's APIs' Implementation and typedefs' declaration.
*
* Author: Shaher Shah Abdalla Kamal
*
* Date:	15-03-2024
*
*******************************************************************************/


/****************************************************************************************/
/*										Includes										*/
/****************************************************************************************/


#include "MCAL/SYSTICK_interface.h"
#include "SERVICE/SCHED_interface.h"



/****************************************************************************************/
/*									Macros Declaration									*/
/****************************************************************************************/


/* Periodicity of our Scheduler */
#define SCHED_PERIODICITY_MS		10



/****************************************************************************************/
/*								User-defined types Declaration							*/
/****************************************************************************************/


/* The reason of "const" is that the scheduler can not add tasks in the runtime */
extern const runnable_t arrayOfRunnables [_RunnablesNumber_];



/****************************************************************************************/
/*									Variables's Declaration								*/
/****************************************************************************************/


/* The reason of "volatile" is that */
static volatile uint32_t pendingTasks = 0;



/****************************************************************************************/
/*								Static Functions' Declaration							*/
/****************************************************************************************/


/**
 *@brief : Function that initializes the scheduler.
 *@param : void.
 *@return: void.
 */
static void SCHED_sched(void)
{
	uint32_t index;
	static uint32_t timeStamp = 0;
	for(index = 0; index < _RunnablesNumber_; index++)
	{
		/* Check on the CallBack pointer that it isn't a NULL pointer and check
		 * if the time of this runnable comes */
		if((arrayOfRunnables[index].callBackFn)\
				&& ((timeStamp % (arrayOfRunnables[index].periodicityMS)) == 0))
		{
			/* If everything is OK, call the CallBackFn of this runnable */
			arrayOfRunnables[index].callBackFn();
		}
	}
	/* Plus the periodicity of our scheduler to the timeStamp variable because when this function
	 * be called next time, the time passed will be equal to the scheduler's periodicity  */
	timeStamp += SCHED_PERIODICITY_MS;
}



/****************************************************************************************/
/*								Functions' Implementation								*/
/****************************************************************************************/


/**
 *@brief : Function that .
 *@param : void.
 *@return: void.
 */
void tickCallBack(void)
{
	pendingTasks++;
}


/**
 *@brief : Function that initializes the scheduler.
 *@param : void.
 *@return: void.
 */
void SCHED_init(void)
{
	SYSTICK_SetTimeMilliSec(SCHED_PERIODICITY_MS);
	SYSTICK_SetCallBack(tickCallBack);
}


/**
 *@brief : Function that starts the scheduler.
 *@param : void.
 *@return: void.
 */
void SCHED_start(void)
{
	SYSTICK_Start(START_PERIODIC);
	while (1)
	{
		if(pendingTasks)
		{
			pendingTasks--;
			SCHED_sched();
		}
	}
}
