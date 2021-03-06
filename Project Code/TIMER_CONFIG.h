#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

////////////////////////////////////////////////////////////////////////////////
//////////PROTOTYPES////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void TIMER0_B_INIT(void);
void TIMER0_A_INIT(void);
void TIMER1_A_INIT (void(*task)(void));                      
void TIMER0_Delay_Ms(long MS);
char getSeconds(void);




////////////////////////////////////////////////////////////////////////////////
//////////CONFIGRATIONS/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define GPTMCFG_VALUE 0x00000000
#define PERIODIC_MODE 0x02
#define TAILR_VALUE 0x00f42400

#define enable 1
#define disable 0
#define CFG_VALUE 0x04

#define TFCPUm 16000
#define TFCPUs 16000000
#define GPT_PRESCLER 1024

#endif // TIMER_CONFIG_H_