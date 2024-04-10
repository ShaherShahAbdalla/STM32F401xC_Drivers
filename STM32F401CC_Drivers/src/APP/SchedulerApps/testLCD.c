/******************************************************************************
 *
 * File Name: testLCD.c
 *
 * Description: Runnable that tests the functions of the LCD.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 08-04-2024
 *
 *******************************************************************************/


/****************************************************************************/
/*								Includes									*/
/****************************************************************************/


#include "HAL/LCD.h"


/****************************************************************************/
/*							Functions' Implementation						*/
/****************************************************************************/


void dummyCB (void) {

}


/**
 *@brief : Runnable with periodicity 1000 milliseconds.
 *@param : void.
 *@return: void.
 */
void RUNNABLE_testLCD(void)
{
	static counter = 0;
	static number = 0;


	switch (counter) {
	case 0:
		LCD_enuWriteStringAsync("Ola Migo", dummyCB);
		counter++;
		break;
	case 1:
		LCD_enuClearScreenAsync(dummyCB);
		counter++;
		break;
	case 2:
		LCD_enuSetCursorAsync(LCD_enuFirstRow, LCD_enuColumn_7, dummyCB);
		counter++;
		break;
	case 3:
		LCD_enuWriteNumberAsync(number, dummyCB);
		counter++;
		break;
	case 4:
		LCD_enuClearScreenAsync(dummyCB);
		counter = 0;
		break;
	}
}
