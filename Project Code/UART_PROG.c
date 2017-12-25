#include "LM4F120H5QR.h"
#include "UART_CONFIG.h"
#include "UART_INTERFACING.h"
#include "Common.h"
#include "TM4C123GH6PM.h"

volatile char ReceiveComplete0 =0;
volatile char i0=0;
volatile char ReceiveComplete1 =0;
volatile char i1=0;
volatile char ReceiveComplete2 =0;
volatile char i2=0;
volatile char ReceiveComplete3 =0;
volatile char i3=0;
volatile char ReceiveComplete4 =0;
volatile char i4=0;
volatile char ReceiveComplete5 =0;
volatile char i5=0;
volatile char ReceiveComplete6 =0;
volatile char i6=0;
volatile char ReceiveComplete7 =0;
volatile char i7=0;

volatile char Uart0_Receive[Uart0_Buffer_Length];
volatile char Uart1_Receive[Uart1_Buffer_Length];
volatile char Uart2_Receive[Uart2_Buffer_Length];
volatile char Uart3_Receive[Uart3_Buffer_Length];
volatile char Uart4_Receive[Uart4_Buffer_Length];
volatile char Uart5_Receive[Uart5_Buffer_Length];
volatile char Uart6_Receive[Uart6_Buffer_Length];
volatile char Uart7_Receive[Uart7_Buffer_Length];

char arrBack[500];
////////////////////////////////////////////////////////////////////////////////
//////////InterruptProtoType////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void UART0_ISR(void);
void UART1_ISR(void);
void UART2_ISR(void);
void UART3_ISR(void);
void UART4_ISR(void);
void UART5_ISR(void);
void UART6_ISR(void);
void UART7_ISR(void);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

UART_STRUCT UART[8]={{Uart0,PORTA,PIN0,PIN1,PCLR_NUM0,PCLR_NUM1},{99,99,99,99,99,99},
{Uart2,PORTD,PIN6,PIN7,PCLR_NUM6,PCLR_NUM7},{Uart3,PORTC,PIN6,PIN7,PCLR_NUM6,PCLR_NUM7},
{Uart4,PORTC,PIN4,PIN5,PCLR_NUM4,PCLR_NUM5},{Uart5,PORTE,PIN4,PIN5,PCLR_NUM4,PCLR_NUM5},
{Uart6,PORTD,PIN4,PIN5,PCLR_NUM4,PCLR_NUM5},{Uart7,PORTE,PIN0,PIN1,PCLR_NUM0,PCLR_NUM1}};

