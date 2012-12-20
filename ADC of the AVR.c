// Post: "The ADC of the AVR"
// URL: http://maxembedded.com/2011/06/20/the-adc-of-the-avr/
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

#define LTHRES 500
#define RTHRES 500

// initialize adc
void adc_init()
{
    // AREF = AVcc
    ADMUX = (1<<REFS0);

    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

// read adc value
uint16_t adc_read(uint8_t ch)
{
    // select the corresponding channel 0~7
    // ANDing with '7' will always keep the value
    // of 'ch' between 0 and 7
    ch &= 0b00000111;  // AND operation with 7
    ADMUX = (ADMUX & 0xF8)|ch;     // clears the bottom 3 bits before ORing

    // start single conversion
    // write '1' to ADSC
    ADCSRA |= (1<<ADSC);

    // wait for conversion to complete
    // ADSC becomes '0' again
    // till then, run loop continuously
    while(ADCSRA & (1<<ADSC));

    return (ADC);
}

int main()
{
    uint16_t adc_result0, adc_result1;
    char int_buffer[10];
    DDRC = 0x01;           // to connect led to PC0

    // initialize adc and lcd
    adc_init();
    lcd_init(LCD_DISP_ON_CURSOR);

    // display the labels on LCD
    lcd_puts("left  ADC = ");
    lcd_gotoxy(0,1);
    lcd_puts("right ADC = ");

    _delay_ms(50);

    while(1)
    {
        adc_result0 = adc_read(0);      // read adc value at PA0
        adc_result1 = adc_read(1);      // read adc value at PA1

        // condition for led to glow
        if (adc_result0 < LTHRES && adc_result1 < RTHRES)
            PORTC = 0x01;
        else
            PORTC = 0x00;

        // now display on lcd
        itoa(adc_result0, int_buffer, 10);
        lcd_gotoxy(12,0);
        lcd_puts(int_buffer);

        itoa(adc_result0, int_buffer, 10);
        lcd_gotoxy(12,1);
        lcd_puts(int_buffer);
        _delay_ms(50);
    }
}