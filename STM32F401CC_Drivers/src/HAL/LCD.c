/******************************************************************************
 *
 * Module: 	LCD driver to: 	- Initialize DIO pins to which the LCD is connected to.
 * 							- Displaying what the user wants.
 *
 * Supported Models:	- 16 x 2 Character LCD.
 *
 * File Name: LCD.c
 *
 * Description: Driver's APIs' implementation.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 01-01-2024
 *
 *******************************************************************************/

#include <MCAL/GPIO.h>
#include <MCAL/RCC.h>
#include "HAL/LCD.h"


/* Check first if the user entered an invalid data bits mode */
#if ((LCD_DATA_BITS_MODE != LCD_FOUR_BITS_MODE) && (LCD_DATA_BITS_MODE != LCD_EIGHT_BITS_MODE))

#error "INVALID DATA BITS MODE is selected :(\nIt must be either LCD_FOUR_BITS_MODE or LCD_EIGHT_BITS_MODE"

#else


#define LCD_CGRAM_START_ADDRESS		0x40
#define LCD_DDRAM_START_ADDRESS		0x80

#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1		0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2		0x32


/****************************************************************************************/
/*									APIs Implementation									*/
/****************************************************************************************/

/**
 *@brief : Function to Set the pins to which the LCD is connected to, and to initialize the LCD.
 *@param : void.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumInit(void)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	LCD_enumError_t LOC_enumErrorState = LCD_enumOk;

	if (arrayofLCDPinConfig == NULL_PTR)
	{
		LOC_enumErrorState = LCD_enumNullPointer;
	}
	else
	{
		uint8_t LOC_uint8counter;
		PORT_strPinConfig_t LOC_LCDPinConfig;

#if (LCD_DATA_BITS_MODE == LCD_FOUR_BITS_MODE)

		/* Setting the pins as an output low pins */
		for(LOC_uint8counter = D4_4BITMODE; LOC_uint8counter <= E_4BITMODE; LOC_uint8counter++)
		{
			LOC_LCDPinConfig.port_number = arrayofLCDPinConfig[LOC_uint8counter].LCD_port_number;
			LOC_LCDPinConfig.pin_number = arrayofLCDPinConfig[LOC_uint8counter].LCD_pin_number;
			LOC_LCDPinConfig.configuration_type = PORT_enumPinOutputLow;

			LOC_enumErrorState = PORT_enumSetPinConfig(&LOC_LCDPinConfig);

			/* Check that every pin is configured without any problem */
			if (LOC_enumErrorState == PORT_enumOk)
			{
				/* Since everything is OK, then continue */
			}
			else
			{
				/* Seems that something wrong happened during the configurations of one of the pins */
				LOC_enumErrorState = LCD_enumWrongPinConfiguration;
				break;
			}
		}

		/* Delay for 30 milliseconds after the power on */
		DIO_DelayMs(30);

		/* These two commands are written in the data sheet */
		LCD_enumWriteCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
		DIO_DelayMs(5);
		LCD_enumWriteCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
		DIO_DelayMs(1);

		/* Function Set */
		/* use 2-lines LCD + 4-bits Data Mode + 5x7 dot display Mode */
		LCD_enumWriteCommand(LCD_FourBitMode_2LineDisplay_5x7);
		DIO_DelayMs(1);

		/* Display ON/OFF Control */
		/* Turn the display ON, turn the cursor ON, and turn the blinking on */
		LCD_enumWriteCommand(LCD_DisplayON_CursorON_BlinkON);
		DIO_DelayMs(1);

		/* Display Clear */
		LCD_enumWriteCommand(LCD_ClearDisplay);
		DIO_DelayMs(2);

		/* Entry Mode Set */
		LCD_enumWriteCommand(LCD_EntryMode_CursorIncrement_ShiftOFF);

		/* End of the software initialization */


