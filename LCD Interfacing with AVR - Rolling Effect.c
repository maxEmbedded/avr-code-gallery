// Post: "LCD Interfacing with AVR" - Rolling Effect Code
// URL: http://maxembedded.com/2011/06/16/lcd-interfacing-with-avr/
// Author: Mayank Prasad, VIT University

/* 	DISCLAIMER

	This is the same code as given in the above URL. Though the code is tested and approved, the author
	is not responsible for any damage, physical, mental or social, which might occur due to the implementation
	of this code and its derivatives, whether in full or part thereof. Use it at your own risk.

	LICENSE
	
	The user is free to modify, reuse, reproduce and distribute the code and its derivatives to any extent,
	whether for free or paid. The user can also use this code for commercial purposes. In other words,
	do whatever you want with the code!
   
*/

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define STRING_LENGTH 27
#define LCD_MAX 15 

void main()
{
    char array[STRING_LENGTH] = { "welcome to maxEmbedded blog" };
    int i,j;
    int start;
    int end; 

    lcd_init(LCD_DISP_ON_CURSOR);
    lcd_clrscr();
    while(1)
    {
        for ( j = 0; j < STRING_LENGTH; j++ )
        {
            if ( j >= LCD_MAX )
                lcd_gotoxy( 0, 0 );
            else
                lcd_gotoxy( LCD_MAX - j, 0 ); 

            start = (j <= LCD_MAX) ? 0 : (j - LCD_MAX); 

            end = (j <= LCD_MAX) ? j : (start + LCD_MAX); 

            if ( end >= STRING_LENGTH )
                end = STRING_LENGTH - 1; 

            for ( i = start; i <= end; i++ )
                lcd_putc( array[i] ); 

            _delay_ms(100);
        } 

        lcd_clrscr();
    }
}