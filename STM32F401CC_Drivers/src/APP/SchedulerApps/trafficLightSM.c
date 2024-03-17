/******************************************************************************
 *
 * File Name: ctrlLED.c
 *
 * Description: Runnable that controls a traffic.
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
/*							Macros Declaration								*/
/****************************************************************************/


#define RUNNABLE_PERIODICITY_IN_SECONDS		1



/****************************************************************************/
/*						User-defined types Declaration						*/
/****************************************************************************/


/**
 *@brief : The lights in a traffic light
 */
typedef enum
{
	red,
	yellow,
	green
}lights_t;



/****************************************************************************/
/*						Static Functions' Declaration						*/
/****************************************************************************/


/**
 *@brief : Function to Turn on the red light in the traffic light and turn off yellow and green lights.
 *@param : void.
 *@return: void.
 */
static void redLightOn(void)
{
	/* Turn off the previous light which is the green */
	LED_enuPowerOFF(YELLOW_LED);
	/* Turn on the red light */
	LED_enuPowerON(RED_LED);
}


/**
 *@brief : Function to Turn on the yellow light in the traffic light and turn off red and green lights.
 *@param : void.
 *@return: void.
 */
static void yellowLightOn(void)
{
	/* Turn off the previous light which is red or green */
	LED_enuPowerOFF(RED_LED);
	LED_enuPowerOFF(GREEN_LED);
	/* Turn on the yellow light */
	LED_enuPowerON(YELLOW_LED);
}


/**
 *@brief : Function to Turn on the green light in the traffic light and turn off red and yellow lights.
 *@param : void.
 *@return: void.
 */
static void greenLightOn(void)
{
	/* Turn off the previous light which is the yellow */
	LED_enuPowerOFF(YELLOW_LED);
	/* Turn on the green light */
	LED_enuPowerON(GREEN_LED);
}



/****************************************************************************/
/*							Functions' Implementation						*/
/****************************************************************************/


/**
 *@brief : Runnable with periodicity 1 second.
 *@param : void.
 *@return: void.
 */
void RUNNABLE_trafficLight_stateMachine(void)
{
	static uint8_t elapsedSeconds = 0;
	static lights_t currentLight = yellow;
	/* Will help us to simulate a real traffic light */
	static lights_t prevLight = red;

	elapsedSeconds += RUNNABLE_PERIODICITY_IN_SECONDS;

	switch (currentLight)
	{
	case red:
		redLightOn();
		/* After 7 seconds We need to switch to the yellow light */
		if(elapsedSeconds == 7)
		{
			elapsedSeconds = 0;
			currentLight = yellow;
			prevLight = red;
		}
		break;
	case yellow:
		yellowLightOn();
		/* After 3 seconds We need to switch to the green light */
		if((elapsedSeconds == 3) && (prevLight == red))
		{
			elapsedSeconds = 0;
			currentLight = green;
			/* No need for the next line but to make the cases similar to each other */
			prevLight = yellow;
		}
		else if((elapsedSeconds == 3) && (prevLight == green))
		{
			elapsedSeconds = 0;
			currentLight = red;
			/* No need for the next line but to make the cases similar to each other */
			prevLight = yellow;
		}
		break;
	case green:
		greenLightOn();
		/* After 7 seconds We need to switch to the red light */
		if(elapsedSeconds == 7)
		{
			elapsedSeconds = 0;
			currentLight = yellow;
			prevLight = green;
		}
		break;
	default:
		/* Dead Area */
		break;
	}
}
