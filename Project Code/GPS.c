#include "UART_CONFIG.h"
#include "UART_INTERFACING.h"
#include "TIMER_CONFIG.h"
#include "TIMER_INTERFACING.h"
#include "GPS.h"
#include <string.h>

extern char NumberOfDataAvailableForReadForGps ;
extern char g_command_response ;
extern char Uart5_Receive[];
extern char g_com_port;
extern char latitude_data[20];
extern char longitude_data[20];
extern char Date_Time[20];
extern char Speed[20];


char flagGps=0;
char nullFlag=0;
char *Info;
char initDate;
char initLat;
char initLong;
char initSpeed;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
char GPS_Start(void){
  UART_WRITE_STRING(g_com_port,"AT+CGNSPWR=1\r\n");
  TIMER0_Delay_Ms(100);
}

////////////////////////////////////////////////////////////////////////////////
void GPS_Read(int g_com_port){
  
  UART_WRITE_STRING(g_com_port,"AT+CGNSSEQ=\"RMC\"\r\n");
  TIMER0_Delay_Ms(2000);
  UART_WRITE_STRING(g_com_port,"AT+CGNSURC=1\r\n");
  TIMER0_Delay_Ms(2000);
  UART_WRITE_STRING(g_com_port,"AT+CGNSINF\r\n");
  Info=UART_READ_STRING(g_com_port);
  TIMER0_Delay_Ms(2000);
  //printf("%s\n",Info);
  //return Uart5_Receive;
  int i;
  initDate=0;
  initLat=0;
  initLong=0;
  initSpeed=0;
  
  
  char *result = strstr(Info,"+UGNSINF: 1,1,");                                 //orCGNSINF: 1,1,
//  printf("%s\n",result);
  for(i=14;i<strlen(result);i++){
    if(result[i]==','){
      flagGps++;
    }else{
      switch(flagGps){
               case 0: Date_Time[initDate]=result[i];
                       initDate++;
               break;
               case 1: latitude_data[initLat]=result[i];
                       initLat++;
               break;
               case 2: longitude_data[initLong]=result[i];
                       initLong++;
               break;
               case 4: Speed[initSpeed]=result[i];
                       initSpeed++;
               default:
                 break;
               }
    }
    if(flagGps>4){
      flagGps=0;
      
      break;
    }
  }
  
  
}

////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
char GPS_Close(void){
  UART_WRITE_STRING(g_com_port,"AT+CGNSPWR=0\r\n");
  TIMER0_Delay_Ms(100);
}