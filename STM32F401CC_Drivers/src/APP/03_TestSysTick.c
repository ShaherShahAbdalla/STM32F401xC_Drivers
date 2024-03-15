/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/******************************************************************************
 *
 * File Name: main03.c
 *
 * Description: Testing the SysTick driver.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 12-03-2024
 *
 *******************************************************************************/


// ----------------------------------------------------------------------------

#include <HAL/LED.h>
#include <MCAL/SYSTICK_interface.h>


// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace-impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


void toggleLED (void)
{
	static uint8_t LOC_counter = 0;
	static uint8_t LOC_counter2 = 0;

	LOC_counter++;
	LOC_counter2++;

	if (LOC_counter == 1)
	{
		LED_enuPowerON(ALARM_LED);
	}
	else
	{
		LOC_counter = 0;
		LED_enuPowerOFF(ALARM_LED);
	}
	/* Disable the SysTick After 16 toggles */
	if (LOC_counter2 == 16)
	{
		SYSTICK_Stop();
	}
}


int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.


	LED_enuInit();
	SYSTICK_SetTimeMilliSec(1000);
	SYSTICK_SetCallBack(toggleLED);
	SYSTICK_Start(START_PERIODIC);


  // Infinite loop
  while (1)
    {

    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
