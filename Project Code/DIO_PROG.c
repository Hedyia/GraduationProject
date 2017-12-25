#include "lm4f120h5qr.h"
#include "DIO_CONFIG.h"
#include "DIO_INTERFACING.h"
#include "Common.h"

////////////////////////////////////////////////////////////////////////////////

void DIO_INIT(void){
 
}
////////////////////////////////////////////////////////////////////////////////
char DIO_WritePinDir(char PIN_NUM,char Val){
  char Pin_Location=PIN_NUM/8;
  char Pin_Index=PIN_NUM%8;
  char check = ok;
  
  Set_Bit(SYSCTL_RCGCGPIO_R,Pin_Location);
  
  if(Val==OutPut){
    switch(Pin_Location){
    case 0:Set_Bit(GPIO_PORTA_DEN_R,Pin_Index);
           Clr_Bit(GPIO_PORTA_AFSEL_R,Pin_Index);
           Set_Bit(GPIO_PORTA_DIR_R,Pin_Index);
      break;
    case 1:Set_Bit(GPIO_PORTB_DEN_R,Pin_Index);
           Clr_Bit(GPIO_PORTB_AFSEL_R,Pin_Index);
           Set_Bit(GPIO_PORTB_DIR_R,Pin_Index);
      break;
    case 2:Set_Bit(GPIO_PORTC_DEN_R,Pin_Index);
           Clr_Bit(GPIO_PORTC_AFSEL_R,Pin_Index);
           Set_Bit(GPIO_PORTC_DIR_R,Pin_Index);
           GPIO_PORTC_LOCK_R=UN_LOCK;
           GPIO_PORTC_CR_R=CR_VALUE;
      break;
    case 3:Set_Bit(GPIO_PORTD_DEN_R,Pin_Index);
           Clr_Bit(GPIO_PORTD_AFSEL_R,Pin_Index);
           Set_Bit(GPIO_PORTD_DIR_R,Pin_Index);
      break;
    case 4:Set_Bit(GPIO_PORTE_DEN_R,Pin_Index);
           Clr_Bit(GPIO_PORTE_AFSEL_R,Pin_Index);
           Set_Bit(GPIO_PORTE_DIR_R,Pin_Index);
      break;
    case 5:Set_Bit(GPIO_PORTF_DEN_R,Pin_Index);
           Clr_Bit(GPIO_PORTF_AFSEL_R,Pin_Index);
           Set_Bit(GPIO_PORTF_DIR_R,Pin_Index);
      break;
    default:check=error;
      break;
    }
  }else if(Val==InPut){
    switch(Pin_Location){
      case 0:Set_Bit(GPIO_PORTA_DEN_R,Pin_Index);
             Clr_Bit(GPIO_PORTA_AFSEL_R,Pin_Index);
             GPIO_PORTA_LOCK_R=UN_LOCK;
             GPIO_PORTA_CR_R=CR_VALUE;
             Set_Bit(GPIO_PORTA_PUR_R,Pin_Index);
             Clr_Bit(GPIO_PORTA_DIR_R,Pin_Index);
        break;
      case 1:Set_Bit(GPIO_PORTB_DEN_R,Pin_Index);
             Clr_Bit(GPIO_PORTB_AFSEL_R,Pin_Index);
             GPIO_PORTB_LOCK_R=UN_LOCK;
             GPIO_PORTB_CR_R=CR_VALUE;
             Set_Bit(GPIO_PORTB_PUR_R,Pin_Index);
             Clr_Bit(GPIO_PORTB_DIR_R,Pin_Index);
        break;
      case 2:Set_Bit(GPIO_PORTC_DEN_R,Pin_Index);
             Clr_Bit(GPIO_PORTC_AFSEL_R,Pin_Index);
             GPIO_PORTC_LOCK_R=UN_LOCK;
             GPIO_PORTC_CR_R=CR_VALUE;
             Set_Bit(GPIO_PORTC_PUR_R,Pin_Index);
             Clr_Bit(GPIO_PORTC_DIR_R,Pin_Index);
        break;
      case 3:Set_Bit(GPIO_PORTD_DEN_R,Pin_Index);
             Clr_Bit(GPIO_PORTD_AFSEL_R,Pin_Index); 
             GPIO_PORTD_LOCK_R=UN_LOCK;
             GPIO_PORTD_CR_R=CR_VALUE;
             Set_Bit(GPIO_PORTD_PUR_R,Pin_Index);
             Clr_Bit(GPIO_PORTD_DIR_R,Pin_Index);
        break;
      case 4:Set_Bit(GPIO_PORTE_DEN_R,Pin_Index);
             Clr_Bit(GPIO_PORTE_AFSEL_R,Pin_Index);
             GPIO_PORTE_LOCK_R=UN_LOCK;
             GPIO_PORTE_CR_R=CR_VALUE;
             Set_Bit(GPIO_PORTE_PUR_R,Pin_Index);
             Clr_Bit(GPIO_PORTE_DIR_R,Pin_Index);
        break;
      case 5:Set_Bit(GPIO_PORTF_DEN_R,Pin_Index);
             Clr_Bit(GPIO_PORTF_AFSEL_R,Pin_Index);
             GPIO_PORTF_LOCK_R=UN_LOCK;
             GPIO_PORTF_CR_R=CR_VALUE;
             Set_Bit(GPIO_PORTF_PUR_R,Pin_Index);
             Clr_Bit(GPIO_PORTF_DIR_R,Pin_Index);
        break;
      default:check=error;
        break;
    }
  }else{
    check=error;
  }
  return check;
  
}
////////////////////////////////////////////////////////////////////////////////
char DIO_WritePinVal(char PIN_NUM,char Val){
  char Pin_Location=PIN_NUM/8;
  char Pin_Index=PIN_NUM%8;
  char check = ok;
  
  if(Val==HIGH){
    switch(Pin_Location){
    case 0:Set_Bit(GPIO_PORTA_DATA_R,Pin_Index);
      break;
    case 1:Set_Bit(GPIO_PORTB_DATA_R,Pin_Index);
      break;
    case 2:Set_Bit(GPIO_PORTC_DATA_R,Pin_Index);
      break;
    case 3:Set_Bit(GPIO_PORTD_DATA_R,Pin_Index);
      break;
    case 4:Set_Bit(GPIO_PORTE_DATA_R,Pin_Index);
      break;
    case 5:Set_Bit(GPIO_PORTF_DATA_R,Pin_Index);
      break;
    default:check=error;
      break;
    }
  }else if(Val==LOW){
    switch(Pin_Location){
      case 0:Clr_Bit(GPIO_PORTA_DATA_R,Pin_Index);
        break;
      case 1:Clr_Bit(GPIO_PORTB_DATA_R,Pin_Index);
        break;
      case 2:Clr_Bit(GPIO_PORTC_DATA_R,Pin_Index);
        break;
      case 3:Clr_Bit(GPIO_PORTD_DATA_R,Pin_Index);
        break;
      case 4:Clr_Bit(GPIO_PORTE_DATA_R,Pin_Index);
        break;
      case 5:Clr_Bit(GPIO_PORTF_DATA_R,Pin_Index);
        break;
      default:check=error;
        break;
    }
  }else{
    check=error;
  }
  return check;
  
}
////////////////////////////////////////////////////////////////////////////////
char DIO_ReadPinVal(char PIN_NUM,int *Val){
  char Pin_Location=PIN_NUM/8;
  char Pin_Index=PIN_NUM%8;
  char check = ok;
  
  switch(Pin_Location){
    case 0:*Val=Get_Bit(GPIO_PORTA_DATA_R,Pin_Index);
      break;
    case 1:*Val=Get_Bit(GPIO_PORTB_DATA_R,Pin_Index);
      break;
    case 2:*Val=Get_Bit(GPIO_PORTC_DATA_R,Pin_Index);
      break;
    case 3:*Val=Get_Bit(GPIO_PORTD_DATA_R,Pin_Index);
      break;
    case 4:*Val=Get_Bit(GPIO_PORTE_DATA_R,Pin_Index);
      break;
    case 5:*Val=Get_Bit(GPIO_PORTF_DATA_R,Pin_Index);
      break;
    default:check=error;
      break;
    }
  if(check==ok){
		return *Val;
	}else{
		return check;
	}
  
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
char DIO_WritePortDir(char PORT_NUM,char Val){
  char check = ok;
  
  if(Val==OutPut){
    switch (PORT_NUM){
      case 0:GPIO_PORTA_DEN_R=PORT_DEN;
             GPIO_PORTA_AFSEL_R=PORT_AFSEL;
             GPIO_PORTA_DIR_R=PORT_DIR_OUT;
      break;
      case 1:GPIO_PORTB_DEN_R=PORT_DEN;
             GPIO_PORTB_AFSEL_R=PORT_AFSEL;
             GPIO_PORTB_DIR_R=PORT_DIR_OUT;
      break;
      case 2:GPIO_PORTC_DEN_R=PORT_DEN;
             GPIO_PORTC_AFSEL_R=PORT_AFSEL;
             GPIO_PORTC_DIR_R=PORT_DIR_OUT;
      break;
      case 3:GPIO_PORTD_DEN_R=PORT_DEN;
             GPIO_PORTD_AFSEL_R=PORT_AFSEL;
             GPIO_PORTD_DIR_R=PORT_DIR_OUT;
      break;
      case 4:GPIO_PORTE_DEN_R=PORT_DEN;
             GPIO_PORTE_AFSEL_R=PORT_AFSEL;
             GPIO_PORTE_DIR_R=PORT_DIR_OUT;
      break;
      case 5:GPIO_PORTF_DEN_R=PORT_DEN;
             GPIO_PORTF_AFSEL_R=PORT_AFSEL;
             GPIO_PORTF_DIR_R=PORT_DIR_OUT;
      break;
    default:check=error;
      break;
    }
  }else if (Val==InPut){
     switch (PORT_NUM){
      case 0:GPIO_PORTA_DEN_R=PORT_DEN;
             GPIO_PORTA_AFSEL_R=PORT_AFSEL;
             GPIO_PORTA_LOCK_R=UN_LOCK;
             GPIO_PORTA_CR_R=CR_VALUE;
             GPIO_PORTA_PDR_R=PORT_PUR;
             GPIO_PORTA_DIR_R=PORT_DIR_IN;
      break;
      case 1:GPIO_PORTB_DEN_R=PORT_DEN;
             GPIO_PORTB_AFSEL_R=PORT_AFSEL;
             GPIO_PORTB_LOCK_R=UN_LOCK;
             GPIO_PORTB_CR_R=CR_VALUE;
             GPIO_PORTB_PDR_R=PORT_PUR;
             GPIO_PORTB_DIR_R=PORT_DIR_IN;
      break;
      case 2:GPIO_PORTC_DEN_R=PORT_DEN;
             GPIO_PORTC_AFSEL_R=PORT_AFSEL;
             GPIO_PORTC_LOCK_R=UN_LOCK;
             GPIO_PORTC_CR_R=CR_VALUE;
             GPIO_PORTC_PDR_R=PORT_PUR;
             GPIO_PORTC_DIR_R=PORT_DIR_IN;
      break;
      case 3:GPIO_PORTD_DEN_R=PORT_DEN;
             GPIO_PORTD_AFSEL_R=PORT_AFSEL;
             GPIO_PORTD_LOCK_R=UN_LOCK;
             GPIO_PORTD_CR_R=CR_VALUE;
             GPIO_PORTD_PDR_R=PORT_PUR;
             GPIO_PORTD_DIR_R=PORT_DIR_IN;
      break;
      case 4:GPIO_PORTE_DEN_R=PORT_DEN;
             GPIO_PORTE_AFSEL_R=PORT_AFSEL;
             GPIO_PORTE_LOCK_R=UN_LOCK;
             GPIO_PORTE_CR_R=CR_VALUE;
             GPIO_PORTE_PDR_R=PORT_PUR;
             GPIO_PORTE_DIR_R=PORT_DIR_IN;
      break;
      case 5:GPIO_PORTF_DEN_R=PORT_DEN;
             GPIO_PORTF_AFSEL_R=PORT_AFSEL;
             GPIO_PORTF_LOCK_R=UN_LOCK;
             GPIO_PORTF_CR_R=CR_VALUE;
             GPIO_PORTF_PDR_R=PORT_PUR;
             GPIO_PORTF_DIR_R=PORT_DIR_IN;
      break;
    default:check=error;
      break;
    }
    }else{
    check=error;
    }
  return error;
  }
  
////////////////////////////////////////////////////////////////////////////////
char DIO_WritePortVal(char PORT_NUM , char Val) {
  char check = ok;
  
  switch (PORT_NUM){
    case 0:GPIO_PORTA_DATA_R=Val;
      break;
    case 1:GPIO_PORTB_DATA_R=Val;
      break;
    case 2:GPIO_PORTC_DATA_R=Val;
      break;
    case 3:GPIO_PORTD_DATA_R=Val;
      break;
    case 4:GPIO_PORTE_DATA_R=Val;
      break;
    case 5:GPIO_PORTF_DATA_R=Val;
      break;
    default:check=error;
      break;
  }
  return check;
}

////////////////////////////////////////////////////////////////////////////////
char DIO_ReadPortVal(char PORT_NUM,char *Val){
  char check=ok;
  
  switch (PORT_NUM){
    case 0:*Val=GPIO_PORTA_DATA_R;
      break;
    case 1:*Val=GPIO_PORTB_DATA_R;
      break;
    case 2:*Val=GPIO_PORTC_DATA_R;
      break;
    case 3:*Val=GPIO_PORTD_DATA_R;
      break;
    case 4:*Val=GPIO_PORTE_DATA_R;
      break;
    case 5:*Val=GPIO_PORTF_DATA_R;
      break;
    default:check=error;
      break;
  }
  if(check==ok){
	return *Val;
  }else{
	return check;
  }
	
}