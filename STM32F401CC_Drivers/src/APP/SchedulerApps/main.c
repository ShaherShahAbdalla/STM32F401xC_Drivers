/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: Testing the Scheduler driver.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 15-03-2024
 *
 *******************************************************************************/


#include <SERVICE/SCHED.h>
#include "HAL/LED.h"
#include "HAL/SWITCH.h"
#include "HAL/LCD.h"

void LCD_initDoneToggleLED(void)
{

	static uint8_t counter = 0;

	counter++;

	if (counter == 1)
	{
		LED_enuPowerON(LCD_initDone);
	}
	else
	{
		LED_enuPowerOFF(LCD_initDone);
		counter = 0;
	}
}


//void LCD_writeDoneToggleLED(void)
//{
//
//	static uint8_t counter = 0;
//
//	counter++;
//
//	if (counter == 1)
//	{
//		LED_enuPowerON(LCD_writeDone);
//	}
//	else
//	{
//		LED_enuPowerOFF(LCD_writeDone);
//		counter = 0;
//	}
//}


int main (void)
{
	uint8_t* str = "TEST";

	LED_enuInit();
	SWITCH_enuInit();

	LCD_enuInitAsync(LCD_initDoneToggleLED);
//	LCD_enuWriteStringAsync(str,LCD_writeDoneToggleLED);

	SCHED_init();
	SCHED_start();

	return 0;
}