#elif (LCD_DATA_BITS_MODE == LCD_EIGHT_BITS_MODE)


		/* Setting the pins as an output low pins */
		for(LOC_uint8counter = D0; LOC_uint8counter <= E; LOC_uint8counter++)
		{
			LOC_LCDPinConfig.port_number = arrayofLCDPinConfig[LOC_uint8counter].LCD_port_number;
			LOC_LCDPinConfig.pin_number = arrayofLCDPinConfig[LOC_uint8counter].LCD_pin_number;
			LOC_LCDPinConfig.configuration_type = PORT_enumPinOutputLow;

			LOC_enumErrorState = PORT_enumSetPinConfig(&LOC_LCDPinConfig);

			/* Check that every pin is configured without any problem */
			if (LOC_enumErrorState == PORT_enumOk)
			{
				/* Since everything is OK, then continue */
			}
			else
			{
				/* Seems that something wrong happened during the configurations of one of the pins */
				LOC_enumErrorState = LCD_enumWrongPinConfiguration;
				break;
			}
		}

		/* Delay for 30 milliseconds after the power on */
		DIO_DelayMs(30);

		/* Function Set */
		/* use 2-lines LCD + 8-bits Data Mode + 5x7 dot display Mode */
		LCD_enumWriteCommand(LCD_EightBitMode_2LineDisplay_5x7);
		DIO_DelayMs(1);

		/* Display ON/OFF Control */
		/* Turn the display ON, turn the cursor ON, and turn the blinking on */
		LCD_enumWriteCommand(LCD_DisplayON_CursorON_BlinkON);
		DIO_DelayMs(1);

		/* Display Clear */
		LCD_enumWriteCommand(LCD_ClearDisplay);
		DIO_DelayMs(2);

		/* Entry Mode Set */
		LCD_enumWriteCommand(LCD_EntryMode_CursorIncrement_ShiftOFF);

		/* End of the software initialization */

