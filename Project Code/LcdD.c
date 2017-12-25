#include "lm4f120h5qr.h"
#include "LcdD.h"
#include "DIO_CONFIG.h"
#include "DIO_INTERFACING.h"
#include "TIMER_CONFIG.h"
#include "TIMER_INTERFACING.h"
#include "Common.h"

///////////////////////////////////////////////////////////////
void LCD_COMMAND(unsigned char command){
        
	DIO_WritePinVal(LCD_RSPin,LOW);                                         // to select command
	DIO_WritePinVal(LCD_RWPin,LOW);                                         // to select write
	//take the first 4 bits
	DIO_WritePinVal(LCD_d7Pin,Get_Bit(command,7));
	DIO_WritePinVal(LCD_d6Pin,Get_Bit(command,6));
	DIO_WritePinVal(LCD_d5Pin,Get_Bit(command,5));
	DIO_WritePinVal(LCD_d4Pin,Get_Bit(command,4));
	// done take the first 4 bits
	DIO_WritePinVal(LCD_ENPin,HIGH);
	TIMER0_Delay_Ms(1);
	DIO_WritePinVal(LCD_ENPin,LOW);
	TIMER0_Delay_Ms(1);
	DIO_WritePinVal(LCD_d7Pin,Get_Bit(command,3));
	DIO_WritePinVal(LCD_d6Pin,Get_Bit(command,2));
	DIO_WritePinVal(LCD_d5Pin,Get_Bit(command,1));
	DIO_WritePinVal(LCD_d4Pin,Get_Bit(command,0));

	//DIO_WritePort(0,(command<<4));

	DIO_WritePinVal(LCD_ENPin,HIGH);
	TIMER0_Delay_Ms(1);
	DIO_WritePinVal(LCD_ENPin,LOW);
	TIMER0_Delay_Ms(1); // wait until the command run
}
///////////////////////////////////////////////////////////////
void LCD_DATA(unsigned char data){
	DIO_WritePinVal(LCD_RSPin,HIGH);
	DIO_WritePinVal(LCD_RWPin,LOW);

	DIO_WritePinVal(LCD_d7Pin,Get_Bit(data,7));
	DIO_WritePinVal(LCD_d6Pin,Get_Bit(data,6));
	DIO_WritePinVal(LCD_d5Pin,Get_Bit(data,5));
	DIO_WritePinVal(LCD_d4Pin,Get_Bit(data,4));
	
	DIO_WritePinVal(LCD_ENPin,HIGH);
	TIMER0_Delay_Ms(1);
	DIO_WritePinVal(LCD_ENPin,LOW);

	TIMER0_Delay_Ms(1);
	
	DIO_WritePinVal(LCD_d7Pin,Get_Bit(data,3));
	DIO_WritePinVal(LCD_d6Pin,Get_Bit(data,2));
	DIO_WritePinVal(LCD_d5Pin,Get_Bit(data,1)); 
	DIO_WritePinVal(LCD_d4Pin,Get_Bit(data,0));
	
	DIO_WritePinVal(LCD_ENPin,HIGH);
	TIMER0_Delay_Ms(1);
	DIO_WritePinVal(LCD_ENPin,LOW);
	TIMER0_Delay_Ms(1);

}
///////////////////////////////////////////////////////////////
void LCD_INIT(){
  
        DIO_WritePinDir(LCD_RSPin,OutPut);
        DIO_WritePinDir(LCD_RWPin,OutPut);
        DIO_WritePinDir(LCD_ENPin,OutPut);
        DIO_WritePinDir(LCD_d7Pin,OutPut);
        DIO_WritePinDir(LCD_d6Pin,OutPut);
        DIO_WritePinDir(LCD_d5Pin,OutPut);
        DIO_WritePinDir(LCD_d4Pin,OutPut);
	
	
	TIMER0_Delay_Ms(1);
	LCD_COMMAND(0x33); // go to 4 bit mode
	LCD_COMMAND(0x32); // go to 4 bit mode
	LCD_COMMAND(0x28); //if 4 bit 2 line init
	LCD_COMMAND(0x0e); // display on cursor on
	LCD_COMMAND(0x01); // clear lcd
	TIMER0_Delay_Ms(20);
	LCD_COMMAND(0x06); // increament el cursor m3 el ktaba
	TIMER0_Delay_Ms(10);
	
	
}
///////////////////////////////////////////////////////////////
void LCD_GoToXY(unsigned char x,unsigned char y){
	unsigned char firstCharAdr[]={0x80,0xc0,0x94,0xd4};
	LCD_COMMAND(firstCharAdr[y-1]+x-1);
	TIMER0_Delay_Ms(100);
}
///////////////////////////////////////////////////////////////
void LCD_Print(char *str){
	unsigned char i=0;
	while(str[i]!=0){
		LCD_DATA(str[i]);
		i++;
	}
}