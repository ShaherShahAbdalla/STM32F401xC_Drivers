/******************************************************************************
 *
 * Module: SWITCH driver to initialize DIO pins for the connected Switches, and getting its state.
 *
 * File Name: SWITCH.c
 *
 * Description: Driver's APIs' implementation.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 15-12-2023 (Edited for ARM at 21-02-2024)
 *
 *******************************************************************************/

/* ِIncluding the .h file that contains typedefs for the primitive data types */
#include <HAL/SWITCH.h>
#include <LIB/std_types.h>
#include <MCAL/GPIO.h>
#include <MCAL/RCC.h>

/****************************************************************************************/
/*									MACROS Declaration									*/
/****************************************************************************************/

#define PIN_Connection_InternalPullUp			GPIO_MODE_INPUT_PU
#define PIN_Connection_ExternalPullUp			GPIO_MODE_INPUT_FLOAT

#define PIN_Connection_InternalPullDown			GPIO_MODE_INPUT_PD
#define PIN_Connection_ExternalPullDown			GPIO_MODE_INPUT_FLOAT


/****************************************************************************************/
/*									Global Variables									*/
/****************************************************************************************/

extern SWITCH_strSwitchConfig_t arrayofSwitchesConfig [NUM_OF_SWITCHES];

/****************************************************************************************/
/*									APIs Implementation									*/
/****************************************************************************************/

/**
 *@brief : Function to Set the pins to which the switches are connected to.
 *@param : Array of structures that contains configuration of the switches.
 *@return: Error Status.
 */
SWITCH_enuErrorStatus_t SWITCH_enuInit(void)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	SWITCH_enuErrorStatus_t LOC_enuErrorStatus = SWITCH_enuOk;

	/* Check if the entered pointer is a NULL pointer, we will not be able to dereference it */
	if (arrayofSwitchesConfig == NULL_PTR)
	{
		LOC_enuErrorStatus = SWITCH_enuNullPointer;
	}
	else
	{
		uint8_t LOC_uint8counter;
		GPIO_strPinConfig_t LOC_SwitchConfig;
		for(LOC_uint8counter = 0; LOC_uint8counter < NUM_OF_SWITCHES; LOC_uint8counter++)
		{

			/* Checking the LED's pin's parameters */

			if ((arrayofSwitchesConfig[LOC_uint8counter].SW_port_number >= GPIO_PORTA)\
					&& (arrayofSwitchesConfig[LOC_uint8counter].SW_port_number <= GPIO_PORTH)\
					&& (arrayofSwitchesConfig[LOC_uint8counter].SW_pin_number >= GPIO_PIN0)\
					&& (arrayofSwitchesConfig[LOC_uint8counter].SW_pin_number <= GPIO_PIN15)
					&& (arrayofSwitchesConfig[LOC_uint8counter].SW_connection_method >= SWITCH_enuInternalPullUpConnection)\
					&& (arrayofSwitchesConfig[LOC_uint8counter].SW_connection_method <= SWITCH_enuExternalPullDownConnection))
			{
				/* If everything is OK, We could configure the pins now */

				/* First enable the GPIOx peripheral to which the current LED is connected */
				switch (arrayofSwitchesConfig[LOC_uint8counter].SW_port_number)
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
					/* The code won't reach here as We already validated the input Switch's PORT */
					break;
				}
				/* Now check that the GPIO peripheral is enabled */
				if (LOC_enuErrorStatus == RCC_enuOk)
				{
					/* Till now, everything is OK, We can start configure the pins */

					LOC_SwitchConfig.GPIO_port = arrayofSwitchesConfig[LOC_uint8counter].SW_port_number;
					LOC_SwitchConfig.GPIO_pin = arrayofSwitchesConfig[LOC_uint8counter].SW_pin_number;
					LOC_SwitchConfig.GPIO_speed = GPIO_SPEED_HIGH;

					/* Now We will switch (search/loop) on the Switch's connection type,
					 * to configure the pin with the correct input type */

					switch (arrayofSwitchesConfig[LOC_uint8counter].SW_connection_method)
					{
					case SWITCH_enuInternalPullUpConnection:
						LOC_SwitchConfig.GPIO_mode = PIN_Connection_InternalPullUp;
						break;
					case SWITCH_enuExternalPullUpConnection:
						LOC_SwitchConfig.GPIO_mode = PIN_Connection_ExternalPullUp;
						break;
					case SWITCH_enuInternalPullDownConnection:
						LOC_SwitchConfig.GPIO_mode = PIN_Connection_InternalPullDown;
						break;
					case SWITCH_enuExternalPullDownConnection:
						LOC_SwitchConfig.GPIO_mode = PIN_Connection_ExternalPullDown;
						break;
					default:
						/* The code won't reach here as We already validated the input Switch's Connection method */
						break;
					}

					/* Passing the configurations assigned in "LOC_SwitchConfig" to the GPIO initialize function
					 * to initialize the pin */
					LOC_enuErrorStatus = GPIO_enuInitPin(&LOC_SwitchConfig);

					/* Check that the last Switch's pin is Initially configured correctly */
					if (LOC_enuErrorStatus == GPIO_enuOk)
					{
						/* We managed to initialize this Switch correctly, continue */
					}
					else
					{
						/* The last Switch's pin could not be Initially configured correctly for some reasons */
						LOC_enuErrorStatus = SWITCH_enuNotOk;
						/* Stop looping on the LEDs, return error */
						break;
					}
				}
				else
				{
					/* The last Switch's PORT could not be enabled for some reasons */
					LOC_enuErrorStatus = SWITCH_enuNotOk;
					/* Stop looping on the Switches, return error */
					break;
				}
			}
			else
			{
				/* One or more of one of the Switches' pin's parameters is wrong */
				LOC_enuErrorStatus = SWITCH_enuNotOk;
				/* Stop looping on the Switches, return error */
				break;
			}
		}
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to check if the switch is pressed or not.
 *@param : Name of the switch you want to check, address of a local variable to assign state of the switch in it.
 *@return: Error Status.
 */
