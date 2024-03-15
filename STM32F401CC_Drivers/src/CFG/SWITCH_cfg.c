/******************************************************************************
 *
 * Module: SWITCH driver to initialize DIO pins for the connected Switches, and getting its state.
 *
 * File Name: SWITCH_cfg.c
 *
 * Description: Configuration file for SWITCH Driver.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 15-12-2023 (Edited for ARM at 21-02-2024)
 *
 *******************************************************************************/

/* Including the .h file that contains Driver's APIs' prototypes and typedefs' declaration. */
#include <CFG/SWITCH_cfg.h>

#include <HAL/SWITCH.h>
/* ِIncluding the .h file that contains all configurations */

/* Description: Create array of switches you chose, setting inside it the configuration you want for each switch.
 * example:
 * SWITCH_strSwitchConfig_t arrayofSwitchesConfig [NUM_OF_SWITCHES] = {
	[SWITCH_01] = { 	.SW_port_number = 			#Options:	GPIO_PORTA
														or		GPIO_PORTB
														or		GPIO_PORTC
														or		GPIO_PORTD
														or		GPIO_PORTE
														or		GPIO_PORTH		#,

						.SW_pin_number = 			#Options:	GPIO_PIN0
														or		GPIO_PIN1
														or		GPIO_PIN2
														or		GPIO_PIN3
														or		GPIO_PIN4
														or		GPIO_PIN5
														or		GPIO_PIN6
														or      GPIO_PIN7
														or      GPIO_PIN8
														or      GPIO_PIN9
														or      GPIO_PIN10
														or      GPIO_PIN11
														or      GPIO_PIN12
														or      GPIO_PIN13
														or      GPIO_PIN14
														or      GPIO_PIN15		#,

						.SW_connection_method = 		#Options:	SWITCH_enuInternalPullUpConnection
														or		SWITCH_enuExternalPullUpConnection
														or		SWITCH_enuInternalPullDownConnection
														or		SWITCH_enuExternalPullDownConnection		#
	},
	[SWITCH_02] = { 	.SW_port_number = 			#Options:	GPIO_PORTA
														or		GPIO_PORTB
														or		GPIO_PORTC
														or		GPIO_PORTD
														or		GPIO_PORTE
														or		GPIO_PORTH		#,

						.SW_pin_number = 			#Options:	GPIO_PIN0
														or		GPIO_PIN1
														or		GPIO_PIN2
														or		GPIO_PIN3
														or		GPIO_PIN4
														or		GPIO_PIN5
														or		GPIO_PIN6
														or      GPIO_PIN7
														or      GPIO_PIN8
														or      GPIO_PIN9
														or      GPIO_PIN10
														or      GPIO_PIN11
														or      GPIO_PIN12
														or      GPIO_PIN13
														or      GPIO_PIN14
														or      GPIO_PIN15		#,

						.SW_connection_method = 		#Options:	SWITCH_enuInternalPullUpConnection
														or		SWITCH_enuExternalPullUpConnection
														or		SWITCH_enuInternalPullDownConnection
														or		SWITCH_enuExternalPullDownConnection		#
	},
	and so on ...
};																									*/

SWITCH_strSwitchConfig_t arrayofSwitchesConfig [NUM_OF_SWITCHES] = {
	[ON_SW] = { .SW_port_number = GPIO_PORTB,
					.SW_pin_number = GPIO_PIN0,
					.SW_connection_method = SWITCH_enuInternalPullDownConnection
	},
	[OFF_SW] = { .SW_port_number = GPIO_PORTB,
					.SW_pin_number = GPIO_PIN7,
					.SW_connection_method = SWITCH_enuInternalPullUpConnection
	}
};
