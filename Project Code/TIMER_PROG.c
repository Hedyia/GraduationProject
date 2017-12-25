#include "lm4f120h5qr.h"
#include "TIMER_CONFIG.h"
#include "TIMER_INTERFACING.h"
#include "Common.h"
#include "TM4C123GH6PM.h"
#include <intrinsics.h>

void (*PeriodicTask)(void);
void TIMER1A_ISR(void);
void TIMER0A_ISR(void);

int second=0;
int min=0;
int hour=0;
int Sclear=0;
int flag=0;
////////////////////////////////////////////////////////////////////////////////
void TIMER0_A_INIT(void){
  Set_Bit(SYSCTL_RCGCTIMER_R,Timer0);                                           /* enable clock to Timer Block 0 */
  Clr_Bit(TIMER0_CTL_R,TAEN);                                                   /* disable Timer before initialization */
  TIMER0_CFG_R = CFG_VALUE ;                                                    /* 16-bit option */
  TIMER0_TAMR_R=PERIODIC_MODE;                                                  /* periodic mode and down-counter */
  TIMER0_TAILR_R=TFCPUs-1;                                                       /* TimerB interval load value reg */
  Set_Bit(TIMER0_ICR_R,TATOCINT);                                               /* clear the TimerB timeout flag */
  Set_Bit(TIMER0_CTL_R,TAEN);                                                   /* enable TimerB after initialization */
  NVIC_EnableIRQ(TIMER0A_IRQn);
  Set_Bit(TIMER0->CTL,TAEN);
  
}
////////////////////////////////////////////////////////////////////////////////
void TIMER0_B_INIT(void){
  Set_Bit(SYSCTL_RCGCTIMER_R,Timer0);                                           /* enable clock to Timer Block 0 */
  Clr_Bit(TIMER0_CTL_R,TBEN);                                                   /* disable Timer before initialization */
  TIMER0_CFG_R = CFG_VALUE ;                                                    /* 16-bit option */
  TIMER0_TBMR_R=PERIODIC_MODE;                                                  /* periodic mode and down-counter */
  TIMER0_TBILR_R=TFCPUm-1;                                                       /* TimerB interval load value reg */
  Set_Bit(TIMER0_ICR_R,TBTOCINT);                                               /* clear the TimerB timeout flag */
  Set_Bit(TIMER0_CTL_R,TBEN);                                                   /* enable TimerB after initialization */
  
}
////////////////////////////////////////////////////////////////////////////////
void TIMER1_A_INIT (void(*task)(void)){                                                      
  Set_Bit(SYSCTL->RCGCTIMER ,Timer1);
  Clr_Bit(TIMER1->CTL,TAEN);
  TIMER1->CFG=CFG_VALUE;
  TIMER1->TAMR |=(0x2<<0);
  TIMER1->TAMR &=~(1<<4);
  TIMER1->TAILR=(2*TFCPUm)-1;
  TIMER1->IMR |=(1<<0);
  NVIC_EnableIRQ(TIMER1A_IRQn);
  Set_Bit(TIMER1->CTL,TAEN);
  
  PeriodicTask = task;
  
}
////////////////////////////////////////////////////////////////////////////////
void TIMER0_Delay_Ms(long MS){
  int i;
  for(i = 0; i < MS; i++){
    while( Get_Bit(TIMER0_RIS_R,TBTORIS)==0);                                   /* wait for TimerB timeout flag */
    Set_Bit(TIMER0_ICR_R,TBTOCINT);                                             /* clear the TimerB timeout flag */
  }
}
////////////////////////////////////////////////////////////////////////////////
void TIMER0A_ISR(void){
  TIMER0->ICR |=(1<<0);
  second++;
  if(second==60){
    second=0;
    min++;
    Sclear++;
  }
  if(Sclear==5){
    Sclear=0;
  }
  if(min==60){
    min=0;
    hour=1;
    
  }
  if(hour==24){
  hour=0;
  }
  
  
}
////////////////////////////////////////////////////////////////////////////////
void TIMER1A_ISR(void){
  TIMER1->ICR |=(1<<0);
  flag++;
  __disable_interrupt();
  (*PeriodicTask)();
  
  if (flag==500){
    __disable_interrupt();
    flag=0;
  }
}
////////////////////////////////////////////////////////////////////////////////
char getSeconds(void){
  return second;
}