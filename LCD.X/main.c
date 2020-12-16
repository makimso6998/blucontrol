/*
 * File:   main.c
 * Author: DELL
 *
 * Created on November 16, 2020, 4:06 PM
 */


// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#include "LCD_PIC.h"
#define _XTAL_FREQ 16000000
/* User variable */
unsigned char var[20]= "SANGDEPTRAI \r\n+"; 
unsigned char a;
/* User function prototype*/
void Send_data (unsigned char *data);

unsigned char array[20] = "SANGDEP TRai+";
void main(void) {
        PSPMODE = 0;
    ADCON1 = ADCON1 | 0x07;
    LCD_Init();
    LCD_WriteString(array);
    TRISDbits.TRISD2 = 0x00;
    TRISBbits.TRISB5 = 0x00;
    TRISBbits.TRISB2 = 0x00;
    TRISBbits.TRISB4 = 0x00;
    TRISCbits.TRISC1 = 1;
    TRISBbits.TRISB1 = 0;
    RB1 = 0;
    RD2 = 0;
    SYNC = 0;
    BRGH = 0;
    SPBRG = 25;
    SPEN = 1;
    TXEN = 1;
    TXREG = 0x41;
    __delay_ms(100);
    TXREG = 0x42;
    CREN = 1;
    PEIE = 1;
    GIE = 0;
    CREN = 1;
    RCIF= 0;
    while(1)
    {
          while (RCIF ==0);
        a = RCREG;
        if ( a == 'A')
        {
        RD2 = ~RD2;
        RB1 = ~RB1;
        }
        if ( a == 'B')
        {
        RB5 = ~RB5;
        RB1 = ~RB1;
        }
        if ( a == 'C')
        {
        RB4 = ~RB4;
        RB1 = ~RB1;
        }
        if ( a == 'D')
        {
        RB2 = ~RB2;
        RB1 = ~RB1;
        }
        Send_data(var);
                while ( TXIF == 0);
                

    }
}
/* User code */
void Send_data (unsigned char *data)
{
    while (*(data) != '+')
    {
        while ( TXIF == 0);
        TXREG = *(data);
        __delay_ms(10);
        data += 1;
    }
    while ( TXIF == 0);
}