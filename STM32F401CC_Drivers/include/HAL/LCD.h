/******************************************************************************
 *
 * Module: 	LCD driver to: 	- Initialize DIO pins to which the LCD is connected to.
 * 							- Displaying what the user wants.
 *
 * Supported Models:	- 16 x 2 Character LCD.
 *
 * File Name: LCD.h
 *
 * Description: Driver's APIs' prototypes and typedefs' declaration.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 01-01-2024
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/* ِIncluding the .h file that contains typedefs for the primitive data types */
#include "LIB/std_types.h"

/* ِIncluding the .h file that contains all configurations */
#include "CFG/LCD_cfg.h"

/****************************************************************************************/
/*									extern Variables									*/
/****************************************************************************************/

#if (LCD_DATA_BITS_MODE == LCD_EIGHT_BITS_MODE)
extern LCD_strLCDPinConfig_t arrayofLCDPinConfig [11];
#elif (LCD_DATA_BITS_MODE == LCD_FOUR_BITS_MODE)
extern LCD_strLCDPinConfig_t arrayofLCDPinConfig [7];
#endif

extern uint8_t customChar1[8];
extern uint8_t customChar2[8];
extern uint8_t customChar3[8];
extern uint8_t customChar4[8];
extern uint8_t customChar5[8];
extern uint8_t customChar6[8];
extern uint8_t customChar7[8];
extern uint8_t customChar8[8];


/****************************************************************************************/
/*									Macros Declaration									*/
/****************************************************************************************/

/**
 *@brief : Clear the display and return the cursor to the upper left corner in the LCD.
 */
#define	LCD_ClearDisplay							0x01
/**
 *@brief : Return the cursor to the upper left corner in the LCD and return the display to its original position.
 */
#define	LCD_ReturnHome								0x02
/**
 *@brief : The cursor will be decremented one position backward every time you type something.
 */
#define LCD_EntryMode_CursorDecrement_ShiftOFF		0x04
/**
 *@brief : The cursor will be incremented one position forward every time you type something.
 */
#define LCD_EntryMode_CursorIncrement_ShiftOFF		0x06
/**
 *@brief : It looks as if the cursor stands still and only the display seems to shift right.
 */
#define LCD_EntryMode_CursorDecrement_ShiftON	 	0x05
/**
 *@brief : It looks as if the cursor stands still and only the display seems to shift left.
 */
#define LCD_EntryMode_CursorIncrement_ShiftON		0x07
/**
 *@brief : The display is on, but the cursor is off and there is no blinking.
 */
#define LCD_DisplayON_CursorOFF_BlinkOFF		 	0x0C
/**
 *@brief : The display is on, but the cursor is off and the current character is blinking.
 */
#define LCD_DisplayON_CursorOFF_BlinkON				0x0D
/**
 *@brief : The display is on, the cursor is on, but there is no blinking.
 */
#define LCD_DisplayON_CursorON_BlinkOFF				0x0E
/**
 *@brief : The display is on, the cursor is on and blinking.
 */
#define LCD_DisplayON_CursorON_BlinkON				0x0F
/**
 *@brief : The display is off, The display data remains in the DDRAM.
 */
#define LCD_DisplayOFF								0x08
/**
 *@brief : Shifts cursor position to the left (AC is decreased by 1).
 */
#define LCD_CursorShiftLeft							0x10
/**
 *@brief : Shifts cursor position to the right (AC is increased by 1).
 */
#define LCD_CursorShiftRight						0x14
/**
 *@brief : Shifts the entire display to the left, cursor follows the display shift.
 */
#define LCD_DisplayShiftLeft						0x18
/**
 *@brief : Shifts the entire display to the right, cursor follows the display shift.
 */
#define LCD_DisplayShiftRight						0x1C
/**
 *@brief : The used mode is four-bit mode, with 2 line display and 5x7 dots character font.
 */
#define LCD_FourBitMode_2LineDisplay_5x7			0x28
/**
 *@brief : The used mode is four-bit mode, with 2 line display and 5x10 dots character font.
 */
#define LCD_FourBitMode_2LineDisplay_5x10			0x2C
/**
 *@brief : The used mode is eight-bit mode, with 2 line display and 5x7 dots character font.
 */
#define LCD_EightBitMode_2LineDisplay_5x7			0x38
/**
 *@brief : The used mode is eight-bit mode, with 2 line display and 5x7 dots character font.
 */
#define LCD_EightBitMode_2LineDisplay_5x10			0x3C


/* GPIO ports */

#define GPIO_PORTA						(0x40020000UL)	/* 	GPIOA Base Address			*/
#define GPIO_PORTB						(0x40020400UL)	/* 	GPIOB Base Address			*/
#define GPIO_PORTC						(0x40020800UL)	/* 	GPIOC Base Address			*/
#define GPIO_PORTD						(0x40020C00UL)	/* 	GPIOD Base Address			*/
#define GPIO_PORTE						(0x40021000UL)	/* 	GPIOE Base Address			*/
#define GPIO_PORTH						(0x40021C00UL)	/* 	GPIOH Base Address			*/
/****************************************************************************************/


