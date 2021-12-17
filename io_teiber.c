#include "simuc.h"
#include "io_treiber.h"

typedef struct BHandle_Data {
    BYTE Board_allocated;	// 1=allocated, 0=free
    BYTE Port_A_Direction;	// 1=Output, 0=Input
    BYTE Port_B_Direction;
    BYTE Port_C_Direction;
    BYTE Port_D_Direction;
} BHandle;


BHandle BoardHandle_Data;
DSCB GlobalBoardHandle = &BoardHandle_Data;



BYTE Init(DSCB BoardHandle, unsigned long int Steuerwort) {
// Mit Leben fuellen
    if(BoardHandle->Board_allocated==1)
                return 1;

    BoardHandle->Board_allocated=1;

    switch(Steuerwort){
 case 0x80:
         io_out16(DIR0,0xFFFF); io_out16(DIR1,0xFFFF);
         BoardHandle->Port_A_Direction=1;BoardHandle->Port_D_Direction=1;BoardHandle->Port_C_Direction=1;BoardHandle->Port_B_Direction=1;
         return 0;
case 0x9B:
         io_out16(DIR0,0x0000);io_out16(DIR1,0x0000);
          BoardHandle->Port_A_Direction=0;BoardHandle->Port_D_Direction=0;BoardHandle->Port_C_Direction=0;BoardHandle->Port_B_Direction=0;
         return 0;
case 0x81:
         io_out16(DIR0,0xFFFF); io_out16(DIR1,0x00FF);
          BoardHandle->Port_A_Direction=1;BoardHandle->Port_D_Direction=0;BoardHandle->Port_C_Direction=1;BoardHandle->Port_B_Direction=1;
         return 0;
case 0x88:
        io_out16(DIR0,0xFFFF); io_out16(DIR1,0xFF00);
         BoardHandle->Port_A_Direction=1;BoardHandle->Port_D_Direction=1;BoardHandle->Port_C_Direction=0;BoardHandle->Port_B_Direction=1;
        return 0;
case 0x89:
         io_out16(DIR0,0xFFFF); io_out16(DIR1,0x0000);
          BoardHandle->Port_A_Direction=1;BoardHandle->Port_D_Direction=1;BoardHandle->Port_C_Direction=1;BoardHandle->Port_B_Direction=0;
         return 0;
case 0x82:
         io_out16(DIR0,0x00FF); io_out16(DIR1,0xFFFF);
          BoardHandle->Port_A_Direction=1;BoardHandle->Port_D_Direction=1;BoardHandle->Port_C_Direction=1;BoardHandle->Port_B_Direction=0;
         return 0;
case 0x83:
         io_out16(DIR0,0x00FF); io_out16(DIR1,0x00FF);
          BoardHandle->Port_A_Direction=1;BoardHandle->Port_D_Direction=0;BoardHandle->Port_C_Direction=1;BoardHandle->Port_B_Direction=0;
         return 0;
case 0x8A :
        io_out16(DIR0,0x00FF); io_out16(DIR1,0xFF00);
         BoardHandle->Port_A_Direction=1;BoardHandle->Port_D_Direction=1;BoardHandle->Port_C_Direction=0;BoardHandle->Port_B_Direction=0;
        return 0;
case 0x8B:
        io_out16(DIR0,0x00FF); io_out16(DIR1,0x0000);
         BoardHandle->Port_A_Direction=1;BoardHandle->Port_D_Direction=0;BoardHandle->Port_C_Direction=0;BoardHandle->Port_B_Direction=0;
        return 0;
case 0x90:
        io_out16(DIR0,0xFF00); io_out16(DIR1,0xFFFF);
         BoardHandle->Port_A_Direction=0;BoardHandle->Port_D_Direction=1;BoardHandle->Port_C_Direction=1;BoardHandle->Port_B_Direction=1;
        return 0;
case 0x91:
        io_out16(DIR0,0xFF00); io_out16(DIR1,0x00FF);
         BoardHandle->Port_A_Direction=0;BoardHandle->Port_D_Direction=0;BoardHandle->Port_C_Direction=1;BoardHandle->Port_B_Direction=1;
        return 0;
case 0x98:
        io_out16(DIR0,0xFF00); io_out16(DIR1,0xFF00);
         BoardHandle->Port_A_Direction=0;BoardHandle->Port_D_Direction=1;BoardHandle->Port_C_Direction=0;BoardHandle->Port_B_Direction=0;
        return 0;
case 0x99:
       io_out16(DIR0,0xFF00); io_out16(DIR1,0x0000);
        BoardHandle->Port_A_Direction=0;BoardHandle->Port_D_Direction=0;BoardHandle->Port_C_Direction=0;BoardHandle->Port_B_Direction=1;
       return 0;
case 0x92 :
      io_out16(DIR0,0x0000); io_out16(DIR1,0xFFFF);
       BoardHandle->Port_A_Direction=0;BoardHandle->Port_D_Direction=1;BoardHandle->Port_C_Direction=1;BoardHandle->Port_B_Direction=0;
      return 0;
case 0x93:
        io_out16(DIR0,0x0000); io_out16(DIR1,0x00FF);
         BoardHandle->Port_A_Direction=0;BoardHandle->Port_D_Direction=0;BoardHandle->Port_C_Direction=1;BoardHandle->Port_B_Direction=0;
        return 0;
case 0x9A:
        io_out16(DIR0,0x0000); io_out16(DIR1,0xFF00);
         BoardHandle->Port_A_Direction=0;BoardHandle->Port_D_Direction=1;BoardHandle->Port_C_Direction=0;BoardHandle->Port_B_Direction=0;
        return 0;
default :
return -1;
    }


}
BYTE InputByte(DSCB BoardHandle, BYTE Port, BYTE *DigitalValue) {
  if(BoardHandle->Board_allocated==0)
 return 1;
 switch(Port) {
 case 3 :
    if(BoardHandle->Port_D_Direction==0){
    *DigitalValue=io_in16(IN1)>>8;
     return 0;}
    return 2;
    break;

case 1:

    if(BoardHandle->Port_B_Direction==0){
    *DigitalValue=io_in16(IN0)>>8;
    return 0;}
    else
    return 2;
    break;

case 0   :
    if(BoardHandle->Port_A_Direction==0){
    *DigitalValue=io_in16(IN0)&0x00FF;
     return 0;}
    else
    return 2;
    break;
case  2 :
   if(BoardHandle->Port_C_Direction==0){
    *DigitalValue=io_in16(IN1)&0x00FF;
   //b=io_in16(IN1)&0xFF;
    return 0;}
    else
    return 2;

    default :
    return 1;
}
}
BYTE OutputByte(DSCB BoardHandle, BYTE Port, BYTE DigitalValue) {

      /*    byte rem;
          byte temp=1;
          byte binary=0;
         while(DigitalValue!=0){
          rem=DigitalValue%2;
      DigitalValue=DigitalValue/2;
      binary=binary+rem*temp;
      temp=temp*10;
      }*/
    unsigned short out1;
  unsigned short  out2;
if(BoardHandle->Board_allocated==0)
    return 1;
switch(Port){
case 3:
if(BoardHandle->Port_D_Direction==1){
 out1=(io_in16(IN1));
 out1=out1& 0x00FF;//die Bits des Ports C behalten und der Port D auf 0 setzen
 out2=(DigitalValue<<8); // binary um 8 Stellen nach Links verschieben und mit den Output verodern ergibt in port C die binäre Wert der Digitalvalue und Port D bleibt unverändert
io_out16(OUT1,out2|out1);
return 0;
}
else {
return 3;
}
case 1:
if(BoardHandle->Port_B_Direction==1){
 out1=(io_in16(OUT0)|0x00FF);//die Bits des Ports A behalten und der Port B auf 0 setzen
 out2=((DigitalValue<<8)|out1);// binary um 8 Stellen nach Links verschieben und mit den Output verodern ergibt in port A die binäre Wert der Digitalvalue und Port Bbleibt unverändert
io_out16(OUT0,out2);
return 0;
}
else {
return 3;
}
case 2:
if(BoardHandle->Port_C_Direction==1){
 out1=(io_in16(OUT1)&0xFF00); //die Bits des Ports D behalten und der Port C auf 0 setzen
 out2=(DigitalValue | out1 );                 // binary mit den Output verodern ergibt in port C die binäre Wert der Digitalvalue und Port D bleibt unverändert
io_out16(OUT1,out2);
return 0;
}
else{
return 3;
}
case 0:
if(BoardHandle->Port_A_Direction==1){
 out1=(io_in16(OUT0)& 0xFF00); //die Bits des Ports B behalten und der Port A auf 0 setzen
 out2=(DigitalValue | out1 );                 // binary mit den Output verodern ergibt in port A die binäre Wert der Digitalvalue und Port B bleibt unverändert
io_out16(OUT0,out2);
return 0;
}
else{
return 3;
}

 default :
   return 2;

}
}



BYTE Free(DSCB BoardHandle) {

        if(BoardHandle->Board_allocated==1){
        BoardHandle->Board_allocated=0;
    return 0;}
    else
    return 1;
}
