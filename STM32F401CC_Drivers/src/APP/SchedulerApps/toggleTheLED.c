/******************************************************************************
 *
 * File Name: toggleTheLED.c
 *
 * Description: Runnable that toggle a LED every one second.
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



/****************************************************************************/
/*							Functions' Implementation						*/
/****************************************************************************/


/**
 *@brief : Runnable with periodicity 1 second.
 *@param : void.
 *@return: void.
 */
void RUNNABLE_toggleLED(void)
{
	// LED_enuInit();

	static uint8_t counter = 0;

	counter++;

	if (counter == 1)
	{
		LED_enuPowerON(ALARM_LED);
	}
	else
	{
		LED_enuPowerOFF(ALARM_LED);
		counter = 0;
	}
}
