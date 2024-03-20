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


int main (void)
{
	LED_enuInit();
	SWITCH_enuInit();

	SCHED_init();
	SCHED_start();

	return 0;
}
