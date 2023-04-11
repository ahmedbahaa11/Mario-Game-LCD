/*=================================================================================*/
/*  File        : LCD_Program.c                                                    */
/*  Description : This file includes LCD Driver implementations for Atmega32       */
/*  Author      : Ahmed Bahaa Taha Nasr. Embedded SW Engineer                      */
/*  Date        : 28/3/2023                                                        */
/*  Linkedin    : https://www.linkedin.com/in/ahmed-bahaa1/                        */
/*  Git account : https://github.com/ahmedbahaa11                                  */
/*  mail        : ahmedbahaataha7@gmil.com                                         */
/*=================================================================================*/

#include <util/delay.h>
/* Include Header Files From LIB */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/* Include Header Files From MCAL Layer */
#include "../../MCAL/DIO/DIO_Interface.h"

/* Include My own Header Files*/
#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"


/*==============================================================================================*/
/**************************    A.BAHAA LCD Functions Implementations     ************************/
/*==============================================================================================*/
/**********************************  LCD_voidInit                ********************************/
/**********************************  LCD_voidWriteCommand         ********************************/
/**********************************  LCD_voidWriteChar            ********************************/
/**********************************  LCD_voidWriteString            ******************************/
/**********************************  LCD_voidWrite_u32Number        *******************************/
/*==============================================================================================*/

void LCD_voidInit (void)
{
    /* Control Pins Directions */
    DIO_voidSetPortDirection(LCD_DATA_PORT , OUTPUT);
    DIO_voidSetPinDirection(LCD_CONTROL_PORT,RS_PIN,OUTPUT);
    DIO_voidSetPinDirection(LCD_CONTROL_PORT,RW_PIN,OUTPUT);
    DIO_voidSetPinDirection(LCD_CONTROL_PORT,E_PIN,OUTPUT);

    _delay_ms(35);

    /* Send Command Function Set */
    LCD_voidWriteCommand ( FS_8BIT_2LINES_5x10 );
    _delay_ms(1);

    /* Send Command Display ON-OFF Control */
    LCD_voidWriteCommand ( DIS_ON_NO_CURSER );
    _delay_ms(1);

    /* Send Command Display Clear */
    LCD_voidWriteCommand ( DIS_CLEAR );
    _delay_ms(2);

    /* Send Command Entry Mode */
    LCD_voidWriteCommand ( ENTRY_MODE_INCREASE_NO_SHIFT );
    _delay_ms(1);


}

void LCD_voidWriteCommand ( u8 Copy_u8Command )
{
    /* RS=0 because we send a Command not Data */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,RS_PIN,LOW);

    /* RW=0 because we Write a Command not Read */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,RW_PIN,LOW);

    /* Send Data bits from MC PINS to LCD Data PINS */
    DIO_voidSetPortValue(LCD_DATA_PORT,Copy_u8Command);

    /* Falling Edge on E PIN to make LCD Read This Command */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,E_PIN,HIGH);
    //_delay_ms(1);
    DIO_voidSetPinValue (LCD_CONTROL_PORT,E_PIN,LOW);
}

void LCD_voidWriteChar ( u8 Copy_u8Char )
{
    /* RS=1 because we send a Data not Command */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,RS_PIN,HIGH);

    /* RW=0 because we Write a Data not Read */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,RW_PIN,LOW);

    /* Send Data bits from MC PINS to LCD Data PINS */
    DIO_voidSetPortValue(LCD_DATA_PORT,Copy_u8Char);

    /* Falling Edge on E PIN to make LCD Read This Command */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,E_PIN,HIGH);
    //_delay_ms(1);
    DIO_voidSetPinValue (LCD_CONTROL_PORT,E_PIN,LOW);
}

void LCD_voidWriteString (u8 *Copy_u8Arr )
{
    u8 i = 0 ;
    while (Copy_u8Arr[i] != '\0' )
    {
        LCD_voidWriteChar ( Copy_u8Arr[i] );
        i++;
    }
}