/*void Delay(double j )
{
  double i=10000*j;
  while(--i);
}*/

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void UART_INIT(char U_NUM,long int baudRate){
    char check =ok ;
    
    float BRDI_float=UARTSysClk/(ClkDiv * baudRate);
    uint16_t BAUD_RATE     = (uint16_t)BRDI_float;
    BRDI_float = BRDI_float - (long)BRDI_float;
    uint8_t FRACTION_PART = (uint8_t)(BRDI_float * 64 + 0.5);
    
    //NVIC_EnableIRQ(UART5_IRQn);                                                                             //enable interrupt
    Set_Bit(SYSCTL_RCGCUART_R,UART[U_NUM].UART_NUM);                                                        // provide clock to UART
    Set_Bit(SYSCTL_RCGCGPIO_R,UART[U_NUM].PORT_NUM);                                                        //enable clock to PORTA
    switch(UART[U_NUM].PORT_NUM){
    case 0:     Set_Two_Bits(GPIOA->AFSEL,UART[U_NUM].URx,UART[U_NUM].UTx);                           //USE ALTERNATIVE FUNCTIONS
                Set_Two_Bits(GPIOA->DEN,UART[U_NUM].URx,UART[U_NUM].UTx);                             //ENABLE DIGITAL
                Set_Two_Bits(GPIOA->PCTL,UART[U_NUM].PCLR_Rx,UART[U_NUM].PCLR_Tx);                    //USE PINS AS UART
      break;
    case 1:     Set_Two_Bits(GPIOB->AFSEL,UART[U_NUM].URx,UART[U_NUM].UTx);                           //USE ALTERNATIVE FUNCTIONS
                Set_Two_Bits(GPIOB->DEN,UART[U_NUM].URx,UART[U_NUM].UTx);                             //ENABLE DIGITAL
                Set_Two_Bits(GPIOB->PCTL,UART[U_NUM].PCLR_Rx,UART[U_NUM].PCLR_Tx);                    //USE PINS AS UART
      break;
    case 2:     Set_Two_Bits(GPIOC->AFSEL,UART[U_NUM].URx,UART[U_NUM].UTx);                           //USE ALTERNATIVE FUNCTIONS
                Set_Two_Bits(GPIOC->DEN,UART[U_NUM].URx,UART[U_NUM].UTx);                             //ENABLE DIGITAL
                Set_Two_Bits(GPIOC->PCTL,UART[U_NUM].PCLR_Rx,UART[U_NUM].PCLR_Tx);                    //USE PINS AS UART
      break;
    case 3:     Set_Two_Bits(GPIOD->AFSEL,UART[U_NUM].URx,UART[U_NUM].UTx);                           //USE ALTERNATIVE FUNCTIONS
                Set_Two_Bits(GPIOD->DEN,UART[U_NUM].URx,UART[U_NUM].UTx);                             //ENABLE DIGITAL
                Set_Two_Bits(GPIOD->PCTL,UART[U_NUM].PCLR_Rx,UART[U_NUM].PCLR_Tx);                    //USE PINS AS UART
      break;
    case 4:     Set_Two_Bits(GPIOE->AFSEL,UART[U_NUM].URx,UART[U_NUM].UTx);                           //USE ALTERNATIVE FUNCTIONS
                Set_Two_Bits(GPIOE->DEN,UART[U_NUM].URx,UART[U_NUM].UTx);                             //ENABLE DIGITAL
                Set_Two_Bits(GPIOE->PCTL,UART[U_NUM].PCLR_Rx,UART[U_NUM].PCLR_Tx);                    //USE PINS AS UART
      break;
    case 5:     Set_Two_Bits(GPIOF->AFSEL,UART[U_NUM].URx,UART[U_NUM].UTx);                           //USE ALTERNATIVE FUNCTIONS
                Set_Two_Bits(GPIOF->DEN,UART[U_NUM].URx,UART[U_NUM].UTx);                             //ENABLE DIGITAL
                Set_Two_Bits(GPIOF->PCTL,UART[U_NUM].PCLR_Rx,UART[U_NUM].PCLR_Tx);                    //USE PINS AS UART
      break;
      default:check=error ;
      break;
    }
  ////////////////////////////////////////////////////////////
     switch(UART[U_NUM].UART_NUM){
    case 0:   NVIC_EnableIRQ(UART0_IRQn);
              Clr_Bit(UART0->CTL,UARTEN);                                       //disable UART
              UART0->IBRD=BAUD_RATE;                                            //16MHz/16=1MHz, 1MHz/104=9600 baud rate
              UART0->FBRD=FRACTION_PART;                                        //fraction part
              UART0->LCRH  |=(WLEN <<WLEN_SHIFT);                               //8-bit, no parity, 1-stop bit, no FIFO
              UART0->CC =SYS_CLOCK;                                             //use system clock
              Set_Three_Bits(UART0->CTL,UARTEN,TXE,RXE);                        //enable UART, TXE, RXE
              Set_Bit(UART0->IM,RXIM);
      break;
    case 1:   NVIC_EnableIRQ(UART1_IRQn);
              Clr_Bit(UART1->CTL,UARTEN);                                       //disable UART
              UART1->IBRD=BAUD_RATE;                                            //16MHz/16=1MHz, 1MHz/104=9600 baud rate
              UART1->FBRD=FRACTION_PART;                                        //fraction part
              UART1->LCRH  |=(WLEN <<WLEN_SHIFT);                               //8-bit, no parity, 1-stop bit, no FIFO
              UART1->CC =SYS_CLOCK;                                             //use system clock
              Set_Three_Bits(UART1->CTL,UARTEN,TXE,RXE);                        //enable UART, TXE, RXE
              Set_Bit(UART1->IM,RXIM);
      break;
    case 2:   NVIC_EnableIRQ(UART2_IRQn);
              Clr_Bit(UART2->CTL,UARTEN);                                       //disable UART
              UART2->IBRD=BAUD_RATE;                                            //16MHz/16=1MHz, 1MHz/104=9600 baud rate
              UART2->FBRD=FRACTION_PART;                                        //fraction part
              UART2->LCRH  |=(WLEN <<WLEN_SHIFT);                               //8-bit, no parity, 1-stop bit, no FIFO
              UART2->CC =SYS_CLOCK;                                             //use system clock
              Set_Three_Bits(UART2->CTL,UARTEN,TXE,RXE);                        //enable UART, TXE, RXE
              Set_Bit(UART2->IM,RXIM);
      break;
    case 3:   NVIC_EnableIRQ(UART3_IRQn);
              Clr_Bit(UART3->CTL,UARTEN);                                       //disable UART
              UART3->IBRD=BAUD_RATE;                                            //16MHz/16=1MHz, 1MHz/104=9600 baud rate
              UART3->FBRD=FRACTION_PART;                                        //fraction part
              UART3->LCRH  |=(WLEN <<WLEN_SHIFT);                               //8-bit, no parity, 1-stop bit, no FIFO
              UART3->CC =SYS_CLOCK;                                             //use system clock
              Set_Three_Bits(UART3->CTL,UARTEN,TXE,RXE);                        //enable UART, TXE, RXE
              Set_Bit(UART3->IM,RXIM);
      break;
    case 4:   NVIC_EnableIRQ(UART4_IRQn);
              Clr_Bit(UART4->CTL,UARTEN);                                       //disable UART
              UART4->IBRD=BAUD_RATE;                                            //16MHz/16=1MHz, 1MHz/104=9600 baud rate
              UART4->FBRD=FRACTION_PART;                                        //fraction part
              UART4->LCRH  |=(WLEN <<WLEN_SHIFT);                               //8-bit, no parity, 1-stop bit, no FIFO
              UART4->CC =SYS_CLOCK;                                             //use system clock
              Set_Three_Bits(UART4->CTL,UARTEN,TXE,RXE);                        //enable UART, TXE, RXE
              Set_Bit(UART4->IM,RXIM);
      break;
    case 5:   NVIC_EnableIRQ(UART5_IRQn);
              Clr_Bit(UART5->CTL,UARTEN);
              UART5->IBRD=BAUD_RATE;
              UART5->FBRD=FRACTION_PART;
              UART5->LCRH |=(WLEN <<WLEN_SHIFT);
              Set_Bit(UART5->LCRH,FEN);
              UART5->CC =SYS_CLOCK;
              Set_Three_Bits(UART5->CTL,UARTEN,TXE,RXE);
              Set_Bit(UART5->IM,RXIM);                                          //ENABLE INTERRUPT

      break;
    case 6:   NVIC_EnableIRQ(UART6_IRQn);
              Clr_Bit(UART6->CTL,UARTEN);                                       //disable UART
              UART6->IBRD=BAUD_RATE;                                            //16MHz/16=1MHz, 1MHz/104=9600 baud rate
              UART6->FBRD=FRACTION_PART;                                        //fraction part
              UART6->LCRH  |=(WLEN <<WLEN_SHIFT);                               //8-bit, no parity, 1-stop bit, no FIFO
              UART6->CC =SYS_CLOCK;                                             //use system clock
              Set_Three_Bits(UART6->CTL,UARTEN,TXE,RXE);                        //enable UART, TXE, RXE
              Set_Bit(UART6->IM,RXIM);
      break;
    case 7:   NVIC_EnableIRQ(UART7_IRQn);
              Clr_Bit(UART7->CTL,UARTEN);                                       //disable UART
              UART7->IBRD=BAUD_RATE;                                            //16MHz/16=1MHz, 1MHz/104=9600 baud rate
              UART7->FBRD=FRACTION_PART;                                        //fraction part
              UART7->LCRH  |=(WLEN <<WLEN_SHIFT);                               //8-bit, no parity, 1-stop bit, no FIFO
              UART7->CC =SYS_CLOCK;                                             //use system clock
              Set_Three_Bits(UART7->CTL,UARTEN,TXE,RXE);                        //enable UART, TXE, RXE
              Set_Bit(UART7->IM,RXIM);
      break;
    default: check=error ;
      break;
    
  }
}

