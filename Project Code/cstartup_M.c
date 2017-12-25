/**************************************************
 *
 * This file contains an interrupt vector for Cortex-M written in C.
 * The actual interrupt functions must be provided by the application developer.
 *
 * Copyright 2007 IAR Systems. All rights reserved.
 *
 * $Revision: 66254 $
 *
 **************************************************/

#pragma language=extended
#pragma segment="CSTACK"

extern void __iar_program_start( void );

extern void NMI_Handler( void );
extern void HardFault_Handler( void );
extern void MemManage_Handler( void );
extern void BusFault_Handler( void );
extern void UsageFault_Handler( void );
extern void SVC_Handler( void );
extern void DebugMon_Handler( void );
extern void PendSV_Handler( void );
extern void SysTick_Handler( void );
void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);
static void UsageFaultISR(void);
 
void TIMER1A_ISR(void);
void TIMER0A_ISR(void);

void UART0_ISR(void);
void UART1_ISR(void);
void UART2_ISR(void);
void UART3_ISR(void);
void UART4_ISR(void);
void UART5_ISR(void);
void UART6_ISR(void);
void UART7_ISR(void);

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

// The vector table is normally located at address 0.
// When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
// If you need to define interrupt service routines,
// make a copy of this file and include it in your project.
// The name "__vector_table" has special meaning for C-SPY, which
// is where to find the SP start value.
// If vector table is not located at address 0, the user has to initialize
// the  NVIC vector table register (VTOR) before using interrupts.


#pragma location = ".intvec"
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,

  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  0,
  0,
  0,
  0,
  SVC_Handler,
  DebugMon_Handler,
  0,
  PendSV_Handler,
  SysTick_Handler,
    0,                      // GPIO Port A
    0,                      // GPIO Port B
    0,                      // GPIO Port C
    0,                      // GPIO Port D
    0,                      // GPIO Port E
    UART0_ISR,                      // UART0 Rx and Tx
    UART1_ISR,                      // UART1 Rx and Tx
    0,                      // SSI0 Rx and Tx
    0,                      // I2C0 Master and Slave
    0,                      // PWM Fault
    0,                      // PWM Generator 0
    0,                      // PWM Generator 1
    0,                      // PWM Generator 2
    0,                      // Quadrature Encoder 0
    0,                      // ADC Sequence 0
    0,                      // ADC Sequence 1
    0,                      // ADC Sequence 2
    0,                      // ADC Sequence 3
    0,                      // Watchdog timer
    TIMER0A_ISR,                      // Timer 0 subtimer A
    0,                      // Timer 0 subtimer B
    TIMER1A_ISR,                      // Timer 1 subtimer A
    0,                      // Timer 1 subtimer B
    0,                      // Timer 2 subtimer A
    0,                      // Timer 2 subtimer B
    0,                      // Analog Comparator 0
    0,                      // Analog Comparator 1
    0,                      // Analog Comparator 2
    0,                      // System Control (PLL, OSC, BO)
    0,                      // FLASH Control
    0,                      // GPIO Port F
    0,                      // GPIO Port G
    0,                      // GPIO Port H
    UART2_ISR,                      // UART2 Rx and Tx
    0,                      // SSI1 Rx and Tx
    0,                      // Timer 3 subtimer A
    0,                      // Timer 3 subtimer B
    0,                      // I2C1 Master and Slave
    0,                      // Quadrature Encoder 1
    0,                      // CAN0
    0,                      // CAN1
    0,                                      // Reserved
    0,                                      // Reserved
    0,                      // Hibernate
    0,                      // USB0
    0,                      // PWM Generator 3
    0,                      // uDMA Software Transfer
    0,                      // uDMA Error
    0,                      // ADC1 Sequence 0
    0,                      // ADC1 Sequence 1
    0,                      // ADC1 Sequence 2
    0,                      // ADC1 Sequence 3
    0,                                      // Reserved
    0,                                      // Reserved
    0,                      // GPIO Port J
    0,                      // GPIO Port K
    0,                      // GPIO Port L
    0,                      // SSI2 Rx and Tx
    0,                      // SSI3 Rx and Tx
    UART3_ISR,                      // UART3 Rx and Tx
    UART4_ISR,                      // UART4 Rx and Tx
    UART5_ISR,                      // UART5 Rx and Tx
    UART6_ISR,                      // UART6 Rx and Tx
    UART7_ISR,                      // UART7 Rx and Tx
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                      // I2C2 Master and Slave
    0,                      // I2C3 Master and Slave
    0,                      // Timer 4 subtimer A
    0,                      // Timer 4 subtimer B
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                      // Timer 5 subtimer A
    0,                      // Timer 5 subtimer B
    0,                      // Wide Timer 0 subtimer A
    0,                      // Wide Timer 0 subtimer B
    0,                      // Wide Timer 1 subtimer A
    0,                      // Wide Timer 1 subtimer B
    0,                      // Wide Timer 2 subtimer A
    0,                      // Wide Timer 2 subtimer B
    0,                      // Wide Timer 3 subtimer A
    0,                      // Wide Timer 3 subtimer B
    0,                      // Wide Timer 4 subtimer A
    0,                      // Wide Timer 4 subtimer B
    0,                      // Wide Timer 5 subtimer A
    0,                      // Wide Timer 5 subtimer B
    0,                      // FPU
    0,                                      // Reserved
    0,                                      // Reserved
    0,                      // I2C4 Master and Slave
    0,                      // I2C5 Master and Slave
    0,                      // GPIO Port M
    0,                      // GPIO Port N
    0,                      // Quadrature Encoder 2
    0,                                      // Reserved
    0,                                      // Reserved
    0,                      // GPIO Port P (Summary or P0)
    0,                      // GPIO Port P1
    0,                      // GPIO Port P2
    0,                      // GPIO Port P3
    0,                      // GPIO Port P4
    0,                      // GPIO Port P5
    0,                      // GPIO Port P6
    0,                      // GPIO Port P7
    0,                      // GPIO Port Q (Summary or Q0)
    0,                      // GPIO Port Q1
    0,                      // GPIO Port Q2
    0,                      // GPIO Port Q3
    0,                      // GPIO Port Q4
    0,                      // GPIO Port Q5
    0,                      // GPIO Port Q6
    0,                      // GPIO Port Q7
    0,                      // GPIO Port R
    0,                      // GPIO Port S
    0,                      // PWM 1 Generator 0
    0,                      // PWM 1 Generator 1
    0,                      // PWM 1 Generator 2
    0,                      // PWM 1 Generator 3
    0                       // PWM 1 Fault
 

};

#pragma call_graph_root = "interrupt"
__weak void NMI_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void HardFault_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void MemManage_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void BusFault_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void UsageFault_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void SVC_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void DebugMon_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void PendSV_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void SysTick_Handler( void ) { while (1) {} }


void __cmain( void );
__weak void __iar_init_core( void );
__weak void __iar_init_vfp( void );

#pragma required=__vector_table
void __iar_program_start( void )
{
  __iar_init_core();
  __iar_init_vfp();
  __cmain();
}
