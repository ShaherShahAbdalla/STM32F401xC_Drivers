/******************************************************************************
 *
 * Module: LED driver to initialize DIO pins for the connected LEDs, Powering it ON and OFF.
 *
 * File Name: LED.c
 *
 * Description: Driver's APIs' implementation.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 11-12-2023 (Edited for ARM at 19-02-2024)
 *
 *******************************************************************************/

/* ِIncluding the .h file that contains typedefs for the primitive data types */
#include "../../00_LIB/std_types.h"

/* Including the RCC to be able to enable the GPIO peripherals */
#include "../../01_MCAL/00_RCC/RCC_interface.h"

/* Including the GPIO driver to be able to configure and set the pins to which the LEDs are connected */
#include "../../01_MCAL/01_GPIO/GPIO_interface.h"

/* Including the .h file that contains Driver's APIs' prototypes and typedefs' declaration. */
#include "./LED.h"


/****************************************************************************************/
/*									MACROS Declaration									*/
/****************************************************************************************/

#define PIN_VAL_ActiveLow_PowerOFF					GPIO_PIN_VAL_HIGH
#define PIN_VAL_ActiveLow_PowerON					GPIO_PIN_VAL_LOW

#define PIN_VAL_ActiveHigh_PowerOFF					GPIO_PIN_VAL_LOW
#define PIN_VAL_ActiveHigh_PowerON					GPIO_PIN_VAL_HIGH



/****************************************************************************************/
/*									Global Variables									*/
/****************************************************************************************/

extern LED_strLEDconfig_t arrayofLEDsconfig [NUM_OF_LEDS];

/****************************************************************************************/
/*									APIs Implementation									*/
/****************************************************************************************/

/**
 *@brief : Function to Set the pins to which the LEDs is connected to.
 *@param : Array of structures that contains configuration of the LEDs.
 *@return: Error Status.
 */
