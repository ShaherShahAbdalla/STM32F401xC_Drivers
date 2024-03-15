/******************************************************************************
 *
 * Module: LED driver to initialize DIO pins for the connected LEDs, Powering it ON and OFF.
 *
 * File Name: LED_cfg.c
 *
 * Description: Configuration file for LEDs Driver.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 11-12-2023 (Edited for ARM at 19-02-2024)
 *
 *******************************************************************************/

/* Including the .h file that contains Driver's APIs' prototypes and typedefs' declaration. */
#include <CFG/LED_cfg.h>

#include <HAL/LED.h>
/* ِIncluding the .h file that contains all configurations */

/* Description: Create array of LEDs you chose, setting inside it the configuration you want for each LED.
 * example:
 * LED_strLEDconfig_t arrayofLEDsconfig [NUM_OF_LEDS] = {
	[START_LED] = { 	.LED_port_number = 	#Options:	GPIO_PORTA
												or		GPIO_PORTB
												or		GPIO_PORTC
												or		GPIO_PORTD
												or		GPIO_PORTE
												or		GPIO_PORTH		#,

						.LED_pin_number = 	#Options:	GPIO_PIN0
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

						.connection_type = 	#Options:	LED_enuActiveLow
												or		LED_enuActiveHigh	#,

						.init_state = 		#Options:	LED_enuOFF
												or		LED_enuON			#
	},
	[SOMETHING_LED] = { .LED_port_number = 	#Options:	GPIO_PORTA
												or		GPIO_PORTB
												or		GPIO_PORTC
												or		GPIO_PORTD
												or		GPIO_PORTE
												or		GPIO_PORTH		#,

						.LED_pin_number = 	#Options:	GPIO_PIN0
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

						.connection_type =	 #Options:	LED_enuActiveLow
												or		LED_enuActiveHigh	#,

						.init_state = 		#Options:	LED_enuOFF
												or		LED_enuON			#
	},
	and so on ...
};																									*/

LED_strLEDconfig_t arrayofLEDsconfig [NUM_OF_LEDS] = {
	[ALARM_LED] = { .LED_port_number = GPIO_PORTA,
					.LED_pin_number = GPIO_PIN2,
					.connection_type = LED_enuActiveHigh,
					.init_state = LED_enuOFF
	}
};
