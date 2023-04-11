#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"



#include "../MCAL/DIO/DIO_Interface.h"

#include "../HAL/LCD/LCD_Interface.h"
#define DELAY 6
int main()
{
	s16 i;
	LCD_voidInit();
	//u8 ArrPattern_0[8] = {0b00000,0b01010,0b10101,0b10001,0b10001,0b01010,0b00100,0b00000}; // Heart Symbol
	//u8 ArrPattern_1[8] = {0b00000,0b00100,0b01110,0b10001,0b10001,0b01010,0b00100,0b00100}; // Head Of Person
	//u8 ArrPattern_2[8] = {0b00100,0b01110,0b10101,0b00100,0b00100,0b00100,0b01010,0b10001}; // Legs Of Person
	//u8 ArrPattern_3[8] = {0b00000,0b00000,0b00001,0b00001,0b11111,0b00000,0b00100,0b00000}; // B
	//u8 ArrPattern_4[8] = {0b00000,0b00000,0b01110,0b01010,0b11111,0b01010,0b01110,0b00000}; // H
	//u8 ArrPattern_5[8] = {0b01000,0b01000,0b01000,0b01000,0b01111,0b00000,0b00000,0b00000}; // A
	//u8 ArrPattern_6[8] = {0b00000,0b00000,0b00111,0b00100,0b01111,0b00000,0b00000,0b00000}; // A
	u8 ArrPattern_0[8] = {0b00100,0b01010,0b00100,0b00100,0b01111,0b00100,0b01010,0b10001}; // Hamoksha
	u8 ArrPattern_1[8] = {0b00000,0b00100,0b01110,0b11111,0b11111,0b01110,0b11111,0b01110}; // Solid pattern
    u8 flag=0 ;
	LCD_voidDrawPattern ( PATTERN_0 , ArrPattern_0 );
	LCD_voidDrawPattern ( PATTERN_1 , ArrPattern_1 );
	u8 Arr1[]={"Welcome To"};
	u8 Arr2[]={"Hamok4a Game"};
	u8 Arr3[]={"Good Mok4a"};
	u8 Arr4[]={"Excellent"};
	u8 Arr5[]={"TimeOut Y Mok4a"};
	u8 Arr6[]={"Bay Bay"};

	LCD_voidGoTo_XY ( LINE_1 ,0);
	LCD_voidWriteString ("Ahmed Bahaa Nasr");
	_delay_ms(2);
	LCD_voidGoTo_XY ( LINE_2 ,3);
	LCD_voidWriteString ("ES Engineer");
	_delay_ms(150);
	LCD_voidClearLine(LINE_1);
	LCD_voidClearLine(LINE_2);

	LCD_voidGoTo_XY ( LINE_1 , 3 );
	LCD_voidWriteString (Arr1 );
	_delay_ms(20);
	LCD_voidGoTo_XY ( LINE_2 , 2 );
	LCD_voidWriteString (Arr2 );
	_delay_ms(100);
	LCD_voidClearDisplay ();

	LCD_voidWritePattern ( 0 , LINE_1 , 0 );
	_delay_ms(15);
	LCD_voidClearGrid ( LINE_1 , 0);

	LCD_voidWritePattern ( 0 , LINE_1 , 1 );
	_delay_ms(15);
	LCD_voidClearGrid ( LINE_1 , 1);

	LCD_voidWritePattern ( 0 , LINE_2 , 2 );
	_delay_ms(15);
	LCD_voidClearGrid ( LINE_2 , 2 );

	LCD_voidWritePattern ( 0 , LINE_2 , 3 );

	while(1)
	{
		LCD_voidWritePattern ( 0 , LINE_2 , 3 );
			for ( i=15 ; i>=0 ; i-- )
			{
				_delay_ms(DELAY);
				LCD_voidClearGrid ( LINE_2 , i+1  );
				LCD_voidWritePattern ( 1 , LINE_2 , i );

				if (i==4)
				{
					LCD_voidClearGrid ( LINE_2 , 3 );
					LCD_voidWritePattern ( 0 , LINE_1 , 3 );
				}
				else if (i==1)
				{
					LCD_voidClearGrid ( LINE_1 , 3 );
					LCD_voidWritePattern ( 0 , LINE_2 , 3 );
				}
				else if(i==0)
				{   _delay_ms(DELAY);
					LCD_voidClearGrid ( LINE_2 , i );
				}
			}
			flag++;
			if (flag==3 )
			{
				LCD_voidGoTo_XY ( LINE_1 , 5 );
				LCD_voidWriteString (Arr3 );
			}
			if (flag==4 )
			{
				LCD_voidClearLine ( LINE_1 );
			}
			if (flag==7 )
			{
				LCD_voidGoTo_XY ( LINE_1 , 6 );
				LCD_voidWriteString (Arr4 );
			}
			if (flag==8 )
			{
				LCD_voidClearLine ( LINE_1 );
			}
			if(flag==10)
				break;
	}

	LCD_voidGoTo_XY ( LINE_1 , 1 );
	LCD_voidWriteString (Arr5 );
	_delay_ms(20);
	LCD_voidGoTo_XY ( LINE_2 , 7 );
	LCD_voidWriteString (Arr6 );

}