/* GPIO port's pins */

#define GPIO_PIN0						(0UL)
#define GPIO_PIN1						(1UL)
#define GPIO_PIN2						(2UL)
#define GPIO_PIN3						(3UL)
#define GPIO_PIN4						(4UL)
#define GPIO_PIN5						(5UL)
#define GPIO_PIN6						(6UL)
#define GPIO_PIN7						(7UL)
#define GPIO_PIN8						(8UL)
#define GPIO_PIN9						(9UL)
#define GPIO_PIN10						(10UL)
#define GPIO_PIN11						(11UL)
#define GPIO_PIN12						(12UL)
#define GPIO_PIN13						(13UL)
#define GPIO_PIN14						(14UL)
#define GPIO_PIN15						(15UL)
/****************************************************************************************/


#define D0		0
#define D1		1
#define D2		2
#define D3		3
#define D4		4
#define D5		5
#define D6		6
#define D7		7
#define RS		8
#define	RW		9
#define	E		10

#define D4_4BITMODE		0
#define D5_4BITMODE		1
#define D6_4BITMODE		2
#define D7_4BITMODE		3
#define RS_4BITMODE		4
#define	RW_4BITMODE		5
#define	E_4BITMODE		6



#define LCD_FOUR_BITS_MODE		0
#define	LCD_EIGHT_BITS_MODE		1



/****************************************************************************************/
/*								User-defined Declaration								*/
/****************************************************************************************/

/**
 *@brief : The Error List Type
 */
typedef enum
{
	/**
	 *@brief : Everything OK, Function had Performed Correctly.
	 */
	LCD_enumOk = 0,
	/**
	 *@brief : NULL Pointer is passed.
	 */
	LCD_enumNullPointer,
	/**
	 *@brief : If the entered Row number is not exist in the LCD.
	 */
	LCD_enumWrongRowNumber,
	/**
	 *@brief : If the entered Column number is not exist in the LCD.
	 */
	LCD_enumWrongColumnNumber,
	/**
	 *@brief : If the entered Block number is not exist in the CGRAM.
	 */
	LCD_enumWrongBlockNumber,
	/**
	 *@brief : If a problem happen when setting the value or the direction of one of the pin that the LCD is connected to.
	 */
	LCD_enumWrongPinConfiguration

}LCD_enumError_t;


/**
 *@brief : The available Rows in the LCD
 */
typedef enum
{
	/**
	 *@brief : First row in the LCD.
	 */
	LCD_enumFirstRow = 0,
	/**
	 *@brief : Second row in the LCD.
	 */
	LCD_enumSecondRow

}LCD_enumRowNumber_t;


/**
 *@brief : The available Columns in the LCD
 */
typedef enum
{
	/**
	 *@brief : First column in the LCD.
	 */
	LCD_enumColumn_1 = 0,
	/**
	 *@brief : Second column in the LCD.
	 */
	LCD_enumColumn_2,
	/**
	 *@brief : Third column in the LCD.
	 */
	LCD_enumColumn_3,
	/**
	 *@brief : Column number 4 in the LCD.
	 */
	LCD_enumColumn_4,
	/**
	 *@brief : Column number 5 in the LCD.
	 */
	LCD_enumColumn_5,
	/**
	 *@brief : Column number 6 in the LCD.
	 */
	LCD_enumColumn_6,
	/**
	 *@brief : Column number 7 in the LCD.
	 */
	LCD_enumColumn_7,
	/**
	 *@brief : Column number 8 in the LCD.
	 */
	LCD_enumColumn_8,
	/**
	 *@brief : Column number 9 in the LCD.
	 */
	LCD_enumColumn_9,
	/**
	 *@brief : Column number 10 in the LCD.
	 */
	LCD_enumColumn_10,
	/**
	 *@brief : Column number 11 in the LCD.
	 */
	LCD_enumColumn_11,
	/**
	 *@brief : Column number 12 in the LCD.
	 */
	LCD_enumColumn_12,
	/**
	 *@brief : Column number 13 in the LCD.
	 */
	LCD_enumColumn_13,
	/**
	 *@brief : Column number 14 in the LCD.
	 */
	LCD_enumColumn_14,
	/**
	 *@brief : Column number 15 in the LCD.
	 */
	LCD_enumColumn_15,
	/**
	 *@brief : Column number 16 in the LCD.
	 */
	LCD_enumColumn_16,
	/**
	 *@brief : Column number 17 in the LCD.
	 */
	LCD_enumColumn_17,
	/**
	 *@brief : Column number 18 in the LCD.
	 */
	LCD_enumColumn_18,
	/**
	 *@brief : Column number 19 in the LCD.
	 */
	LCD_enumColumn_19,
	/**
	 *@brief : Column number 20 in the LCD.
	 */
	LCD_enumColumn_20,
	/**
	 *@brief : Column number 21 in the LCD.
	 */
	LCD_enumColumn_21,
	/**
	 *@brief : Column number 22 in the LCD.
	 */
	LCD_enumColumn_22,
	/**
	 *@brief : Column number 23 in the LCD.
	 */
	LCD_enumColumn_23,
	/**
	 *@brief : Column number 24 in the LCD.
	 */
	LCD_enumColumn_24,
	/**
	 *@brief : Column number 25 in the LCD.
	 */
	LCD_enumColumn_25,
	/**
	 *@brief : Column number 26 in the LCD.
	 */
	LCD_enumColumn_26,
	/**
	 *@brief : Column number 27 in the LCD.
	 */
	LCD_enumColumn_27,
	/**
	 *@brief : Column number 28 in the LCD.
	 */
	LCD_enumColumn_28,
	/**
	 *@brief : Column number 29 in the LCD.
	 */
	LCD_enumColumn_29,
	/**
	 *@brief : Column number 30 in the LCD.
	 */
	LCD_enumColumn_30,
	/**
	 *@brief : Column number 31 in the LCD.
	 */
	LCD_enumColumn_31,
	/**
	 *@brief : Column number 32 in the LCD.
	 */
	LCD_enumColumn_32,
	/**
	 *@brief : Column number 33 in the LCD.
	 */
	LCD_enumColumn_33,
	/**
	 *@brief : Column number 34 in the LCD.
	 */
	LCD_enumColumn_34,
	/**
	 *@brief : Column number 35 in the LCD.
	 */
	LCD_enumColumn_35,
	/**
	 *@brief : Column number 36 in the LCD.
	 */
	LCD_enumColumn_36,
	/**
	 *@brief : Column number 37 in the LCD.
	 */
	LCD_enumColumn_37,
	/**
	 *@brief : Column number 38 in the LCD.
	 */
	LCD_enumColumn_38,
	/**
	 *@brief : Column number 39 in the LCD.
	 */
	LCD_enumColumn_39,
	/**
	 *@brief : Column number 40 in the LCD.
	 */
	LCD_enumColumn_40,

}LCD_enumColumnNumber_t;


