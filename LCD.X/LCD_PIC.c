#include "LCD_PIC.h"



void LCD_PREDT(unsigned char data)
{
    DB7 = (data >> 3) & 0x01;
    DB6 = (data >> 2) & 0x01;
    DB5 = (data >> 1) & 0x01;
    DB4 = (data & 0x01);
}

void LCD_WriteIR(unsigned char data)
{
    RS = 0;
    RW = 0;
    EN = 1;
    LCD_PREDT(data >> 4);
    EN = 0;
    __delay_ms(5);
    EN = 1;
    LCD_PREDT(data);
    EN = 0;

    __delay_ms(5);
}

void LCD_WriteDT(unsigned char data)
{

    RS = 1;
    RW = 0;
    EN = 1;
    LCD_PREDT(data >> 4);
    EN = 0;
    __delay_ms(5);
    EN = 1;
    LCD_PREDT(data);
    EN = 0;
    __delay_ms(5);
}

void LCD_Init(void)
{
    DB7DR = 0;
    DB6DR = 0;
    DB5DR = 0;
    DB4DR = 0;

    RSDR = 0;
    RWDR = 0;
    ENDR = 0;
    RS = 0;
    RW = 0;
    EN = 1;
    LCD_PREDT(0x02);
    EN = 0;
    __delay_ms(5);
    LCD_WriteIR(0x01);         //Display Clear
    LCD_WriteIR(0x28);          //8bits Interface, 2Line
    LCD_WriteIR(0x0f);          //Cursor display
//    LCD_WriteIR(0x14);          // Cursor shift right
    LCD_WriteIR(0x06);
}

void LCD_WriteString(unsigned char* data)
{
    unsigned char i;
    while (*(data) != 0x2B)
    {
        LCD_WriteDT(*(data));
        data++;
    }
}