#endif /* #if (LCD_DATA_BITS_MODE == LCD_FOUR_BITS_MODE) */

	}

	return LOC_enumErrorState;
}
/****************************************************************************************/
/****************************************************************************************/
/**
 *@brief : Function to Write data to the LCD.
 *@param : Data you want to send.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumWriteData(uint8 Copy_uint8Data)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	LCD_enumError_t LOC_enumErrorState = LCD_enumOk;



#if (LCD_DATA_BITS_MODE == LCD_FOUR_BITS_MODE)

	/* Set the value of RS pin as output low as we are sending a command */
	LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[RS_4BITMODE].LCD_port_number,arrayofLCDPinConfig[RS_4BITMODE].LCD_pin_number,DIO_enumPinLogicHigh);

	/* Check that the pin configuration is done properly */
	if (LOC_enumErrorState == DIO_enumOk)
	{
		/* Small delay mentioned in the data sheet */
		DIO_DelayMs(1);

		/* Set the value of R/w pin as output low as we are writing */
		LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[RW_4BITMODE].LCD_port_number,arrayofLCDPinConfig[RW_4BITMODE].LCD_pin_number,DIO_enumPinLogicLow);

		/* Check that the pin configuration is done properly */
		if (LOC_enumErrorState == DIO_enumOk)
		{
			/* Small delay mentioned in the data sheet */
			DIO_DelayMs(1);

			/* Set the value of the E pin to be output low to make pulse on it later once we put the data on the data pins */
			LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[E_4BITMODE].LCD_port_number,arrayofLCDPinConfig[E_4BITMODE].LCD_pin_number,DIO_enumPinLogicLow);

			/* Check that the pin configuration is done properly */
			if (LOC_enumErrorState == DIO_enumOk)
			{
				/* Small delay mentioned in the data sheet */
				DIO_DelayMs(1);

				/* Putting the upper 4-bits data on the data pins of the LCD */
				LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D7_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D7_4BITMODE].LCD_pin_number,( ( Copy_uint8Data & (1<<D7) ) >> D7 ));

				/* Check that the pin configuration is done properly */
				if (LOC_enumErrorState == DIO_enumOk)
				{
					LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D6_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D6_4BITMODE].LCD_pin_number,( ( Copy_uint8Data & (1<<D6) ) >> D6 ));

					/* Check that the pin configuration is done properly */
					if (LOC_enumErrorState == DIO_enumOk)
					{
						LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D5_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D5_4BITMODE].LCD_pin_number,( ( Copy_uint8Data & (1<<D5) ) >> D5 ));

						/* Check that the pin configuration is done properly */
						if (LOC_enumErrorState == DIO_enumOk)
						{
							LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D4_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D4_4BITMODE].LCD_pin_number,( ( Copy_uint8Data & (1<<D4) ) >> D4 ));

							/* Check that the pin configuration is done properly */
							if (LOC_enumErrorState == DIO_enumOk)
							{
								/* ٍSmall delay mentioned in the data sheet */
								DIO_DelayMs(1);

								/* Send a pulse to the E pin to send the data to the LCD */
								LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[E_4BITMODE].LCD_port_number,arrayofLCDPinConfig[E_4BITMODE].LCD_pin_number,DIO_enumPinLogicHigh);

								/* Check that the pin configuration is done properly */
								if (LOC_enumErrorState == DIO_enumOk)
								{
									/* ٍSmall delay mentioned in the data sheet */
									DIO_DelayMs(1);

									/* Send a pulse to the E pin to send the data to the LCD */
									LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[E_4BITMODE].LCD_port_number,arrayofLCDPinConfig[E_4BITMODE].LCD_pin_number,DIO_enumPinLogicLow);

									/* Check that the pin configuration is done properly */
									if (LOC_enumErrorState == DIO_enumOk)
									{
										/* ٍSmall delay mentioned in the data sheet */
										DIO_DelayMs(1);
////
										/* Putting the lower 4-bits data on the data pins of the LCD */
										LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D7_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D7_4BITMODE].LCD_pin_number,( ( Copy_uint8Data & (1<<D3) ) >> D3 ));

										/* Check that the pin configuration is done properly */
										if (LOC_enumErrorState == DIO_enumOk)
										{
											LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D6_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D6_4BITMODE].LCD_pin_number,( ( Copy_uint8Data & (1<<D2) ) >> D2 ));

											/* Check that the pin configuration is done properly */
											if (LOC_enumErrorState == DIO_enumOk)
											{
												LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D5_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D5_4BITMODE].LCD_pin_number,( ( Copy_uint8Data & (1<<D1) ) >> D1 ));

												/* Check that the pin configuration is done properly */
												if (LOC_enumErrorState == DIO_enumOk)
												{
													LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D4_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D4_4BITMODE].LCD_pin_number,( ( Copy_uint8Data & (1<<D0) ) >> D0 ));

													/* Check that the pin configuration is done properly */
													if (LOC_enumErrorState == DIO_enumOk)
													{
														/* ٍSmall delay mentioned in the data sheet */
														DIO_DelayMs(1);

														/* Send a pulse to the E pin to send the data to the LCD */
														LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[E_4BITMODE].LCD_port_number,arrayofLCDPinConfig[E_4BITMODE].LCD_pin_number,DIO_enumPinLogicHigh);

														/* Check that the pin configuration is done properly */
														if (LOC_enumErrorState == DIO_enumOk)
														{
															/* ٍSmall delay mentioned in the data sheet */
															DIO_DelayMs(1);

															/* Send a pulse to the E pin to send the data to the LCD */
															LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[E_4BITMODE].LCD_port_number,arrayofLCDPinConfig[E_4BITMODE].LCD_pin_number,DIO_enumPinLogicLow);

															/* Check that the pin configuration is done properly */
															if (LOC_enumErrorState == DIO_enumOk)
															{
																/* ٍSmall delay mentioned in the data sheet */
																DIO_DelayMs(1);

/////////////////////////////////////////////////

															}
															else
															{
																/* Seems Like wrong pin configuration happened */
																LOC_enumErrorState = LCD_enumWrongPinConfiguration;
															}

														}
														else
														{
															/* Seems Like wrong pin configuration happened */
															LOC_enumErrorState = LCD_enumWrongPinConfiguration;
														}
///
													}
													else
													{
														/* Seems Like wrong pin configuration happened */
														LOC_enumErrorState = LCD_enumWrongPinConfiguration;
													}

												}
												else
												{
													/* Seems Like wrong pin configuration happened */
													LOC_enumErrorState = LCD_enumWrongPinConfiguration;
												}

											}
											else
											{
												/* Seems Like wrong pin configuration happened */
												LOC_enumErrorState = LCD_enumWrongPinConfiguration;
											}

										}
										else
										{
											/* Seems Like wrong pin configuration happened */
											LOC_enumErrorState = LCD_enumWrongPinConfiguration;
										}

									}
									else
									{
										/* Seems Like wrong pin configuration happened */
										LOC_enumErrorState = LCD_enumWrongPinConfiguration;
									}

								}
								else
								{
									/* Seems Like wrong pin configuration happened */
									LOC_enumErrorState = LCD_enumWrongPinConfiguration;
								}

							}
							else
							{
								/* Seems Like wrong pin configuration happened */
								LOC_enumErrorState = LCD_enumWrongPinConfiguration;
							}

						}
						else
						{
							/* Seems Like wrong pin configuration happened */
							LOC_enumErrorState = LCD_enumWrongPinConfiguration;
						}

					}
					else
					{
						/* Seems Like wrong pin configuration happened */
						LOC_enumErrorState = LCD_enumWrongPinConfiguration;
					}

				}
				else
				{
					/* Seems Like wrong pin configuration happened */
					LOC_enumErrorState = LCD_enumWrongPinConfiguration;
				}


