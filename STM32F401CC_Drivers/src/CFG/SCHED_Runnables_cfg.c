/******************************************************************************
 *
 * File Name: RunnablesList_cfg.c
 *
 * Description: Configuration file for The Runnables in the System.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 15-03-2024
 *
 *******************************************************************************/

/************************************************************************************/
/*									Includes										*/
/************************************************************************************/


#include <SERVICE/SCHED.h>



/************************************************************************************/
/*								extern Public Functions								*/
/************************************************************************************/


/* Add here The functions that you will set in the callBackFn member for the runnables */
extern void RUNNABLE_toggleLED(void);
extern void RUNNABLE_testLCD(void);
//extern void RUNNABLE_ctrlLED(void);
//extern void RUNNABLE_SWITCH_getSwitchState(void);
//extern void RUNNABLE_trafficLight_stateMachine(void);
extern void RUNNABLE_LCD(void);



/************************************************************************************/
/*							User-defined Types Definition							*/
/************************************************************************************/


/* Description: Create array of Runnables in your system,
 * 				setting inside it the configuration you want for each Runnable.
 * Example:
 * const runnable_t arrayOfRunnables [_RunnablesNumber_] = {
	[Runnable1] = { .name = "Toggle LED each second",
							.periodicityMS = 1000,
							.callBackFn = RUNNABLE_LED_toggle
	},
	[Runnable2] = { .name = "Check the status of the switches",
							.periodicityMS = 30,
							.callBackFn = RUNNABLE_SWITCH_getSwitchState
	},
	and so on ...
};
 * Cautions: 	- Be careful when setting the periodicity of any runnable that it's not
 * 					smaller than 10 ms.
 * 				- Note that the order in which You will write the runnables in the array defines
 * 					the priority for each of them, the priority decreases as the index of the runnable
 * 					increases (Runnable in index zero is the one with the highest priority).
 * 																					*/

const runnable_t arrayOfRunnables [_RunnablesNumber_] = {
	[toggleTheLED] 		= { .name = "Toggle LED each second",
							.periodicityMS = 1000,
							.firstDelay = 50,
							.callBackFn = RUNNABLE_toggleLED
	},
	[testLCD] 		= { .name = "Test the LCD driver",
							.periodicityMS = 100,
							.firstDelay = 50,
							.callBackFn = RUNNABLE_testLCD
	},
//	[switchRunnable] 	= { .name = "Check the status of the switches",
//							.periodicityMS = 30,
//							.callBackFn = RUNNABLE_SWITCH_getSwitchState
//	},
//	[ctrlLED] 			= { .name = "Control a LED through a switch",
//							.periodicityMS = 50,
//							.callBackFn = RUNNABLE_ctrlLED
//	},
//	[trafficLightSM] 	= { .name = "Traffic light application",
//							.periodicityMS = 1000,
//							.callBackFn = RUNNABLE_trafficLight_stateMachine
//	},
	[lcdRunnable] 		= { .name = "LCD module",
							.periodicityMS = 1,
							.firstDelay = 0,
							.callBackFn = RUNNABLE_LCD
	}
};
