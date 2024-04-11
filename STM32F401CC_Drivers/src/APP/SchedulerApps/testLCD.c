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


static void DummyCB(void)
{

}


/**
 *@brief : Runnable with periodicity 1000 milliseconds.
 *@param : void.
 *@return: void.
 */
void RUNNABLE_testLCD(void)
{

	static uint8_t hours   = 15;
	static uint8_t minutes = 0;
	static uint32_t seconds = 1240450;

	static uint32_t entryCounter = 0;

	switch (entryCounter)
	{
	case 0:
		//LCD_enuWriteStringAsync("0", DummyCB);
		break;
	case 1:
		LCD_enuWriteNumberAsync(hours, DummyCB);
		break;
	case 2:
		LCD_enuWriteStringAsync(":", DummyCB);
		break;
	case 3:
		LCD_enuWriteStringAsync("0", DummyCB);
		break;
	case 4:
		LCD_enuWriteNumberAsync(minutes, DummyCB);
		break;
	case 5:
		LCD_enuWriteStringAsync(":", DummyCB);
		break;
	case 6:
		//LCD_enuWriteStringAsync("0", DummyCB);
		break;
	case 7:
		LCD_enuWriteNumberAsync(seconds, DummyCB);
		break;
	}

	entryCounter++;


	//	/* Variables related to the date and time. Initially We are setting them as follows */
	//	static uint8_t hours   = 7;
	//	static uint8_t minutes = 3;
	//	static uint8_t seconds = 0;
	//	static uint8_t day = 1;
	//	static uint8_t month = 1;
	//	static uint16_t year = 2024;
	//
	//	static uint64_t LCD_Counter = 0;
	//
	//	switch(LCD_Counter)
	//	{
	//	case 0 :
	//		LCD_enuSetCursorAsync  (LCD_enuFirstRow,LCD_enuColumn_1 ,DummyCB);
	//		LCD_Counter ++ ;
	//		break;
	//	case 1 :
	//		LCD_enuWriteStringAsync("Date: ",DummyCB);
	//		LCD_Counter ++ ;
	//		break;
	//	case 2 :
	//		if (day < 10)
	//		{
	//			LCD_enuWriteStringAsync("0",DummyCB);
	//		}
	//		else
	//		{
	//			LCD_enuWriteNumberAsync(day,DummyCB);
	//		}
	//		LCD_Counter ++ ;
	//		break;
	//	case 3:
	//		if (day < 10)
	//		{
	//			LCD_enuWriteNumberAsync(day,DummyCB);
	//		}
	//		else
	//		{
	//
	//		}
	//		LCD_Counter ++ ;
	//		break;
	//	case 4 :
	//		LCD_enuWriteStringAsync("/",DummyCB);
	//		LCD_Counter ++ ;
	//		break;
	//	case 5 :
	//		if (month < 10)
	//		{
	//			LCD_enuWriteStringAsync("0",DummyCB);
	//		}
	//		else
	//		{
	//			LCD_enuWriteNumberAsync(month,DummyCB);
	//		}
	//		LCD_Counter ++ ;
	//		break;
	//	case 6:
	//		if (month < 10)
	//		{
	//			LCD_enuWriteNumberAsync(month,DummyCB);
	//		}
	//		else
	//		{
	//
	//		}
	//		LCD_Counter ++ ;
	//		break;
	//	case 7 :
	//		LCD_enuWriteStringAsync("/",DummyCB);
	//		LCD_Counter ++ ;
	//		break;
	//	case 8 :
	//		if (year < 1000)
	//		{
	//			LCD_enuWriteStringAsync("0",DummyCB);
	//		}
	//		else if (year < 100)
	//		{
	//			LCD_enuWriteStringAsync("00",DummyCB);
	//		}
	//		else if (year < 10)
	//		{
	//			LCD_enuWriteStringAsync("000",DummyCB);
	//		}
	//		else if (year < 1)
	//		{
	//			LCD_enuWriteStringAsync("0000",DummyCB);
	//		}
	//		else
	//		{
	//			LCD_enuWriteNumberAsync(year,DummyCB);
	//		}
	//		LCD_Counter ++ ;
	//		break;
	//	case 9 :
	//		if (year < 1000)
	//		{
	//			LCD_enuWriteNumberAsync(year,DummyCB);
	//		}
	//		else if (year < 100)
	//		{
	//			LCD_enuWriteNumberAsync(year,DummyCB);
	//		}
	//		else if (year < 10)
	//		{
	//			LCD_enuWriteNumberAsync(year,DummyCB);
	//		}
	//		else if (year < 1)
	//		{
	//			LCD_enuWriteNumberAsync(year,DummyCB);
	//		}
	//		else
	//		{
	//
	//		}
	//		LCD_Counter ++ ;
	//		break;
	//	case 10 :
	//		LCD_enuSetCursorAsync  (LCD_enuSecondRow,LCD_enuColumn_1 ,DummyCB);
	//		LCD_Counter ++ ;
	//		break;
	//	case 11:
	//		LCD_enuWriteStringAsync("Time:   ",DummyCB);
	//		LCD_Counter ++ ;
	//		break;
	//	case 12:
	//		if (hours < 10)
	//		{
	//			LCD_enuWriteStringAsync("0",DummyCB);
	//		}
	//		else
	//		{
	//			LCD_enuWriteNumberAsync(hours,DummyCB);
	//		}
	//		LCD_Counter ++ ;
	//		break;
	//	case 13:
	//		if(hours < 10)
	//		{
	//			LCD_enuWriteNumberAsync(hours,DummyCB);
	//		}
	//		else
	//		{
	//
	//		}
	//		LCD_Counter ++ ;
	//		break;
	//	case 14 :
	//		LCD_enuWriteStringAsync(":",DummyCB);
	//		LCD_Counter ++ ;
	//		break;
	//	case 15 :
	//		if (minutes < 10)
	//		{
	//			LCD_enuWriteStringAsync("0",DummyCB);
	//		}
	//		else
	//		{
	//			LCD_enuWriteNumberAsync(minutes,DummyCB);
	//		}
	//		LCD_Counter ++ ;
	//		break;
	//	case 16 :
	//		if(minutes < 10)
	//		{
	//			LCD_enuWriteNumberAsync(minutes,DummyCB);
	//		}
	//		else
	//		{
	//
	//		}
	//		LCD_Counter ++ ;
	//		break;
	//	case 17:
	//		LCD_enuWriteStringAsync(":",DummyCB);
	//		LCD_Counter ++ ;
	//		break;
	//	case 18 :
	//		if (seconds < 10)
	//		{
	//			LCD_enuWriteStringAsync("0",DummyCB);
	//		}
	//		else
	//		{
	//			LCD_enuWriteNumberAsync(seconds,DummyCB);
	//		}
	//		LCD_Counter ++ ;
	//		break;
	//	case 19 :
	//		if(seconds < 10)
	//		{
	//			LCD_enuWriteNumberAsync(seconds,DummyCB);
	//		}
	//		else
	//		{
	//
	//		}
	//		//printEntireScreen = FALSE ;
	//		LCD_Counter = 0 ;
	//		break;
	//	}
}
