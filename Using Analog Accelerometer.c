// Post: "Using an Analog Accelerometer"
// URL: http://maxembedded.com/2013/06/28/using-an-analog-accelerometer/
// Author: Yash Tambi, VIT University

/* 	DISCLAIMER

	This is the same code as given in the above URL. Though the code is tested and approved, the author
	is not responsible for any damage, physical, mental or social, which might occur due to the implementation
	of this code and its derivatives, whether in full or part thereof. Use it at your own risk.

	LICENSE
	
	The user is free to modify, reuse, reproduce and distribute the code and its derivatives to any extent,
	whether for free or paid. The user can also use this code for commercial purposes. In other words,
	do whatever you want with the code!
   
*/

#ifndef F_CPU 
#define F_CPU 16000000UL 
#endif 

#include <avr/io.h> 
#include <stdlib.h>				//include Library for 'itoa' function 
#include "lcd.h" 				//include LCD Library 
#include <util/delay.h> 

void adc_init(void) 
{ 
    ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //ENABLE ADC, PRESCALER 128 
    ADMUX|=(1<<REFS0); 			//PC0, AVcc AS REFERENCE VOLTAGE 
} 

uint16_t adc_read(uint8_t ch) 
{ 
    ch&=0b00000111; 			//ANDing to limit input to 7 
    ADMUX = (ADMUX & 0xf8)|ch; 	//Clear last 3 bits of ADMUX, OR with ch 
    ADCSRA|=(1<<ADSC); 			//START CONVERSION 
    while((ADCSRA)&(1<<ADSC)); 	//WAIT UNTIL CONVERSION IS COMPLETE 
    return(ADC); 				//RETURN ADC VALUE 
} 

int main(void) 
{ 
    uint16_t x,y,z; 
    char bufferx[10], buffery[10], bufferz[10]; //Initialize character arrays for each 
     
    adc_init(); 				//INITIALIZE ADC 
    lcd_init(LCD_DISP_ON); 		//INITIALIZE LCD 
    lcd_clrscr(); 				//CLEAR LCD SCREEN 
     
    while(1) 
    { 
        lcd_home(); 			//LCD - GO TO HOME POSITION 

        x=adc_read(0); 			//READ ADC VALUE FROM CHANNEL 0 
        y=adc_read(1); 			//READ ADC VALUE FROM CHANNEL 1 
        z=adc_read(2); 			//READ ADC VALUE FROM CHANNEL 2 

        itoa(x,bufferx,10); 	//STORE THE ADC VALUES IN ARRAYS 
        itoa(y,buffery,10); 
        itoa(z,bufferz,10); 

        lcd_puts("x="); 		//DISPLAY THE RESULTS ON LCD 
        lcd_gotoxy(2,0); 
        lcd_puts(bufferx); 

        lcd_gotoxy(0,1); 
        lcd_puts("y="); 
        lcd_gotoxy(2,1); 
        lcd_puts(buffery); 

        lcd_gotoxy(6,0); 
        lcd_puts("z="); 
        lcd_gotoxy(6,1); 
        lcd_puts(bufferz); 
    } 
}