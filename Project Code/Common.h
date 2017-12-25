


#define Set_Bit(Reg,bitNum) Reg=Reg|(1<<bitNum)
#define Set_Two_Bits(Reg,bitNum1,bitNum2) Reg=Reg|(1<<bitNum1)|(1<<bitNum2)
#define Set_Three_Bits(Reg,bitNum1,bitNum2,bitNum3) Reg=Reg|(1<<bitNum1)|(1<<bitNum2)|(1<<bitNum3)
#define Get_Bit(Reg,bitNum) (Reg&(1<<bitNum))>>bitNum
#define Clr_Bit(Reg,bitNum) Reg=Reg&(~(1<<bitNum))
#define GieON __asm__("SEI")
#define GieOFF __asm__("CLI")



#define BAUDRATE 9600
#define FCPU 4000000 

#define ok 1
#define error 0