#elif (LCD_DATA_BITS_MODE == LCD_EIGHT_BITS_MODE)


				/* Set the value of RS pin as output low as we are sending a command */
				LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[RS].LCD_port_number,arrayofLCDPinConfig[RS].LCD_pin_number,DIO_enumPinLogicHigh);

				/* Check that the pin configuration is done properly */
				if (LOC_enumErrorState == DIO_enumOk)
				{
					/* Small delay mentioned in the data sheet */
					DIO_DelayMs(1);

					/* Set the value of R/w pin as output low as we are writing */
					LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[RW].LCD_port_number,arrayofLCDPinConfig[RW].LCD_pin_number,DIO_enumPinLogicLow);

					/* Check that the pin configuration is done properly */
					if (LOC_enumErrorState == DIO_enumOk)
					{
						/* Small delay mentioned in the data sheet */
						DIO_DelayMs(1);

						/* Set the value of the E pin to be output low to make pulse on it later once we put the data on the data pins */
						LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[E].LCD_port_number,arrayofLCDPinConfig[E].LCD_pin_number,DIO_enumPinLogicLow);

						/* Check that the pin configuration is done properly */
						if (LOC_enumErrorState == DIO_enumOk)
						{
							/* Small delay mentioned in the data sheet */
							DIO_DelayMs(1);
				/* Putting the upper 4-bits data on the data pins of the LCD */
				LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D7].LCD_port_number,arrayofLCDPinConfig[D7].LCD_pin_number,( ( Copy_uint8Data & (1<<D7) ) >> D7 ));

				/* Check that the pin configuration is done properly */
				if (LOC_enumErrorState == DIO_enumOk)
				{
					LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D6].LCD_port_number,arrayofLCDPinConfig[D6].LCD_pin_number,( ( Copy_uint8Data & (1<<D6) ) >> D6 ));

					/* Check that the pin configuration is done properly */
					if (LOC_enumErrorState == DIO_enumOk)
					{
						LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D5].LCD_port_number,arrayofLCDPinConfig[D5].LCD_pin_number,( ( Copy_uint8Data & (1<<D5) ) >> D5 ));

						/* Check that the pin configuration is done properly */
						if (LOC_enumErrorState == DIO_enumOk)
						{
							LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D4].LCD_port_number,arrayofLCDPinConfig[D4].LCD_pin_number,( ( Copy_uint8Data & (1<<D4) ) >> D4 ));

							/* Check that the pin configuration is done properly */
							if (LOC_enumErrorState == DIO_enumOk)
							{
								LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D3].LCD_port_number,arrayofLCDPinConfig[D3].LCD_pin_number,( ( Copy_uint8Data & (1<<D3) ) >> D3 ));

								/* Check that the pin configuration is done properly */
								if (LOC_enumErrorState == DIO_enumOk)
								{
									LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D2].LCD_port_number,arrayofLCDPinConfig[D2].LCD_pin_number,( ( Copy_uint8Data & (1<<D2) ) >> D2 ));

									/* Check that the pin configuration is done properly */
									if (LOC_enumErrorState == DIO_enumOk)
									{
										LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D1].LCD_port_number,arrayofLCDPinConfig[D1].LCD_pin_number,( ( Copy_uint8Data & (1<<D1) ) >> D1 ));

										/* Check that the pin configuration is done properly */
										if (LOC_enumErrorState == DIO_enumOk)
										{
											LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[D0].LCD_port_number,arrayofLCDPinConfig[D0].LCD_pin_number,( ( Copy_uint8Data & (1<<D0) ) >> D0 ));

											/* Check that the pin configuration is done properly */
											if (LOC_enumErrorState == DIO_enumOk)
											{

												/* ٍSmall delay mentioned in the data sheet */
												DIO_DelayMs(1);

												/* Send a pulse to the E pin to send the data to the LCD */
												LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[E].LCD_port_number,arrayofLCDPinConfig[E].LCD_pin_number,DIO_enumPinLogicHigh);

												/* Check that the pin configuration is done properly */
												if (LOC_enumErrorState == DIO_enumOk)
												{
													/* ٍSmall delay mentioned in the data sheet */
													DIO_DelayMs(1);

													/* Send a pulse to the E pin to send the data to the LCD */
													LOC_enumErrorState = DIO_enumSetPin(arrayofLCDPinConfig[E].LCD_port_number,arrayofLCDPinConfig[E].LCD_pin_number,DIO_enumPinLogicLow);

													/* Check that the pin configuration is done properly */
													if (LOC_enumErrorState == DIO_enumOk)
													{
														/* ٍSmall delay mentioned in the data sheet */
														DIO_DelayMs(1);
													}
													else
													{
														/* Seems Like wrong pin configuration happened */
														LOC_enumErrorState = LCD_enumWrongPinConfiguration;
													}
												}
												else
												{
													/* Seems Like wrong pin configuration happened */
													LOC_enumErrorState = LCD_enumWrongPinConfiguration;
												}
											}
											else
											{
												/* Seems Like wrong pin configuration happened */
												LOC_enumErrorState = LCD_enumWrongPinConfiguration;
											}
										}
										else
										{
											/* Seems Like wrong pin configuration happened */
											LOC_enumErrorState = LCD_enumWrongPinConfiguration;
										}
									}
									else
									{
										/* Seems Like wrong pin configuration happened */
										LOC_enumErrorState = LCD_enumWrongPinConfiguration;
									}
								}
								else
								{
									/* Seems Like wrong pin configuration happened */
									LOC_enumErrorState = LCD_enumWrongPinConfiguration;
								}
							}
							else
							{
								/* Seems Like wrong pin configuration happened */
								LOC_enumErrorState = LCD_enumWrongPinConfiguration;
							}
						}
						else
						{
							/* Seems Like wrong pin configuration happened */
							LOC_enumErrorState = LCD_enumWrongPinConfiguration;
						}
					}
					else
					{
						/* Seems Like wrong pin configuration happened */
						LOC_enumErrorState = LCD_enumWrongPinConfiguration;
					}
				}
				else
				{
					/* Seems Like wrong pin configuration happened */
					LOC_enumErrorState = LCD_enumWrongPinConfiguration;
				}

