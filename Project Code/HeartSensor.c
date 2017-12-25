#include "UART_CONFIG.h"
#include "UART_INTERFACING.h"
#include "DIO_INTERFACING.h"
#include "HeartSensor.h"
#include "TIMER_CONFIG.h"
#include "TIMER_INTERFACING.h"
#include <intrinsics.h>
#include "TM4C123GH6PM.h"
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
extern volatile char Uart2_Receive[];  
char *receiving;
char HBPM[10];
int i;
int j;
char H_alarm=0;
char * information;
////////////////////////////////////////////////////////////////////////////////
void HeartSensor_INIT(void){
  UART_INIT(Uart2,BR_9600);

}

////////////////////////////////////////////////////////////////////////////////
char *Read_HeartBeats(void){
  receiving=UART_READ_STRING(Uart2);
  //printf("%s",receiving);
  information=strstr(receiving,"*BPM=");
  for(i=0;i<strlen(information);i++){
    if(information[i]==*("\n")){
      break;
    }else{
      HBPM[i]=information[i];
    }
  }
  
  return HBPM;
 
}
////////////////////////////////////////////////////////////////////////////////
