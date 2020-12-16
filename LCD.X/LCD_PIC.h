#ifndef __LCD_PIC_H

#define _XTAL_FREQ  16000000
#include    <xc.h>

#define RS  RE0					//PIN for Control bits
#define RW  RE1
#define EN  RE2

#define RSDR    TRISE0			//PIN direction
#define RWDR    TRISE1
#define ENDR    TRISE2

#define DB7 RD7					//4 bits interface only 
#define DB6 RD6					//4 bits data PIN
#define DB5 RD5
#define DB4 RD4

#define DB7DR   TRISD7			//4bits PIN Direction
#define DB6DR   TRISD6
#define DB5DR   TRISD5
#define DB4DR   TRISD4


void LCD_PREDT(unsigned char data);			//Prepare data for PIN
void LCD_WriteIR(unsigned char data);		//Write Instruction to LCD
void LCD_WriteDT(unsigned char data);		//Write Data to LCD
void LCD_Init(void);						//Initialize LCD (first Instruction)
void LCD_WriteString(unsigned char* data);	//Write String to LCD, Last character '+'

#endif // !__LCD_PIC_H