////////////////////////////////////////////////////////////////////////////////
void UART_TRANSMIT(char U_NUM,char DATA){
  
  char check =ok ;
  
  switch(UART[U_NUM].UART_NUM){
    case 0:   
              while(Get_Bit(UART0->FR,TXFF)!=0);                                //wait until Tx buffer not full
              UART0->DR=DATA;                                                   //before giving it another byte     
      break;
    case 1:   
              while(Get_Bit(UART1->FR,TXFF)!=0);                                //wait until Tx buffer not full
              UART1->DR=DATA;                                                   //before giving it another byte     
      break;
    case 2:   
              while(Get_Bit(UART2->FR,TXFF)!=0);                                //wait until Tx buffer not full
              UART2->DR=DATA;                                                   //before giving it another byte     
      break;
    case 3:   
              while(Get_Bit(UART3->FR,TXFF)!=0);                                //wait until Tx buffer not full
              UART3->DR=DATA;                                                   //before giving it another byte     
      break;
    case 4:   
              while(Get_Bit(UART4->FR,TXFF)!=0);                                //wait until Tx buffer not full
              UART4->DR=DATA;                                                   //before giving it another byte     
      break;
    case 5:   
              while(Get_Bit(UART5->FR,TXFF)!=0);                                //wait until Tx buffer not full
              UART5->DR=DATA;                                                   //before giving it another byte     
      break;
    case 6:   
              while(Get_Bit(UART6->FR,TXFF)!=0);                                //wait until Tx buffer not full
              UART6->DR=DATA;                                                   //before giving it another byte     
      break;
    case 7:   
              while(Get_Bit(UART7->FR,TXFF)!=0);                                //wait until Tx buffer not full
              UART7->DR=DATA;                                                   //before giving it another byte     
      break;
    default: check=error ;
      break;
    
  }
  
}