#endif /* #if (LCD_DATA_BITS_MODE == LCD_FOUR_BITS_MODE) */

			}
			else
			{
				/* Seems Like wrong pin configuration happened */
				LOC_enumErrorState = LCD_enumWrongPinConfiguration;
			}

		}
		else
		{
			/* Seems Like wrong pin configuration happened */
			LOC_enumErrorState = LCD_enumWrongPinConfiguration;
		}

	}
	else
	{
		/* Seems Like wrong pin configuration happened */
		LOC_enumErrorState = LCD_enumWrongPinConfiguration;
	}


	return LOC_enumErrorState;
}
/****************************************************************************************/
/****************************************************************************************/
/**
 *@brief : Function to Write command to the LCD.
 *@param : Command you want to send.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumWriteCommand(uint8 Copy_uint8Command)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	LCD_enumError_t LOC_enumErrorState = LCD_enumOk;



#if (LCD_DATA_BITS_MODE == LCD_FOUR_BITS_MODE)

	/* Set the value of RS pin as output low as we are sending a command */
	DIO_enumSetPin(arrayofLCDPinConfig[RS_4BITMODE].LCD_port_number,arrayofLCDPinConfig[RS_4BITMODE].LCD_pin_number,DIO_enumPinLogicLow);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);

	/* Set the value of R/w pin as output low as we are writing */
	DIO_enumSetPin(arrayofLCDPinConfig[RW_4BITMODE].LCD_port_number,arrayofLCDPinConfig[RW_4BITMODE].LCD_pin_number,DIO_enumPinLogicLow);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);
	/* Set the value of the E pin to be output low to make pulse on it later once we put the data on the data pins */
	DIO_enumSetPin(arrayofLCDPinConfig[E_4BITMODE].LCD_port_number,arrayofLCDPinConfig[E_4BITMODE].LCD_pin_number,DIO_enumPinLogicLow);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);

	/* Putting the upper 4-bits data on the data pins of the LCD */
	DIO_enumSetPin(arrayofLCDPinConfig[D7_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D7_4BITMODE].LCD_pin_number,( ( Copy_uint8Command & (1<<D7) ) >> D7 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D6_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D6_4BITMODE].LCD_pin_number,( ( Copy_uint8Command & (1<<D6) ) >> D6 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D5_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D5_4BITMODE].LCD_pin_number,( ( Copy_uint8Command & (1<<D5) ) >> D5 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D4_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D4_4BITMODE].LCD_pin_number,( ( Copy_uint8Command & (1<<D4) ) >> D4 ));
	/* ٍSmall delay mentioned in the data sheet */
	DIO_DelayMs(1);

	/* Send a pulse to the E pin to send the data to the LCD */
	DIO_enumSetPin(arrayofLCDPinConfig[E_4BITMODE].LCD_port_number,arrayofLCDPinConfig[E_4BITMODE].LCD_pin_number,DIO_enumPinLogicHigh);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);
	DIO_enumSetPin(arrayofLCDPinConfig[E_4BITMODE].LCD_port_number,arrayofLCDPinConfig[E_4BITMODE].LCD_pin_number,DIO_enumPinLogicLow);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);

	/* Putting the lower 4-bits data on the data pins of the LCD */
	DIO_enumSetPin(arrayofLCDPinConfig[D7_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D7_4BITMODE].LCD_pin_number,( ( Copy_uint8Command & (1<<D3) ) >> D3 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D6_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D6_4BITMODE].LCD_pin_number,( ( Copy_uint8Command & (1<<D2) ) >> D2 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D5_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D5_4BITMODE].LCD_pin_number,( ( Copy_uint8Command & (1<<D1) ) >> D1 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D4_4BITMODE].LCD_port_number,arrayofLCDPinConfig[D4_4BITMODE].LCD_pin_number,( ( Copy_uint8Command & (1<<D0) ) >> D0 ));
	/* ٍSmall delay mentioned in the data sheet */
	DIO_DelayMs(1);

	/* Send a pulse to the E pin to send the data to the LCD */
	DIO_enumSetPin(arrayofLCDPinConfig[E_4BITMODE].LCD_port_number,arrayofLCDPinConfig[E_4BITMODE].LCD_pin_number,DIO_enumPinLogicHigh);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);
	DIO_enumSetPin(arrayofLCDPinConfig[E_4BITMODE].LCD_port_number,arrayofLCDPinConfig[E_4BITMODE].LCD_pin_number,DIO_enumPinLogicLow);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);