void LCD_voidWrite_u32Number ( u32 Copy_u32Number)
{
    u8 Arr[20] ;
    u8 i=0 ;
    while ( Copy_u32Number > 0 )
    {
        Arr[i] = Copy_u32Number % 10 ;
        Copy_u32Number /= 10 ;
        i++;
    }
    i--;
    for( s16 j=i ; j>=0 ; j--)
    {
        LCD_voidWriteChar ( Arr[j] + '0' );
    }
}

void LCD_voidGoTo_XY ( u8 Copy_u8Line , u8 Copy_u8Position )
{
    /* i/p validation */
    if ( Copy_u8Line > LINE_2 || Copy_u8Position > 15 )
    {
        // Do Nothing
    }
    else
    {
        switch(Copy_u8Line)
        {
            case LINE_1 :    LCD_voidWriteCommand ( 0x80 + Copy_u8Position );      break;  //First position at Line_1 is 0x80 Address at DDRAM
            case LINE_2 :    LCD_voidWriteCommand ( 0xC0 + Copy_u8Position );      break;  //First position at Line_2 is 0xC0 Address at DDRAM
            default     :                                                          break;
        }        
    }
}
/*************************************************************************************************************************/
/* Function Name : LCD_voidDrawPattern                                                                                   */
/* Description : Draw a Pattern and save it on PATTERN_NUMBER at CGRAM                                                   */
/* Fun.Argument1: Copy_u8Pattern_Number{PATTERN_0,PATTERN_1,PATTERN_2,PATTERN_3,PATTERN_4,PATTERN_5,PATTERN_6,PATTERN_7} */
/* Fun.Argument2: *Copy_u8Arr_Pattern { Address of array for Details of drawing }                                        */
/* Fun. Return : void                                                                                                    */
/*************************************************************************************************************************/
void LCD_voidDrawPattern ( u8 Copy_u8Pattern_Number , u8 *Copy_u8Arr_Pattern )
{
    LCD_voidWriteCommand ( Copy_u8Pattern_Number );   

    for ( u8 i=0 ; i < 8 ; i++ )
    {
        LCD_voidWriteChar ( Copy_u8Arr_Pattern[i] );
    }
}
/*****************************************************************************************/
/* Function Name : LCD_voidWritePattern                                                  */
/* Description : Write a Pattern on the LCD at specific Line & Position                  */
/* Fun. Argument1: Copy_u8Pattern {0,1,2,3,4,5,6,7}                                      */
/* Fun. Argument2: Copy_u8Line { LINE_1 , LINE_2 }                                       */
/* Fun. Argument3: Copy_u8Position { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }             */
/* Fun. Return : void                                                                    */
/*****************************************************************************************/
void LCD_voidWritePattern ( u8 Copy_u8Pattern , u8 Copy_u8Line , u8 Copy_u8Position )
{
    LCD_voidGoTo_XY ( Copy_u8Line , Copy_u8Position );
    LCD_voidWriteChar ( Copy_u8Pattern );
}

void LCD_voidClearDisplay (void)
{
    LCD_voidWriteCommand ( DIS_CLEAR );
}

void LCD_voidShiftLeft (void)
{
    LCD_voidWriteCommand ( ENTRY_MODE_INCREASE_LEFT_SHIFT );
}
void LCD_voidShiftRight (void)
{
    LCD_voidWriteCommand ( ENTRY_MODE_DECREASE_RIGHT_SHIFT );
}

void LCD_voidClearGrid ( u8 Copy_u8Line , u8 Copy_u8Position )
{
    LCD_voidGoTo_XY (Copy_u8Line ,Copy_u8Position);
    LCD_voidWriteChar ( ' ' );
}
void LCD_voidClearLine ( u8 Copy_u8Line )
{
	for(u8 i=0 ; i<16 ; i++)
	{
		LCD_voidGoTo_XY (Copy_u8Line ,i);
		LCD_voidWriteChar ( ' ' );
	}
}