SWITCH_enuErrorStatus_t SWITCH_enuGetSwitchState(uint8_t copy_uint8SwitchName, SWITCH_enuSwitchState_t* Add_enuSwitchState)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	SWITCH_enuErrorStatus_t LOC_enuErrorStatus = SWITCH_enuOk;

	/* Check if the entered pointer is a NULL pointer, we will not be able to dereference it */
	if (Add_enuSwitchState == NULL_PTR)
	{
		LOC_enuErrorStatus = SWITCH_enuNullPointer;
	}
	/* Check that the user entered one of the Listed Switches or not */
	else if (copy_uint8SwitchName >= NUM_OF_SWITCHES)
	{
		LOC_enuErrorStatus = SWITCH_enuWrongSwitchName;
	}
	else
	{
		/* Seems like the user entered valid parameters, We can Read the switch's pin's state */

		/* Local variable used to be passed to "GPIO_enuGetPinVal" function to assign in it the switch state */
		uint32_t u32SwitchPinState = 0;

		/* Read the error state when reading the value of the pin which the switch is connected to */
		LOC_enuErrorStatus = GPIO_enuGetPinVal(arrayofSwitchesConfig[copy_uint8SwitchName].SW_port_number,\
												arrayofSwitchesConfig[copy_uint8SwitchName].SW_pin_number,\
												&u32SwitchPinState);

		switch(arrayofSwitchesConfig[copy_uint8SwitchName].SW_connection_method)
		{
		/* Whether the pull up connection is internally or externally, the state of the pin in both cases
		 * reflexes the same switch's state */
		case SWITCH_enuInternalPullUpConnection:
		case SWITCH_enuExternalPullUpConnection:
			/* Check if the function "GPIO_enuGetPinVal" works properly and exits after assigning the value of
			 * the pin in "u32SwitchPinState", and check if the button is pressed or not, and since it is connected
			 * with pull up resistance, so when it is pressed the value of the button will be LOW, so we will check on
			 * the LOW state */
			if ((GPIO_enuGetPinVal(arrayofSwitchesConfig[copy_uint8SwitchName].SW_port_number,\
									arrayofSwitchesConfig[copy_uint8SwitchName].SW_pin_number,\
									&u32SwitchPinState) == GPIO_enuOk)\
					&& (u32SwitchPinState == GPIO_PIN_VAL_LOW))
			{
				*Add_enuSwitchState = SWITCH_enuIS_PRESSED;
			}
			else
			{
				*Add_enuSwitchState = SWITCH_enuNOT_PRESSED;
			}
			break;

			/* Whether the pull down connection is internally or externally, the state of the pin in both cases
			 * reflexes the same switch's state */
		case SWITCH_enuInternalPullDownConnection:
		case SWITCH_enuExternalPullDownConnection:
			/* Check if the function "GPIO_enuGetPinVal" works properly and exits after assigning the value of
			 * the pin in "u32SwitchPinState", and check if the button is pressed or not, and since it is connected
			 * with pull down resistance, so when it is pressed the value of the button will be HIGH, so we
			 * will check on the HIGH state */
			if ((GPIO_enuGetPinVal(arrayofSwitchesConfig[copy_uint8SwitchName].SW_port_number,\
									arrayofSwitchesConfig[copy_uint8SwitchName].SW_pin_number,\
									&u32SwitchPinState) == GPIO_enuOk)\
					&& (u32SwitchPinState == GPIO_PIN_VAL_HIGH))
			{
				*Add_enuSwitchState = SWITCH_enuIS_PRESSED;
			}
			else
			{
				*Add_enuSwitchState = SWITCH_enuNOT_PRESSED;
			}
			break;
		default:
			/* The code won't reach here as We already validated the input Switch's Connection method */
			break;
		}
	}

	return LOC_enuErrorStatus;
}



/**
 *@brief : Runnable with periodicity 30 milliseconds.
 *@param : void.
 *@return: void.
 */
void RUNNABLE_SWITCH_getSwitchState(void)
{
	uint32_t iterator;
}
