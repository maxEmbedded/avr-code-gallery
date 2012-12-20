// Post: "LCD Interfacing with AVR"
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

int main(void)
{
    lcd_init(LCD_DISP_ON_CURSOR); /* initialize lcd, display on, cursor on */
                                  /* for more options for
                                  /* lcd_init(), view lcd.h file
    while(1)                      /* run continuously */
    {
        lcd_clrscr();             /* clear screen of lcd */
        lcd_home();               /* bring cursor to 0,0 */
        lcd_puts("hello");        /* type something random */
        lcd_gotoxy(0,1);          /* go to 2nd row 1st col */
        lcd_puts("maxEmbedded");  /* type something random */
        _delay_ms(50);            /* wait 50ms */
    }
}