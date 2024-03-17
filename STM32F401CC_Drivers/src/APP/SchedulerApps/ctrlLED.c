/******************************************************************************
 *
 * File Name: ctrlLED.c
 *
 * Description: Runnable that controls a LED state through a switch.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 16-03-2024
 *
 *******************************************************************************/


/****************************************************************************/
/*								Includes									*/
/****************************************************************************/


#include "HAL/LED.h"
#include "HAL/SWITCH.h"



/****************************************************************************/
/*							Functions' Implementation						*/
/****************************************************************************/


/**
 *@brief : Runnable with periodicity 50 milliseconds.
 *@param : void.
 *@return: void.
 */
void RUNNABLE_ctrlLED(void)
{
	//LED_enuInit();

	//SWITCH_enuInit();


	SWITCH_enuSwitchState_t Add_enuSwitchState = 0;


	SWITCH_enuGetSwitchState(CTRL_SW,&Add_enuSwitchState);

	if (Add_enuSwitchState == SWITCH_enuIS_PRESSED)
	{
		LED_enuPowerON(TEST_LED);
	}
	else if (Add_enuSwitchState == SWITCH_enuNOT_PRESSED)
	{
		LED_enuPowerOFF(TEST_LED);
	}
	else
	{
		/* Do Nothing */
	}
}