#elif (LCD_DATA_BITS_MODE == LCD_EIGHT_BITS_MODE)

	/* Set the value of RS pin as output low as we are sending a command */
	DIO_enumSetPin(arrayofLCDPinConfig[RS].LCD_port_number,arrayofLCDPinConfig[RS].LCD_pin_number,DIO_enumPinLogicLow);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);

	/* Set the value of R/w pin as output low as we are writing */
	DIO_enumSetPin(arrayofLCDPinConfig[RW].LCD_port_number,arrayofLCDPinConfig[RW].LCD_pin_number,DIO_enumPinLogicLow);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);
	/* Set the value of the E pin to be output low to make pulse on it later once we put the data on the data pins */
	DIO_enumSetPin(arrayofLCDPinConfig[E].LCD_port_number,arrayofLCDPinConfig[E].LCD_pin_number,DIO_enumPinLogicLow);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);

	/* Putting the data on the data pins of the LCD */
	DIO_enumSetPin(arrayofLCDPinConfig[D7].LCD_port_number,arrayofLCDPinConfig[D7].LCD_pin_number,( ( Copy_uint8Command & (1<<D7) ) >> D7 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D6].LCD_port_number,arrayofLCDPinConfig[D6].LCD_pin_number,( ( Copy_uint8Command & (1<<D6) ) >> D6 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D5].LCD_port_number,arrayofLCDPinConfig[D5].LCD_pin_number,( ( Copy_uint8Command & (1<<D5) ) >> D5 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D4].LCD_port_number,arrayofLCDPinConfig[D4].LCD_pin_number,( ( Copy_uint8Command & (1<<D4) ) >> D4 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D3].LCD_port_number,arrayofLCDPinConfig[D3].LCD_pin_number,( ( Copy_uint8Command & (1<<D3) ) >> D3 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D2].LCD_port_number,arrayofLCDPinConfig[D2].LCD_pin_number,( ( Copy_uint8Command & (1<<D2) ) >> D2 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D1].LCD_port_number,arrayofLCDPinConfig[D1].LCD_pin_number,( ( Copy_uint8Command & (1<<D1) ) >> D1 ));
	DIO_enumSetPin(arrayofLCDPinConfig[D0].LCD_port_number,arrayofLCDPinConfig[D0].LCD_pin_number,( ( Copy_uint8Command & (1<<D0) ) >> D0 ));
	/* ٍSmall delay mentioned in the data sheet */
	DIO_DelayMs(1);

	/* Send a pulse to the E pin to send the data to the LCD */
	DIO_enumSetPin(arrayofLCDPinConfig[E].LCD_port_number,arrayofLCDPinConfig[E].LCD_pin_number,DIO_enumPinLogicHigh);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);
	DIO_enumSetPin(arrayofLCDPinConfig[E].LCD_port_number,arrayofLCDPinConfig[E].LCD_pin_number,DIO_enumPinLogicLow);
	/* Small delay mentioned in the data sheet */
	DIO_DelayMs(1);


