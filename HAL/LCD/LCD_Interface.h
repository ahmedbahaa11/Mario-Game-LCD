/*===================================================================================================*/
/*  File        : LCD_Interface.h                                                                    */
/*  Description : This interface file includes LCD Driver prototypes and declarations for Atmega32   */
/*  Author      : Ahmed Bahaa Taha Nasr. Embedded SW Engineer                                        */
/*  Date        : 28/3/2023                                                                          */
/*  Linkedin    : https://www.linkedin.com/in/ahmed-bahaa1/                                          */
/*  Git account : https://github.com/ahmedbahaa11                                                    */
/*  mail        : ahmedbahaataha7@gmil.com                                                           */
/*===================================================================================================*/

/* File Gaurd by ifndef & endif */
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define LINE_1       0
#define LINE_2       1

#define    PATTERN_0        0b01000000    // address of First Byte at Sequence 0 at CGRAM            
#define    PATTERN_1        0b01001000    // address of First Byte at Sequence 1 at CGRAM            
#define    PATTERN_2        0b01010000    // address of First Byte at Sequence 2 at CGRAM
#define    PATTERN_3        0b01011000    // address of First Byte at Sequence 3 at CGRAM
#define    PATTERN_4        0b01100000    // address of First Byte at Sequence 4 at CGRAM
#define    PATTERN_5        0b01101000    // address of First Byte at Sequence 5 at CGRAM
#define    PATTERN_6        0b01110000    // address of First Byte at Sequence 6 at CGRAM
#define    PATTERN_7        0b01111000    // address of First Byte at Sequence 7 at CGRAM


void LCD_voidInit (void);
void LCD_voidWriteCommand ( u8 Copy_u8Command );
void LCD_voidWriteChar ( u8 Copy_u8Char );
void LCD_voidWriteString (u8 *Copy_u8Arr );
void LCD_voidWrite_u32Number ( u32 Copy_u32Number);
void LCD_voidGoTo_XY ( u8 Copy_u8Line , u8 Copy_u8Position );
/*************************************************************************************************************************/
/* Function Name : LCD_voidDrawPattern                                                                                   */
/* Description : Draw a Pattern and save it on PATTERN_NUMBER at CGRAM                                                   */
/* Fun.Argument1: Copy_u8Pattern_Number{PATTERN_0,PATTERN_1,PATTERN_2,PATTERN_3,PATTERN_4,PATTERN_5,PATTERN_6,PATTERN_7} */
/* Fun.Argument2: *Copy_u8Arr_Pattern { Address of array for Details of drawing }                                        */
/* Fun. Return : void                                                                                                    */
/*************************************************************************************************************************/
void LCD_voidDrawPattern ( u8 Copy_u8Pattern_Number , u8 *Copy_u8Arr_Pattern );
/*****************************************************************************************/
/* Function Name : LCD_voidWritePattern                                                  */
/* Description : Write a Pattern on the LCD at specific Line & Position                  */
/* Fun. Argument1: Copy_u8Pattern {0,1,2,3,4,5,6,7}                                      */
/* Fun. Argument2: Copy_u8Line { LINE_1 , LINE_2 }                                       */
/* Fun. Argument3: Copy_u8Position { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }             */
/* Fun. Return : void                                                                    */
/*****************************************************************************************/
void LCD_voidWritePattern ( u8 Copy_u8Pattern , u8 Copy_u8Line , u8 Copy_u8Position );
void LCD_voidClearDisplay (void);
void LCD_voidShiftLeft (void);
void LCD_voidShiftRight (void);
void LCD_voidClearGrid ( u8 Copy_u8Line , u8 Copy_u8Position );
void LCD_voidClearLine ( u8 Copy_u8Line );







#endif