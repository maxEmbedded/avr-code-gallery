// Post: "Seven Segment Multiplexing"
// URL: http://maxembedded.com/2013/01/30/seven-segment-multiplexing/
// Author: Yash Tambi and Mayank Prasad, VIT University

/* 	DISCLAIMER

	This is the same code as given in the above URL. Though the code is tested and approved, the author
	is not responsible for any damage, physical, mental or social, which might occur due to the implementation
	of this code and its derivatives, whether in full or part thereof. Use it at your own risk.

	LICENSE
	
	The user is free to modify, reuse, reproduce and distribute the code and its derivatives to any extent,
	whether for free or paid. The user can also use this code for commercial purposes. In other words,
	do whatever you want with the code!
   
*/

/*
 * counter.c
 *
 * Created: 1/12/2013 2:48:21 PM
 *  Author: yash
 *
 * COMMON LINES
 * pd0: SSD1
 * pd1: SSD2
 * PD2: SSD3
 * pd3: SSD4
 * pd4: SSD5
 */
 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
 
#define F_CPU 100000000
 
volatile uint16_t digits[5]={0,0,0,0,0}; //INITIALIZE VARIABLE TO STORE INDIVIDUAL DIGITS OF THE NUMBER
 
void breakup(uint16_t num) //FUNCTION TO FIND THE INDIVIDUAL DIGITS OF THE NUMBER
{                            // AND STORE THEM IN A GLOBAL VARIABLE
    DDRD=0xFF; // INITIALIZE PORTD AS ALL OUTPUT
    PORTD=0x00;
    unsigned int i=0;
    while (num!=0)
    {
        digits[i]=num%10;
        num=num/10;
        i++;
    }
    for(i=0;i<5;i++)
    {
        PORTD=(1<<i); // 'i'th PORTD GIVEN HIGH
        display(digits[i]);
        _delay_us(600);
        PORTD=(0<<i); //'i'th PORTD GIVEN LOW
    }
 
}
 
void display (uint16_t num) // FUNCTION TO DISPLAY VALUES ON SSD
{
    DDRB=0b11111111;
    PORTB=0xFF;
    switch(num)
    {
        case 0:
        PORTB=0b11011101;
        break;
        case 1:
        PORTB=0b01010000;
        break;
        case 2:
        PORTB=0b10011011;
        break;
        case 3:
        PORTB=0b11011010;
        break;
        case 4:
        PORTB=0b01010110;
        break;
        case 5:
        PORTB=0b11001110;
        break;
        case 6:
        PORTB=0b11001111;
        break;
        case 7:
        PORTB=0b01011000;
        break;
        case 8:
        PORTB=0b11011111;
        break;
        case 9:
        PORTB=0b11011110;
        break;
        default:
        PORTB=0xFF;
    }
}
 
int main(void)
{
    DDRB=0xFF; //INITIALIZE PORTB AS ALL OUTPUT
    DDRC=0b11111110;   //PORTC0 DEFINED AS INPUT AND PORTD5 AS OUTPUT
    PORTC|=(1<<0); //enable internal pull-up resistors in PC0 and PC2
        char x;
    uint16_t i, c=0,z=0;
        z=eeprom_read_word((uint16_t*)500); //read the value stored in the memory
    c=z;
    while(1)
        {
        x=PINC&0b00000001; //CHECK CONDITION OF INPUT '1' at PC0
            if (x==0)
        {
               c++;
               breakup(c); //PASS THE VALUE OF 'c' FOR DIGIT BREAKUP AND DISPLAY
               _delay_ms(1000);
               eeprom_update_word((uint16_t*)500,c); //update memory
        }
 
        else
        breakup(c);
    }
}