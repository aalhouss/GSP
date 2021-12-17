
#include "simuc.h"
#include "io_treiber.h"
/*Diese hier zur Testierung vorgelegte Lösung wurde durch folgendes Team
erarbeitet:
Studierender 1: Ahmad Al Housseini,11145964
Studierender 2: FATima ALkhattabi, 11145655
wenn die Lösung nicht im Team erarbeitet wurde)
Jeder der oben genannten Studierenden erklärt hiermit folgendes:
- Die abgegebene Ausarbeitung habe ich (Name des Studierenden) zusammen
 mit dem oben genannten Teampartner eigenständig auf Basis der von der
 TH-Köln bereitgestellten Vorlagen (Softwarerahmen) erarbeitet.
- Ich bin in der Lage diese meine Ausarbeitung auf Nachfrage eigenständig zu
 erläutern und notwendige Änderungen, die sich auf Basis einer leicht geänderten
 Aufgabenstellung ergeben zu skizzieren.

 * */
// Die Verwendung der folgenden Zustandsnamen ist verbindlich
typedef enum{Steht,StarteRunter,StarteRauf,Notaus,FahreRauf_MIT_OF,FahreRauf_OHNE_OF,FahreRunter_MIT_OF,FahreRunter_OHNE_OF} state_t;

// Die folgenden Defines muessen sinnvoll genutzt werden
#define BIT_T2		5
#define BIT_T1		4
#define BIT_ESR		3
#define BIT_ESL		2

#define BIT_M_Re	2
#define BIT_M_Li	1
#define BIT_M_An	0

static long int startpos;
static long int endpos;
static long int aktpos;

// Hier die Steuerungsfunktion definieren
// ...
void stgfunc (unsigned short int ESL, unsigned short int ESR, unsigned short int T1, unsigned short int T2,
unsigned short int* M_Re,unsigned short int *M_Li,unsigned short int* M_An, state_t* pstate,long int aktpos ) {
    switch (*pstate) {

    case Steht:
        *M_Li = 0;
        *M_An=0;
        *M_Re=0;
        if(T1==1)
       {
           *pstate=Notaus;
       }
       else if(ESR==1){
           *pstate=StarteRauf;
        }
        else if(ESL==1){
            *pstate=StarteRunter;
        }

        break;
    case StarteRauf:
        *M_Li=1;*M_Re=0;*M_An=1;
        startpos=aktpos;
        endpos = (startpos - 60000) % 65535;
        if(endpos<0)
        {
         endpos=endpos+65535;
        }
         if(T1==1)
        {
            *pstate=Notaus;
                }
       else  if(startpos < endpos) {
            *pstate=FahreRauf_MIT_OF;
        }
       else  if(startpos >= endpos){
            *pstate=FahreRauf_OHNE_OF;

        }
        break;
    case StarteRunter:
        *M_Li=0;*M_Re=1;*M_An=1;
        startpos=aktpos;
        endpos = (startpos + 60000) % 65535;
        if(T1==1){
         *pstate=Notaus;
        }
       else if(startpos > endpos){
            *pstate=FahreRunter_MIT_OF;
        }
       else if(startpos <= endpos){
            *pstate=FahreRunter_OHNE_OF;
        }
        break;
    case FahreRunter_OHNE_OF:
        *M_Li=0;*M_Re=1;*M_An=1;
        if(ESL==1){
            *pstate=StarteRunter;
        }
        if(T1==1){
        *pstate=Notaus;
       }
       else if((aktpos > endpos) || (aktpos < startpos)){
            *pstate=Steht;
        }

        break;
    case FahreRunter_MIT_OF:
        *M_Li=0;*M_Re=1;*M_An=1;
        if((aktpos > endpos) && (aktpos < startpos)){
            *pstate=Steht;
        }
        if(T1==1){
        *pstate=Notaus;
       }
       else if(ESL==1){
            *pstate=StarteRunter;
        }


        break;
    case FahreRauf_MIT_OF:
        if(T1==1){
        *pstate=Notaus;
       }
         else if(ESR==1){
              *pstate=StarteRauf;
          }
       else if((aktpos < endpos) && (aktpos > startpos)){
            *pstate=Steht;
        }


        break;
    case FahreRauf_OHNE_OF:
        *M_Li=1;*M_Re=0;*M_An=1;
        if(T1==1){
         *pstate=Notaus;
        }
        else if(ESR==1){
            *pstate=StarteRauf;
    }
       else  if((aktpos < endpos) || (aktpos > startpos)){
            *pstate=Steht;
        }
        break;
    case Notaus:
        *M_Re=0; *M_Li=0;*M_An=0;
        if(T2){
            *pstate=Steht;
        }
        break;
    default: *pstate=Steht;
}
}

void emain(void* arg)
{
  // 2) Definition des Startzustandes
    state_t pstate;
        // Hier alle benoetigten Variablen deklarieren
        // ...
    unsigned short int ESL; unsigned short int ESR; unsigned short int T1; unsigned short int T2;

    //Variable für die Ausgabesignale (Aufgabe 2)
    unsigned short int M_Re;unsigned short int M_Li;unsigned short int M_An;
    BYTE output;
    BYTE test1,test2,test3,test4,test5,test6,x;
      test5=15;

        INIT_BM_WITH_REGISTER_UI; // Hier unbedingt einen Break-Point setzen !!!


        // Hier die Treiberfunktionen aufrufen und testen (Aufgabe 1)
    // ...
    test1=Init(GlobalBoardHandle, 0x9A);
    test2=InputByte(GlobalBoardHandle,2,&test4);
    test3=OutputByte(GlobalBoardHandle,3,test5);
    test6=Free(GlobalBoardHandle);


    pstate=Steht;
    Init(GlobalBoardHandle,0x9A );// Port D als Ausgang und Port A,B,C als Eingänge

        // Ab hier beginnt die Endlosschleife fuer den Automaten (Aufgabe 2)
        while(1) {

    //    Hier alle benoetigten Variablen deklarieren
               // Variable fuer Aufgabe 1


             SYNC_SIM;


               // Hier die Treiberfunktionen aufrufen und testen (Aufgabe 1)
           // ...
           //test1=Init(GlobalBoardHandle, 0x80);
          // test2=InputByte(GlobalBoardHandle,1,33);
          //) test3=OutputByte(GlobalBoardHandle,1, 22);




              // 1) Hardware konfigurieren
           //Free(GlobalBoardHandle);





              //3)Unendliche Schleife
          // Ab hier beginnt die Endlosschleife fuer den Automaten (Aufgabe 2)


 InputByte(GlobalBoardHandle,PC,&x);
                       // Hier die Eingabesignale einlesen


ESL=(x>>BIT_ESL)&0x01;
ESR=(x>>BIT_ESR)&0x01;
T1=(x>>BIT_T1)&0x01;
T2=(x>>BIT_T2)&0x01;

InputByte(GlobalBoardHandle,PA,&x);
BYTE a=x;
InputByte(GlobalBoardHandle,PB,&x);
BYTE b=x;
aktpos=(b<<8)|a;


                       // Hier die Steuerungsfunktion aufrufen
                  stgfunc(ESL,ESR,T1,T2,&M_Re,&M_Li,&M_An,&pstate,aktpos );

                    // Hier die Ausgabesignale ausgeben

                    output=output&~((1<<BIT_M_An)|(1<<BIT_M_Li)|(1<<BIT_M_Re));
                    output=output|((M_Re)<<BIT_M_Re)|((M_Li)<<BIT_M_Li)|((M_An)<<BIT_M_An);

                    OutputByte(GlobalBoardHandle,PD,output);

               }


       }