////////////////////////////////////////////////////////////////////////////////
char UART_RECIEVER(char U_NUM ){
  char check =ok ;
  
  switch(UART[U_NUM].UART_NUM){
    case 0:  
              //while(Get_Bit(UART0_FR_R,RXFE)!=0);                               //wait until the buffer is not empty
              return Uart0_Receive[0];                                               //read the received data
              
      break;
    case 1:   
              //while(Get_Bit(UART1_FR_R,RXFE)!=0);
              return Uart1_Receive[0];
      break;
    case 2:  
              //while(Get_Bit(UART2_FR_R,RXFE)!=0);
              return Uart2_Receive[0];
      break;
    case 3:   
              //while(Get_Bit(UART3_FR_R,RXFE)!=0);
              return Uart3_Receive[0];
      break;
    case 4:   
              //while(Get_Bit(UART4_FR_R,RXFE)!=0);
              return Uart4_Receive[0];
      break;
    case 5: 
              //while(Get_Bit(UART5_FR_R,RXFE)!=0);
              return Uart5_Receive[0];
      break;
    case 6:  
              //while(Get_Bit(UART6_FR_R,RXFE)!=0);
              return Uart6_Receive[0];
      break;
    case 7:  
              //while(Get_Bit(UART7_FR_R,RXFE)!=0);
              return Uart7_Receive[0];
      break;
    default: check=error ;
      break;
    
  }
  
  
}
////////////////////////////////////////////////////////////////////////////////
void UART_WRITE_STRING(char U_NUM,char const * string)
{
  while(*string != '\0')
  {
    UART_TRANSMIT(U_NUM,* string );
    string++;
  }
}
////////////////////////////////////////////////////////////////////////////////
char* UART_READ_STRING(char U_NUM ){
  
  switch(U_NUM){
  case 0:strcpy(arrBack,Uart0_Receive);
  break;
  case 1:strcpy(arrBack,Uart1_Receive);
  break;
  case 2:strcpy(arrBack,Uart2_Receive);
  break;
  case 3:strcpy(arrBack,Uart3_Receive);
  break;
  case 4:strcpy(arrBack,Uart4_Receive);
  break;
  case 5:strcpy(arrBack,Uart5_Receive);
  break;
  case 6:strcpy(arrBack,Uart6_Receive);
  break;
  case 7:strcpy(arrBack,Uart7_Receive);
  break;
  default:
    break;
    
  } 
  return arrBack;
}
////////////////////////////////////////////////////////////////////////////////
void Clear_Buffer(char U_NUM){
  switch(U_NUM){
  case 0:memset(Uart0_Receive,'0',Uart0_Buffer_Length);
  break;
  case 1:memset(Uart1_Receive,'0',Uart1_Buffer_Length);
  break;
  case 2:memset(Uart2_Receive,'0',Uart2_Buffer_Length);
  break;
  case 3:memset(Uart3_Receive,'0',Uart3_Buffer_Length);
  break;
  case 4:memset(Uart4_Receive,'0',Uart4_Buffer_Length);
  break;
  case 5:memset(Uart5_Receive,'0',Uart5_Buffer_Length);
  break;
  case 6:memset(Uart6_Receive,'0',Uart6_Buffer_Length);
  break;
  case 7:memset(Uart7_Receive,'0',Uart7_Buffer_Length);
  break;
  default:
    break;
  }
}
////////////////////////////////////////////////////////////////////////////////
void UART0_ISR(void)
{
  Uart0_Receive[i0]=UART0->DR;
    if(Uart0_Receive[i0]==*("\n")){
      Clr_Bit(UART0->ICR,RXIC);
    i0=0;
    }else{
      i0++;
    }

}
////////////////////////////////////////////////////////////////////////////////
void UART1_ISR(void)
{
 Uart1_Receive[i1]=UART1->DR;
    if(Uart1_Receive[i1]==*("\n")){
      Clr_Bit(UART1->ICR,RXIC);
    i1=0;
    }else{
      i1++;
    }

}
////////////////////////////////////////////////////////////////////////////////
void UART2_ISR(void)
{
    Uart2_Receive[i2]=UART2->DR;
    if(Uart2_Receive[i2]==*("\n")){
      Clr_Bit(UART2->ICR,RXIC);
    i2=0;
    }else{
      i2++;
    }

}
////////////////////////////////////////////////////////////////////////////////
void UART3_ISR(void)
{
  Uart3_Receive[i3]=UART3->DR;
    if(Uart3_Receive[i3]==*("\n")){
      Clr_Bit(UART3->ICR,RXIC);
    i3=0;
    }else{
      i3++;
    }

}
////////////////////////////////////////////////////////////////////////////////
void UART4_ISR(void)
{
  Uart4_Receive[i4]=UART4->DR;
    if(Uart4_Receive[i4]==*("\n")){
      Clr_Bit(UART4->ICR,RXIC);
    i4=0;
    }else{
      i4++;
    }

}
////////////////////////////////////////////////////////////////////////////////
void UART5_ISR(void)
{
 /*if(i5 ==0){
    Clear_Buffer(Uart5);
  }*/
  Uart5_Receive[i5]=UART5->DR;
  //UART_TRANSMIT(0,UART5->DR);
  if(i5==Uart5_Buffer_Length){
    ReceiveComplete5 =1;
  i5=0;}
  i5++;
  if(ReceiveComplete5==1){
    Clr_Bit(UART5->ICR,RXIC);
    i5=0;
  }
  
}
////////////////////////////////////////////////////////////////////////////////
void UART6_ISR(void)
{
  Uart6_Receive[i6]=UART6->DR;
    if(Uart6_Receive[i6]==*("\n")){
      Clr_Bit(UART6->ICR,RXIC);
    i6=0;
    }else{
      i6++;
    }

}

////////////////////////////////////////////////////////////////////////////////
void UART7_ISR(void)
{
 Uart7_Receive[i7]=UART7->DR;
    if(Uart7_Receive[i7]==*("\n")){
      Clr_Bit(UART7->ICR,RXIC);
    i7=0;
    }else{
      i7++;
    }

}