LED_enuErrorStatus_t LED_enuInit(void)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	LED_enuErrorStatus_t LOC_enuErrorStatus = LED_enuOk;

	/* Check if the entered pointer is a NULL pointer, we will not be able to dereference it */
	if (arrayofLEDsconfig == NULL_PTR)
	{
		LOC_enuErrorStatus = LED_enuNullPointer;
	}
	else
	{
		uint8_t LOC_uint8counter;
		GPIO_strPinConfig_t LOC_LEDconfig;
		for(LOC_uint8counter = 0; LOC_uint8counter < NUM_OF_LEDS; LOC_uint8counter++)
		{

			/* Checking the LED's pin's parameters */

			if ((arrayofLEDsconfig[LOC_uint8counter].LED_port_number >= GPIO_PORTA)\
					&& (arrayofLEDsconfig[LOC_uint8counter].LED_port_number <= GPIO_PORTH)\
					&& (arrayofLEDsconfig[LOC_uint8counter].LED_pin_number >= GPIO_PIN0)\
					&& (arrayofLEDsconfig[LOC_uint8counter].LED_pin_number <= GPIO_PIN15)
					&& (arrayofLEDsconfig[LOC_uint8counter].connection_type >= LED_enuActiveLow)\
					&& (arrayofLEDsconfig[LOC_uint8counter].connection_type <= LED_enuActiveHigh)\
					&& (arrayofLEDsconfig[LOC_uint8counter].init_state >= LED_enuOFF)\
					&& (arrayofLEDsconfig[LOC_uint8counter].init_state <= LED_enuON))
			{
				/* If everything is OK, We could configure the pins now */

				/* First enable the GPIOx peripheral to which the current LED is connected */
				switch (arrayofLEDsconfig[LOC_uint8counter].LED_port_number)
				{
				case GPIO_PORTA:
					LOC_enuErrorStatus = RCC_enuEnableAHB1Peripheral(AHB1_GPIOA);
					break;
				case GPIO_PORTB:
					LOC_enuErrorStatus = RCC_enuEnableAHB1Peripheral(AHB1_GPIOB);
					break;
				case GPIO_PORTC:
					LOC_enuErrorStatus = RCC_enuEnableAHB1Peripheral(AHB1_GPIOC);
					break;
				case GPIO_PORTD:
					LOC_enuErrorStatus = RCC_enuEnableAHB1Peripheral(AHB1_GPIOD);
					break;
				case GPIO_PORTE:
					LOC_enuErrorStatus = RCC_enuEnableAHB1Peripheral(AHB1_GPIOE);
					break;
				case GPIO_PORTH:
					LOC_enuErrorStatus = RCC_enuEnableAHB1Peripheral(AHB1_GPIOH);
					break;
				default:
					/* The code won't reach here as We already validated the input LED's PORT */
					break;
				}
				/* Now check that the GPIO peripheral is enabled */
				if (LOC_enuErrorStatus == RCC_enuOk)
				{
					/* Till now, everything is OK, We can start configure the pins */

					LOC_LEDconfig.GPIO_port = arrayofLEDsconfig[LOC_uint8counter].LED_port_number;
					LOC_LEDconfig.GPIO_pin = arrayofLEDsconfig[LOC_uint8counter].LED_pin_number;
					LOC_LEDconfig.GPIO_speed = GPIO_SPEED_HIGH;
					LOC_LEDconfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;

					/* Passing the configurations assigned in "LOC_LEDconfig" to the GPIO initialize function
					 * to initialize the pin */
					LOC_enuErrorStatus = GPIO_enuInitPin(&LOC_LEDconfig);

					/* Check that the last LED's pin is Initially configured correctly */
					if (LOC_enuErrorStatus == GPIO_enuOk)
					{
						/* The last LED's pin is Initially configured correctly, We now can set its initial state */

						/* Switch on the LED's Active type */
						switch(arrayofLEDsconfig[LOC_uint8counter].connection_type)
						{
						case LED_enuActiveLow:
							switch (arrayofLEDsconfig[LOC_uint8counter].init_state)
							{
							case LED_enuOFF:
								/* Setting the configuration after checking that everything is correct and OK */
								LOC_enuErrorStatus = GPIO_enuSetPinVal(arrayofLEDsconfig[LOC_uint8counter].LED_port_number,\
										arrayofLEDsconfig[LOC_uint8counter].LED_pin_number,\
										PIN_VAL_ActiveLow_PowerOFF);
								break;
							case LED_enuON:
								/* Setting the configuration after checking that everything is correct and OK */
								LOC_enuErrorStatus = GPIO_enuSetPinVal(arrayofLEDsconfig[LOC_uint8counter].LED_port_number,\
										arrayofLEDsconfig[LOC_uint8counter].LED_pin_number,\
										PIN_VAL_ActiveLow_PowerON);
								break;
							default:
								/* The code won't reach here as We already validated the input LED's Initial state */
								break;
							}
							break;
						case LED_enuActiveHigh:
							switch (arrayofLEDsconfig[LOC_uint8counter].init_state)
							{
							case LED_enuOFF:
								/* Setting the configuration after checking that everything is correct and OK */
								LOC_enuErrorStatus = GPIO_enuSetPinVal(arrayofLEDsconfig[LOC_uint8counter].LED_port_number,\
										arrayofLEDsconfig[LOC_uint8counter].LED_pin_number,\
										PIN_VAL_ActiveHigh_PowerOFF);
								break;
							case LED_enuON:
								/* Setting the configuration after checking that everything is correct and OK */
								LOC_enuErrorStatus = GPIO_enuSetPinVal(arrayofLEDsconfig[LOC_uint8counter].LED_port_number,\
										arrayofLEDsconfig[LOC_uint8counter].LED_pin_number,\
										PIN_VAL_ActiveHigh_PowerON);
								break;
							default:
								/* The code won't reach here as We already validated the input LED's Initial type */
								break;
							}
							break;
						default:
							/* The code won't reach here as We already validated the input LED's Connection type */
							break;
						}
						/* Now check that the LED's pin's value is set correctly */
						if(LOC_enuErrorStatus == GPIO_enuOk)
						{
							/* We managed to initialize this LED correctly, continue */
						}
						else
						{
							/* The last LED's pin's value could not be set correctly for some reasons */
							LOC_enuErrorStatus = LED_enuNotOk;
							/* Stop looping on the LEDs, return error */
							break;
						}
					}
					else
					{
						/* The last LED's pin could not be Initially configured correctly for some reasons */
						LOC_enuErrorStatus = LED_enuNotOk;
						/* Stop looping on the LEDs, return error */
						break;
					}
				}
				else
				{
					/* The last LED's PORT could not be enabled for some reasons */
					LOC_enuErrorStatus = LED_enuNotOk;
					/* Stop looping on the LEDs, return error */
					break;
				}
			}
			else
			{
				/* One or more of one of the LEDs' pin's parameters is wrong */
				LOC_enuErrorStatus = LED_enuNotOk;
				/* Stop looping on the LEDs, return error */
				break;
			}
		}
	}


	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to power ON the entered LED.
 *@param : Name of the LED you want to power it ON.
 *@return: Error Status.
 */
