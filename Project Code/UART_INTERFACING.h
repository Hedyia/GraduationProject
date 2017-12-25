
////////////////////////////////////////////////////////////////////////////////
//RCGCUART PINs
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7

//UARTCTL PINs
#define  UARTEN 0
#define  TXE 8
#define  RXE 9

//UARTFR PINs
#define CTS 0
#define BUSY 3
#define RXFE 4
#define TXFF 5
#define RXFF 6
#define TXFE 7

//UARTRIS PINs
#define RTRIS 6

//UART’IS PINs
#define RXMIS 6

//
#define RXIM 4
#define RXIC 4
#define FEN 4
////////////////////////////////////////////////////////////////////////////////
#define Uart0 0
#define Uart1 1
#define Uart2 2
#define Uart3 3
#define Uart4 4
#define Uart5 5
#define Uart6 6
#define Uart7 7
////////////////////////////////////////////////////////////////////////////////
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5
////////////////////////////////////////////////////////////////////////////////
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
////////////////////////////////////////////////////////////////////////////////
#define PCLR_NUM0 0
#define PCLR_NUM1 4
#define PCLR_NUM2 8
#define PCLR_NUM3 12
#define PCLR_NUM4 16
#define PCLR_NUM5 20
#define PCLR_NUM6 24
#define PCLR_NUM7 28


////////////////////////////////////////////////////////////////////////////////
typedef struct {
  char UART_NUM;
  char PORT_NUM;
  char URx;
  char UTx;
  char PCLR_Rx;
  char PCLR_Tx;
}UART_STRUCT;

