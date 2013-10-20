// Post: "The USART of the AVR"
// URL: http://maxembedded.com/2013/09/30/the-usart-of-the-avr/ ‎
// Author: Yash Tambi, VIT University, tambi@maxEmbedded.com

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
#include <stdlib.h>
#include "lcd.h"							// include LCD library

#define BAUD 9600							// define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)	// set baudrate value for UBRR

#ifndef F_CPU
#define F_CPU 16000000UL					// set the CPU clock
#endif

// function to initialize UART
void uart_init (void)
{
	UBRRH=(BAUDRATE>>8);
	UBRRL=BAUDRATE;							//set baud rate
	UCSRB|=(1<<TXEN)|(1<<RXEN); 			//enable receiver and transmitter
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);// 8bit data format
}

// function to send data - NOT REQUIRED FOR THIS PROGRAM IMPLEMENTATION
void uart_transmit (unsigned char data)
{
	while (!( UCSRA & (1<<UDRE))); 			// wait while register is free
	UDR = data; 							// load data in the register
}

// function to receive data
unsigned char uart_recieve (void)
{ 
	while(!(UCSRA) & (1<<RXC)); 			// wait while data is being received
	return UDR; 							// return 8-bit data
}

// main function: entry point of program
int main (void)
{
	unsigned char a;
	char buffer[10];

	uart_init(); 							// initialize UART 
	lcd_init(LCD_DISP_ON_CURSOR); 			// initialize LCD
	lcd_home(); 							// goto LCD Home

  	while(1)
  	{
		a=uart_recieve(); 					// save the received data in a variable
		itoa(a,buffer,10); 					// convert numerals into string
		lcd_clrscr(); 						// LCD clear screen
		lcd_home();							// goto LCD home
		lcd_puts(buffer); 					// display the received value on LCD
		_delay_ms(100);						// wait before next attempt
  	}
  	
  	return 0;
}
