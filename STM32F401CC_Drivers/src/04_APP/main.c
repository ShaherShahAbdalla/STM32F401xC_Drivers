///*
// * This file is part of the µOS++ distribution.
// *   (https://github.com/micro-os-plus)
// * Copyright (c) 2014 Liviu Ionescu.
// *
// * Permission is hereby granted, free of charge, to any person
// * obtaining a copy of this software and associated documentation
// * files (the "Software"), to deal in the Software without
// * restriction, including without limitation the rights to use,
// * copy, modify, merge, publish, distribute, sublicense, and/or
// * sell copies of the Software, and to permit persons to whom
// * the Software is furnished to do so, subject to the following
// * conditions:
// *
// * The above copyright notice and this permission notice shall be
// * included in all copies or substantial portions of the Software.
// *
// * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// * OTHER DEALINGS IN THE SOFTWARE.
// */
//
///******************************************************************************
// *
// * File Name: main.c
// *
// * Description: Testing the LED and the Switch driver.
// *
// * Author: Shaher Shah Abdalla Kamal
// *
// * Date: 24-02-2024
// *
// *******************************************************************************/
//
//
//// ----------------------------------------------------------------------------
//
//#include "../02_HAL/00_LED/LED.h"
//#include "../02_HAL/01_SWITCH/SWITCH.h"
//
//// ----------------------------------------------------------------------------
////
//// Standalone STM32F4 empty sample (trace via DEBUG).
////
//// Trace support is enabled by adding the TRACE macro definition.
//// By default the trace messages are forwarded to the DEBUG output,
//// but can be rerouted to any device or completely suppressed, by
//// changing the definitions required in system/src/diag/trace-impl.c
//// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
////
//
//// ----- main() ---------------------------------------------------------------
//
//// Sample pragmas to cope with warnings. Please note the related line at
//// the end of this function, used to pop the compiler diagnostics status.
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-parameter"
//#pragma GCC diagnostic ignored "-Wmissing-declarations"
//#pragma GCC diagnostic ignored "-Wreturn-type"
//
//int
//main(int argc, char* argv[])
//{
//  // At this stage the system clock should have already been configured
//  // at high speed.
//
//
//	LED_enuInit();
//
//	SWITCH_enuInit();
//
//
//	SWITCH_enuSwitchState_t Add_enuSwitchState = 0;
//
//
//
//  // Infinite loop
//  while (1)
//    {
//       // Add your code here.
//
//	  SWITCH_enuGetSwitchState(ON_SW,&Add_enuSwitchState);
//
//	  if (Add_enuSwitchState == SWITCH_enuIS_PRESSED)
//	  {
//		  LED_enuPowerON(ALARM_LED);
//	  }
//	  SWITCH_enuGetSwitchState(OFF_SW,&Add_enuSwitchState);
//	  if (Add_enuSwitchState == SWITCH_enuIS_PRESSED)
//	  {
//		  LED_enuPowerOFF(ALARM_LED);
//	  }
//    }
//}
//
//#pragma GCC diagnostic pop
//
//// ----------------------------------------------------------------------------
