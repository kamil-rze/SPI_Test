/*
 * File:   main_LCD.c
 * Author: Microchip
 *
 * Created on 04 October 2017, 20:48
 */

#define _XTAL_FREQ 8000000UL

#include <xc.h>
#include "Fuses.h"

#define RS  0x10
#define E   0x20



void Init(void){
    OSCCON = 0x71;
    ANSEL = 0x00;
    ANSELH = 0x00;
    PORTA = PORTB = PORTD = PORTD = PORTE = 0x00;
    TRISA = TRISB = TRISC = TRISD = TRISE = 0x00;
}





void lcd_reset()
{
PORTD = 0xFF;
__delay_ms(20);
PORTD = 0x03 + E;
PORTD = 0x03;
__delay_ms(10);
PORTD = 0x03 + E;
PORTD = 0x03;
__delay_ms(1);
PORTD = 0x03 + E;
PORTD = 0x03;
__delay_ms(1);
PORTD = 0x02 + E;
PORTD = 0x02;
__delay_ms(1);
}

void lcd_cmd (char cmd)
{
PORTD = (unsigned)((cmd >> 4) & 0x0F) | E;
PORTD = (unsigned)((cmd >> 4) & 0x0F);
PORTD = (unsigned)(cmd & 0x0F) | E;
PORTD = (unsigned)(cmd & 0x0F);
__delay_us(200);
__delay_us(200);
}



void lcd_init ()
{
lcd_reset(); // Call LCD reset
lcd_cmd(0x28); // 4-bit mode - 2 line - 5x7 font.
lcd_cmd(0x0C); // Display no cursor - no blink.
lcd_cmd(0x06); // Automatic Increment - No Display shift.
lcd_cmd(0x80); // Address DDRAM with 0 offset 80h.
}





void lcd_data (unsigned char dat)
{
PORTD = (unsigned)(((dat >> 4) & 0x0F) | E |RS);
PORTD = (unsigned)(((dat >> 4) & 0x0F) | RS);
PORTD = (unsigned)((dat & 0x0F)|E|RS);
PORTD = (unsigned)((dat & 0x0F)|RS);
__delay_us(200);
__delay_us(200);
}


void lcd_send_string(unsigned char *str, char length)
{
    while(length--) lcd_data(*str++);
}

void lcd_clear()
{
    lcd_cmd(0x01);
}

void lcd_return_home()
{
    lcd_cmd(0x02);
}

void lcd_entry_mode_set(char inc, char shift)
{
    if(inc) inc = 1;
    if(shift) shift = 1;
    lcd_cmd((0x04) | (inc << 1) | shift);
}

void main(void) {
    unsigned char text[] = "0123456789ABCDEFGHIJo123456789abcdefghij,123456789qwertyghij";
    Init();
    lcd_init();
    lcd_send_string(text,60);    
    __delay_ms(1500);
//    lcd_entry_mode_set(0,0);
//    lcd_data(0x41); 
//    lcd_data(0x42);
//    lcd_data(0x43);
//    __delay_ms(1500);
//    lcd_clear();
    while(1);
    return;
}