#endif /* #if (LCD_DATA_BITS_MODE == LCD_FOUR_BITS_MODE) */


	return LOC_enumErrorState;
}
/****************************************************************************************/
/****************************************************************************************/
/**
 *@brief : Function to go to certain location in the DDRAM.
 *@param : The row number, and the column number in that row.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumGotoDDRAM_XY(LCD_enumRowNumber_t Copy_uint8X, LCD_enumColumnNumber_t Copy_uint8Y)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	LCD_enumError_t LOC_enumErrorState = LCD_enumOk;

	if ((Copy_uint8X < LCD_enumFirstRow) || (Copy_uint8X > LCD_enumSecondRow))
	{
		LOC_enumErrorState = LCD_enumWrongRowNumber;
	}
	else if ((Copy_uint8Y < LCD_enumColumn_1) || (Copy_uint8Y > LCD_enumColumn_40))
	{
		LOC_enumErrorState = LCD_enumWrongColumnNumber;
	}
	else
	{
		uint8 LOC_uint8Location;
		/* Seems like the inputs are correct, then let us go to the required location */

		if (Copy_uint8X == LCD_enumFirstRow)
		{
			LOC_uint8Location = Copy_uint8Y;
		}
		else
		{
			/* Then Copy_uint8X equals LCD_enumSecondRow */

			LOC_uint8Location = 0x40 + Copy_uint8Y;
		}

		/* Send a command to the LCD to make the cursor go to the required location */
		LCD_enumWriteCommand(LCD_DDRAM_START_ADDRESS + LOC_uint8Location);
	}


	return LOC_enumErrorState;
}
/****************************************************************************************/
/****************************************************************************************/
/**
 *@brief : Function to Print certain number on the LCD.
 *@param : Number you want to print.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumWriteNumber(uint64 Copy_uint64Number)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	LCD_enumError_t LOC_enumErrorState = LCD_enumOk;

	uint64 LOC_uint64InvertedImage = 0;
	uint8 LOC_uint8Digit;

	/* Its usage is to check if the unit digit in the input number is zero or not */
	uint8 LOC_uint8ZeroInUnitsChecker = 0;

	while (Copy_uint64Number != 0)
	{
		/* Save an inverted image of the input in a local variable to b able to print it properly */
		LOC_uint64InvertedImage *= 10;
		LOC_uint64InvertedImage += Copy_uint64Number % 10;

		/* If the unit digit in the input number is zero then raise the Zero checker flag */
		if (LOC_uint64InvertedImage == 0)
		{
			LOC_uint8ZeroInUnitsChecker = 1;
		}
		//LOC_uint64InvertedImage *= 10;
		Copy_uint64Number /= 10;
	}

	while (LOC_uint64InvertedImage != 0)
	{
		/* Send the inverted number to be printed digit-by-digit */
		LOC_uint8Digit = LOC_uint64InvertedImage % 10;
		LCD_enumWriteData(LOC_uint8Digit + 48);
		LOC_uint64InvertedImage /= 10;
	}

	/* If the Zero checker flag is set then print Zero as the last thing to be printed */
	if (LOC_uint8ZeroInUnitsChecker == 1)
	{
		LCD_enumWriteData(0 + 48);
		LOC_uint8ZeroInUnitsChecker = 0;
	}
	else
	{
		/* Do Nothing */
	}

	return LOC_enumErrorState;
}
/****************************************************************************************/
/****************************************************************************************/
/**
 *@brief : Function to Print certain string on the LCD.
 *@param : String you want to print, and the length of that string.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumWriteString(uint8* Copy_puint8Pattern)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	LCD_enumError_t LOC_enumErrorState = LCD_enumOk;

	if (Copy_puint8Pattern == NULL_PTR)
	{
		LOC_enumErrorState = LCD_enumNullPointer;
	}
	else
	{
		uint8 LOC_uint8Counter = 0;
		while(Copy_puint8Pattern[LOC_uint8Counter] != '\0')
		{
			LCD_enumWriteData(Copy_puint8Pattern[LOC_uint8Counter]);
			LOC_uint8Counter++;
		}
	}

	return LOC_enumErrorState;
}
/****************************************************************************************/
/****************************************************************************************/
/**
 *@brief : Function to Save Special character in the CGRAM, and then to print it on the LCD.
 *@param : Special character you want to print, the block number that character will be saved inside in the
 *			CGRAM, then (for the printing purpose) the row and column number in which that character will
 *			be displayed.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumDisplaySpecialPattern(uint8* Copy_puint8SpecialChar, LCD_enumBlockNumber_t Copy_uint8CGRAMBlockNumber, LCD_enumRowNumber_t Copy_uint8X, LCD_enumColumnNumber_t Copy_uint8Y)
{
	/* A local variable to assign the error state inside it and use only one return in the whole function
	 * through returning the value of this local variable.
	 * Initially we assume that everything is OK, if not its value will be changed according to a definite error type */
	LCD_enumError_t LOC_enumErrorState = LCD_enumOk;

	/* Some Validations to check that every input is a valid one */
	if (Copy_puint8SpecialChar == NULL_PTR)
	{
		LOC_enumErrorState = LCD_enumNullPointer;
	}
	else if ((Copy_uint8CGRAMBlockNumber < LCD_enumBlockNumber_1) || (Copy_uint8CGRAMBlockNumber > LCD_enumBlockNumber_8))
	{
		LOC_enumErrorState = LCD_enumWrongBlockNumber;
	}
	else if ((Copy_uint8X < LCD_enumFirstRow) || (Copy_uint8X > LCD_enumSecondRow))
	{
		LOC_enumErrorState = LCD_enumWrongRowNumber;
	}
	else if ((Copy_uint8Y < LCD_enumColumn_1) || (Copy_uint8Y > LCD_enumColumn_40))
	{
		LOC_enumErrorState = LCD_enumWrongColumnNumber;
	}
	else
	{
		/* Seems that everything in inputs is OK, let us start our work :) */

		/* Since that each block in CGRAM is consisted of 8 rows, so to go to the proper location (the beginning
		 * of the block) we need to shift forward by 8 for each block */
		uint8 LOC_uint8Location = Copy_uint8CGRAMBlockNumber * 8;
		uint8 LOC_uint8Counter;

		/* Go to the specified block to start save the input pattern in it */
		LCD_enumWriteCommand(LOC_uint8Location + LCD_CGRAM_START_ADDRESS);

		/* Saving the input pattern inside the block */
		for (LOC_uint8Counter = 0; LOC_uint8Counter < 8; LOC_uint8Counter++)
		{
			LCD_enumWriteData(Copy_puint8SpecialChar[LOC_uint8Counter]);
		}

		/* Now after the pattern is saved in the block, let's print it :) */

		LCD_enumGotoDDRAM_XY(Copy_uint8X,Copy_uint8Y);

		LCD_enumWriteData(Copy_uint8CGRAMBlockNumber);

	}

	return LOC_enumErrorState;
}



#endif /* #if ((LCD_DATA_BITS_MODE != LCD_FOUR_BITS_MODE) && (LCD_DATA_BITS_MODE != LCD_EIGHT_BITS_MODE)) */