LED_enuErrorStatus_t LED_enuPowerON(uint8_t copy_LEDname)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	LED_enuErrorStatus_t LOC_enuErrorStatus = LED_enuOk;

	/* Check on the input LED name if it is in the LEDs list or not */
	if(copy_LEDname < NUM_OF_LEDS)
	{
		switch(arrayofLEDsconfig[copy_LEDname].connection_type)
		{
		case LED_enuActiveLow:
			LOC_enuErrorStatus = GPIO_enuSetPinVal(arrayofLEDsconfig[copy_LEDname].LED_port_number,\
					arrayofLEDsconfig[copy_LEDname].LED_pin_number,\
					PIN_VAL_ActiveLow_PowerON);
			break;
		case LED_enuActiveHigh:
			LOC_enuErrorStatus = GPIO_enuSetPinVal(arrayofLEDsconfig[copy_LEDname].LED_port_number,\
					arrayofLEDsconfig[copy_LEDname].LED_pin_number,\
					PIN_VAL_ActiveHigh_PowerON);
			break;
		default:
			/* The code won't reach here as We already validated the input LED's Connection type */
			break;
		}
	}
	else
	{
		/* The user didn't enter on of the listed LEDs */
		LOC_enuErrorStatus = LED_enuNotOk;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to power OFF the entered LED.
 *@param : Name of the LED you want to power it OFF.
 *@return: Error Status.
 */
LED_enuErrorStatus_t LED_enuPowerOFF(uint8_t copy_LEDname)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	LED_enuErrorStatus_t LOC_enuErrorStatus = LED_enuOk;

	/* Check on the input LED name if it is in the LEDs list or not */
	if(copy_LEDname < NUM_OF_LEDS)
	{
		switch(arrayofLEDsconfig[copy_LEDname].connection_type)
		{
		case LED_enuActiveLow:
			LOC_enuErrorStatus = GPIO_enuSetPinVal(arrayofLEDsconfig[copy_LEDname].LED_port_number,\
					arrayofLEDsconfig[copy_LEDname].LED_pin_number,\
					PIN_VAL_ActiveLow_PowerOFF);
			break;
		case LED_enuActiveHigh:
			LOC_enuErrorStatus = GPIO_enuSetPinVal(arrayofLEDsconfig[copy_LEDname].LED_port_number,\
					arrayofLEDsconfig[copy_LEDname].LED_pin_number,\
					PIN_VAL_ActiveHigh_PowerOFF);
			break;
		default:
			/* The code won't reach here as We already validated the input LED's Connection type */
			break;
		}
	}
	else
	{
		/* The user didn't enter on of the listed LEDs */
		LOC_enuErrorStatus = LED_enuNotOk;
	}

	return LOC_enuErrorStatus;
}
