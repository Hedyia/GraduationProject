#include "UART_CONFIG.h"
#include "UART_INTERFACING.h"
#include "TIMER_CONFIG.h"
#include "TIMER_INTERFACING.h"
#include "GPRS.h"
#include <string.h>

static char weblink1[]="AT+HTTPPARA=\"URL\",\"http://data.sparkfun.com/input/NJWOZD9RmbtabDyJOELK?private_key=5dPZJ0bDnmC7gBj2dbx4";
static char weblink2[]="AT+HTTPPARA=\"URL\",\"http://data.sparkfun.com/input/vV7xJ93AjOczzLaxwAJ6?private_key=aRmgnqy75dhaaepWoml4";
static char getDir[]="AT+HTTPPARA=\"URL\",\"http://data.sparkfun.com/output/OwaK9WxmLYTKvQRAJa38?private_key=828m0NXZnvi5YDvy76KN\"\r\n";
static char clear1[]="AT+HTTPPARA=\"URL\",\"http://data.sparkfun.com/input/NJWOZD9RmbtabDyJOELK/clear?private_key=5dPZJ0bDnmC7gBj2dbx4\"\r\n";
static char clear2[]="AT+HTTPPARA=\"URL\",\"http://data.sparkfun.com/input/vV7xJ93AjOczzLaxwAJ6/clear?private_key=aRmgnqy75dhaaepWoml4\"\r\n";
extern char g_command_response ;
extern char NumberOfDataAvailableForReadForGprs ;
extern char gps_parameters[150];
extern char latitude_data[20];
extern char longitude_data[20];
//extern char Speed[20];
extern char g_com_port;
extern char Uart5_Receive [];
char * Order;
char state;
char Dir;
//char *testbuf;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
char GPRS_INIT(char g_com_port){
  
  UART_INIT(g_com_port,BR_19200);
  UART_WRITE_STRING(g_com_port,"AT+CSQ\r\n");
  TIMER0_Delay_Ms(100);
  UART_WRITE_STRING(g_com_port,"AT+CGATT?\r\n");
  TIMER0_Delay_Ms(100);
  UART_WRITE_STRING(g_com_port,"AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n");            //setting the SAPBR, the connection type is using gprs
  TIMER0_Delay_Ms(1000);
  UART_WRITE_STRING(g_com_port,"AT+SAPBR=3,1,\"APN\",\"CMNET\"\r\n");               //setting the APN, the second need you fill in your local apn server
  TIMER0_Delay_Ms(4000);
  UART_WRITE_STRING(g_com_port,"AT+SAPBR=1,1\r\n");                                 //setting the SAPBR, for detail you can refer to the AT command mamual
  TIMER0_Delay_Ms(2000);
}

////////////////////////////////////////////////////////////////////////////////
char Http_INIT(char g_com_port){
  UART_WRITE_STRING(g_com_port,"AT+HTTPINIT\r\n");                                  //init the HTTP request
  TIMER0_Delay_Ms(2000);
}

////////////////////////////////////////////////////////////////////////////////
char Start_Communication(char g_com_port, char * HeartBeats,char *Temp,char * speed){
  Http_INIT(g_com_port);
  char webservice[400];
  
  strcpy(webservice,weblink2);
  strcat(webservice,"&heartbeats=");
  strcat(webservice,HeartBeats);
  strcat(webservice,"&latitude=");
  strcat(webservice,latitude_data);
  strcat(webservice,"&longtude=");
  strcat(webservice,longitude_data);
  strcat(webservice,"&speed=");
  strcat(webservice,speed);
  strcat(webservice,"&temperature=");
  strcat(webservice,Temp);
  strcat(webservice,"\"\r\n");
  
  
  UART_WRITE_STRING(g_com_port,webservice);                             // setting the httppara, the second parameter is the website you want to access
  TIMER0_Delay_Ms(1000);
  UART_WRITE_STRING(g_com_port,"AT+HTTPACTION=0\r\n");                              //submit the request 
  TIMER0_Delay_Ms(4000);
  UART_WRITE_STRING(g_com_port,"AT+HTTPREAD\r\n");                                  // read the data from the website you access
  TIMER0_Delay_Ms(300);
  UART_WRITE_STRING(g_com_port,"AT+HTTPTERM\r\n");
  TIMER0_Delay_Ms(500);
  
}
////////////////////////////////////////////////////////////////////////////////
void GetOrder(char g_com_port){
  
  Http_INIT(g_com_port);
  UART_WRITE_STRING(g_com_port,getDir);  
  TIMER0_Delay_Ms(1000);
  UART_WRITE_STRING(g_com_port,"AT+HTTPACTION=0\r\n");                          //submit the request 
  TIMER0_Delay_Ms(4000);
  //Clear_Buffer(g_com_port);
  UART_WRITE_STRING(g_com_port,"AT+HTTPREAD=0,32\r\n");                         // read the data from the website you access
  TIMER0_Delay_Ms(3000);
  //printf("%s",Uart5_Receive);
   
  
  Order=UART_READ_STRING(Uart5);
  char * FindState = strstr(Order,"timestamp");
  //printf("%s",FindState);
      Dir=FindState[11];
      state=FindState[10];

  
  UART_WRITE_STRING(g_com_port,"AT+HTTPTERM\r\n");
  TIMER0_Delay_Ms(500);
  
}
////////////////////////////////////////////////////////////////////////////////
char returnState(void){
  return Uart5_Receive[14];
}
////////////////////////////////////////////////////////////////////////////////
void Clear_Server(void){
  Http_INIT(g_com_port);
  UART_WRITE_STRING(g_com_port,clear1);                             // setting the httppara, the second parameter is the website you want to access
  TIMER0_Delay_Ms(1000);
  UART_WRITE_STRING(g_com_port,"AT+HTTPACTION=0\r\n");                              //submit the request 
  TIMER0_Delay_Ms(4000);
  UART_WRITE_STRING(g_com_port,"AT+HTTPTERM\r\n");
  TIMER0_Delay_Ms(500);
  
}
