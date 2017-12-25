#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_
////////////////////////////////////////////////////////////////////////////////
//////////PROTOTYPES////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void UART_INIT(char U_NUM,long int baudRate);
void UART_TRANSMIT(char U_NUM,char DATA);
char UART_RECIEVER(char U_NUM);
void UART_WRITE_STRING(char U_NUM,char const * string);
char* UART_READ_STRING(char U_NUM );
void Clear_Buffer(char U_NUM);
void UART_STR_ZERO(void);


////////////////////////////////////////////////////////////////////////////////
//////////CONFIGRATIONS/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define UARTSysClk  16000000.0f
#define ClkDiv 16.0f
#define SYS_CLOCK 0
#define WLEN 0x3
#define WLEN_SHIFT 5


#define Uart0_Buffer_Length 20
#define Uart1_Buffer_Length 20
#define Uart2_Buffer_Length 10
#define Uart3_Buffer_Length 20
#define Uart4_Buffer_Length 20
#define Uart5_Buffer_Length 600
#define Uart6_Buffer_Length 20
#define Uart7_Buffer_Length 20

////////////////////////////////////////////////////////////////////////////////
//////////BAUDRATES/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
enum UART_BAUDRATE_t {
    BR_110    = 110,
    BR_300    = 300,
    BR_600    = 600,
    BR_1200   = 1200,
    BR_2400   = 2400,
    BR_4800   = 4800,
    BR_9600   = 9600,
    BR_14400  = 14400,
    BR_19200  = 19200,
    BR_28800  = 28800,
    BR_38400  = 38400,
    BR_56000  = 56000,
    BR_57600  = 57600,
    BR_115200 = 115200,
    BR_128000 = 128000,
    BR_153600 = 153600,
    BR_230400 = 230400,
    BR_256000 = 256000,
    BR_460800 = 460800,
    BR_921600 = 921600
};

#endif // UART_CONFIG_H_