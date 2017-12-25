#include "lm4f120h5qr.h"
#include "ADC_CONFIG.h"
#include "ADC_INTERFACING.h"
#include "Common.h" 
#include "DIO_INTERFACING.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ADC_INIT(char ADC_NUM, char CHANNEL_NUM){
  /*if(ADC_NUM==0){
  ADC0_ACTSS_R=ADCACTSS_INITIAL;
  ADC0_EMUX_R=ADCEMUX_INITIAL;}
  else if(ADC_NUM==1){
  
  
  ADC1_ACTSS_R=ADCACTSS_INITIAL;
  ADC1_EMUX_R=ADCEMUX_INITIAL;
  }else{
  }*/
  
  int PORT_NUM= CHANNEL_NUM/8;
  int PIN_INDEX=CHANNEL_NUM%8;
  
  char check =ok ;
  Set_Bit(SYSCTL_RCGCADC_R,ADC_NUM);        //choose adc module adc0 or adc1
  Set_Bit(SYSCTL_RCGCGPIO_R,PORT_NUM);          //enable port
  
   switch(PORT_NUM){
      
      case 1: Set_Bit(GPIO_PORTB_AFSEL_R,PIN_INDEX);
              Clr_Bit(GPIO_PORTB_DEN_R,PIN_INDEX);
              Set_Bit(GPIO_PORTB_AMSEL_R,PIN_INDEX);
      break;
     
      case 3: Set_Bit(GPIO_PORTD_AFSEL_R,PIN_INDEX);
              Clr_Bit(GPIO_PORTD_DEN_R,PIN_INDEX);
              Set_Bit(GPIO_PORTD_AMSEL_R,PIN_INDEX); 
      break;
      case 4: Set_Bit(GPIO_PORTE_AFSEL_R,PIN_INDEX);
              Clr_Bit(GPIO_PORTE_DEN_R,PIN_INDEX);
              Set_Bit(GPIO_PORTE_AMSEL_R,PIN_INDEX);
      break;
      
      default:check=error ;
      break;

  }
  
}

////////////////////////////////////////////////////////////////////////////////
int ADC_CONVERT(char ADC_NUM ,char CHANNEL_NUM){

  char check =ok ;
  char ADC_PIN;
  int result=0;

 // Set_Bit(SYSCTL_RCGCADC_R,ADC_NUM);        //choose adc module adc0 or adc1
  
  
  if(CHANNEL_NUM ==PE3){
    ADC_PIN =0;
  }else if(CHANNEL_NUM ==PE2){
    ADC_PIN =1;
  }else if(CHANNEL_NUM ==PE1){
    ADC_PIN =2;
  }else if(CHANNEL_NUM ==PE0){
    ADC_PIN =3;
  }else if(CHANNEL_NUM ==PD3){
    ADC_PIN =4;
  }else if(CHANNEL_NUM ==PD2){
    ADC_PIN =5;
  }else if(CHANNEL_NUM ==PD1){
    ADC_PIN =6;
  }else if(CHANNEL_NUM ==PD0){
    ADC_PIN =7;
  }else if(CHANNEL_NUM ==PE5){
    ADC_PIN =8;
  }else if(CHANNEL_NUM ==PE4){
    ADC_PIN =9;
  }else if(CHANNEL_NUM ==PB4){
    ADC_PIN =10;
  }else if(CHANNEL_NUM ==PB5){
    ADC_PIN =11;
  }else {
    check =error;
  }
  
  if(ADC_NUM==0){
   
              Clr_Bit(ADC0_ACTSS_R,ASDN3);               //Disable Sample Sequencer
              ADC0_EMUX_R &= ~0x0000F000;                //software trigger for ss3
              ADC0_SSMUX3_R=ADC_PIN;                     // select ADC input
              ADC0_SSCTL3_R |=0x6;                         //single-ended, one-conversion, and raw interrupt
              Set_Bit(ADC0_ACTSS_R,ASDN3);               //enable sample sequencer
              Set_Bit(ADC0_PSSI_R,SS3);                  // start conversion
              while(Get_Bit(ADC0_RIS_R,INTR3)==0);      //wait conversion
              result=ADC0_SSFIFO3_R;                  // Data read
              Set_Bit(ADC0_ISC_R,IN3);                   //clearINT3 flag
      
      
  }
  else if(ADC_NUM==1){
            Clr_Bit(ADC1_ACTSS_R,ASDN3);               //Disable Sample Sequencer
              ADC1_EMUX_R &= ~0x0000F000;                //software trigger for ss3
              ADC1_SSMUX3_R=ADC_PIN;                     // select ADC input
              ADC1_SSCTL3_R |=0x6;                         //single-ended, one-conversion, and raw interrupt
              Set_Bit(ADC1_ACTSS_R,ASDN3);               //enable sample sequencer
              Set_Bit(ADC1_PSSI_R,SS3);                  // start conversion
              while(Get_Bit(ADC1_RIS_R,INTR3)==0);      //wait conversion
              result=ADC1_SSFIFO3_R;                  // Data read
              Set_Bit(ADC1_ISC_R,IN3);                   //clearINT3 flag
              
     
  }else{
    check=error;
  }
  return result ;
}
////////////////////////////////////////////////////////////////////////////////
