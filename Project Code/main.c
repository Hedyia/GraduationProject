////////////////////////////////////////////////////////////////////////////////
//////////#Includes4Mcal////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdint.h>
#include <intrinsics.h>
#include <string.h>
#include "lm4f120h5qr.h"
#include "DIO_CONFIG.h"
#include "DIO_INTERFACING.h"
#include "TIMER_CONFIG.h"
#include "TIMER_INTERFACING.h"
#include "UART_CONFIG.h"
#include "UART_INTERFACING.h"
#include "ADC_CONFIG.h"
#include "ADC_INTERFACING.h"

#include "Common.h"
#include "GLOBAL.h"

////////////////////////////////////////////////////////////////////////////////
//////////#Includes4Hal/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "GPRS.h"
#include "GPS.h"
#include "LCDD.h"
#include "HeartSensor.h"
#include "TempSen.h"
////////////////////////////////////////////////////////////////////////////////
//////////GlobalVariables////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
extern char g_com_port;
extern char latitude_data[20];
extern char longitude_data[20];
extern char Date_Time[20];
extern char Speed[20];
extern char testbuf[];


//extern char Uart5_Receive[];
extern int Sclear;
char Sbuffer[20];
char Tbuffer[20];
double HeartSensor;
int temperature;
extern char state;
extern char Dir;
char arr[20];
double val;
double s;
////////////////////////////////////////////////////////////////////////////////
//////////ProtoTypes////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Buzzer_Alarm(void);
char * PrintSpeed(void);
////////////////////////////////////////////////////////////////////////////////
//////////MainFunction//////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int main()
{
  //__enable_interrupt();
  //////////////////////////////////////////////////////////////////////////////
  //////////McalInit////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  
  TIMER0_B_INIT();
  
  
  UART_INIT(Uart5,BR_19200);
  UART_INIT(Uart0,BR_19200);
  UART_INIT(Uart2,BR_9600);
  
  GPIO_PORTD_LOCK_R=UN_LOCK;
  GPIO_PORTD_CR_R=CR_VALUE;
  //////////////////////////////////////////////////////////////////////////////
  //////////HalInit/////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  LCD_INIT();
  LCD_Print("waiting......");
  HeartSensor_INIT();
  TempSen_INIT();
  TIMER0_Delay_Ms(6000);
  GPS_Start();
  GPRS_INIT(g_com_port);
  //Clear_Server();
  TIMER0_A_INIT();
  //Http_INIT(g_com_port);
  
  //GPIO_PORTA_LOCK_R=UN_LOCK;
  //GPIO_PORTA_CR_R=CR_VALUE;
  //GPIO_PORTC_LOCK_R=UN_LOCK;
  //GPIO_PORTC_CR_R=CR_VALUE;

  //////////////////////////////////////////////////////////////////////////////
  //////////LocalVariables//////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  //double HeartSensor2;
  
  
  //////////////////////////////////////////////////////////////////////////////
  //////////WhileLoop///////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  
  while(1){
    GetOrder(g_com_port);
    /*if(Sclear ==4){
      Clear_Server();
    }*/
    temperature=TempSen_Read(); 
    sprintf(Tbuffer, "Temp = %dC", temperature);                                //*330/4096
    GPS_Start();
    GPS_Read(g_com_port);
    val=atof(Speed);
    s=(val*0.27777777);
    strcpy(arr,"urSpd ");
    sprintf(Sbuffer, "%4.2f", s);
    strcat(arr,Sbuffer);
    strcat(arr," m");
    strcat(arr,"/");
    strcat(arr,"s");
    ////////////////////////////////////////////////////////////////////////////
    if((state==0)||(state=='0')){                                                               //for monitoring only
      LCD_COMMAND(0x01);
      TIMER0_Delay_Ms(10); 
      LCD_GoToXY(1,1);
      LCD_Print(Read_HeartBeats());
      LCD_GoToXY(1,2);
      LCD_Print(Tbuffer);
      Start_Communication(g_com_port,Read_HeartBeats(),Tbuffer,arr);
      GPS_Close();
    }else if(state=='1'){                                                         //for control direction and monitoring
      LCD_COMMAND(0x01);
      TIMER0_Delay_Ms(10);
      LCD_GoToXY(1,1);
      switch(Dir){
        case '0':
               LCD_Print("Stop");
               Buzzer_Alarm();
          break;
        case '1':
               LCD_Print("Turn Right");
               Buzzer_Alarm();
          break;
        case '2':
               LCD_Print("Turn Left");
               Buzzer_Alarm();
          break;
        case '3':
               LCD_Print("Go Along");
               Buzzer_Alarm();
          break;
        case '4':Buzzer_Alarm();
               LCD_Print("Go Back");
          break;
        default:
        break;
      }
      LCD_GoToXY(1,2);
      
      LCD_Print(arr);
      Start_Communication(g_com_port,Read_HeartBeats(),Tbuffer,arr);
      GPS_Close();
    }else{
      LCD_COMMAND(0x01);
      TIMER0_Delay_Ms(10);
      LCD_GoToXY(1,1);
      LCD_Print("Connection Error");
      LCD_GoToXY(1,2);
      LCD_Print(Read_HeartBeats());
    }
    
////////////////////////////////////////////////////////////////////////////////
//////////TestingPart///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
    //LCD_COMMAND(0x01);
    //TIMER0_Delay_Ms(10);
    //Read_HeartBeats();
    //printf("%s",Read_HeartBeats());
    //printf("%s",UART_READ_STRING(Uart2));
    /*LCD_GoToXY(1,1);
    LCD_Print(Read_HeartBeats());*/
      //TIMER0_Delay_Ms(1000);
    //printf("%s",Uart2_Receive);
    //TIMER0_Delay_Ms(1000);
    //Clear_Buffer(g_com_port);
    // Http_INIT(g_com_port);
    //LCD_COMMAND(0x01);
    //TIMER0_Delay_Ms(1000);
    /* LCD_COMMAND(0x01);
    LCD_DATA(Dir);
    TIMER0_Delay_Ms(50);
    LCD_DATA(state);*/
    //////////HEARTSENSORPROCESS////////////////////////////////////////////////
 
    //TIMER0_Delay_Ms(1000);
    
    // LCD_COMMAND(0x01);
    /*GPS_Start();
    GPS_Read(g_com_port);
    printf("Lat\:\r%s\n",latitude_data);
    printf("Long\:\r%s\n",longitude_data);
    printf("Date\:\r%s\n",Date_Time);
    printf("Speed\:\r%s\n",Speed);
    GPS_Close();*/
    //LCD_Print(GPS_Read(g_com_port));
     //Http_INIT(g_com_port);
     //Start_Communication(g_com_port,"120","37");
  
    /* LCD_COMMAND(0x01);
    LCD_Print(latitude_data);
     TIMER0_Delay_Ms(1000);
    LCD_COMMAND(0x01);
    LCD_Print(longitude_data);
    
    TIMER0_Delay_Ms(1000);
    LCD_COMMAND(0x01);
    TIMER0_Delay_Ms(5);*/
    //__enable_interrupt();//
  
  }
  
  return 0;
}
void Buzzer_Alarm(void){
  DIO_WritePinDir(PF4,OutPut);
  DIO_WritePinVal(PF4,HIGH);
  TIMER0_Delay_Ms(1000);
  DIO_WritePinVal(PF4,LOW);
}
char *PrintSpeed(void){
  
  strcpy(arr,"urSpeed");
  strcat(arr,Speed);
  return arr;
}