/**
 *@brief : The available Block numbers in the CGRAM
 */
typedef enum
{
	/**
	 *@brief : First block in the CGRAM.
	 */
	LCD_enumBlockNumber_1 = 0,
	/**
	 *@brief : Second block in the CGRAM.
	 */
	LCD_enumBlockNumber_2,
	/**
	 *@brief : Third block in the CGRAM.
	 */
	LCD_enumBlockNumber_3,
	/**
	 *@brief : Fourth block in the CGRAM.
	 */
	LCD_enumBlockNumber_4,
	/**
	 *@brief : Fifth block in the CGRAM.
	 */
	LCD_enumBlockNumber_5,
	/**
	 *@brief : Sixth block in the CGRAM.
	 */
	LCD_enumBlockNumber_6,
	/**
	 *@brief : Seventh block in the CGRAM.
	 */
	LCD_enumBlockNumber_7,
	/**
	 *@brief : Eighth block in the CGRAM.
	 */
	LCD_enumBlockNumber_8

}LCD_enumBlockNumber_t;


/* Structure that will be used when setting the direction and the value of any of the LCD's pins */
typedef struct {
	uint32_t LCD_port_number;
	uint32_t LCD_pin_number;
}LCD_strLCDPinConfig_t;

/********************************************************************************************/
/*									Functions' Declaration									*/
/********************************************************************************************/

/**
 *@brief : Function to Set the pins to which the LCD is connected to, and to initialize the LCD.
 *@param : void.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumInit(void);

/**
 *@brief : Function to Write data to the LCD.
 *@param : Data you want to send.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumWriteData(uint8_t Copy_uint8Data);

/**
 *@brief : Function to Write command to the LCD.
 *@param : Command you want to send.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumWriteCommand(uint8_t Copy_uint8Command);

/**
 *@brief : Function to go to certain location in the DDRAM.
 *@param : The row number, and the column number in that row.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumGotoDDRAM_XY(LCD_enumRowNumber_t Copy_uint8X, LCD_enumColumnNumber_t Copy_uint8Y);

/**
 *@brief : Function to Print certain number on the LCD.
 *@param : Number you want to print.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumWriteNumber(uint64_t Copy_uint64Number);

/**
 *@brief : Function to Print certain string on the LCD.
 *@param : String you want to print.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumWriteString(uint8_t* Copy_puint8Pattern);

/**
 *@brief : Function to Save Special character in the CGRAM, and then to print it on the LCD.
 *@param : Special character you want to print, the block number that character will be saved inside in the
 *			CGRAM, then (for the printing purpose) the row and column number in which that character will
 *			be displayed.
 *@return: Error State.
 */
LCD_enumError_t LCD_enumDisplaySpecialPattern(uint8_t* Copy_puint8SpecialChar, LCD_enumBlockNumber_t Copy_uint8CGRAMBlockNumber, LCD_enumRowNumber_t Copy_uint8X, LCD_enumColumnNumber_t Copy_uint8Y);

#endif /* LCD_H_ */
