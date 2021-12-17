#include "simuc.h"

///////////////////////////////////////////////////////////////////////////////////////
// Bedingte Compilierung
// Es darf immer nur ein "define" aktive, d.h. nicht auskommentiert, sein.
//
//#define V3_Aufgabe_1
#define V3_Aufgabe_2_und_3
//#define nachrichtenempfang_ueber_ports
//#define timer_als_taktsignalgenerator
//
///////////////////////////////////////////////////////////////////////////////////////

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


 #ifdef V3_Aufgabe_1

/*
    ES GELTEN DIE BEI "rollosteuerung_moore" AN GLEICHER STELLE VORANGESTELLTEN KOMMENTARE
*/

// Einige Defines zum leichteren Wiederfinden
#define BIT_POS_IST_OBEN	0
#define BIT_POS_IST_UNTEN	1
#define BIT_POS_NACH_OBEN	4
#define BIT_POS_NACH_UNTEN	5
#define BIT_POS_FAHRE_NACH_OBEN	9
#define BIT_POS_MOTOR_AN	8
#define BIT_POS_FAHRE_NACH_UNTEN	10
#define ZT_MAXW	2	//20
#define SS_MAXW	6	//60
#define MM_MAXW	6	//60
#define HH_MAXW	3	//24
typedef enum {hoch, runter, steht} STATE;	// Datentyp für den Zustand das Automaten.
                                            // Vergleichbar mit "TYPE .... IS" in VHDL.
typedef unsigned short int USHORT;			// Eigener Datentyp zur Abkuerzung
typedef struct {
    unsigned char hh;
    unsigned char mm;
    unsigned char ss;
} uhrzeit;
uhrzeit akt_zeit;
uhrzeit hoch_zeit;
uhrzeit runter_zeit;
unsigned char zt=0;





void steuerungsfunktion    (	USHORT ist_oben, USHORT ist_unten,
                                                USHORT nach_oben, USHORT nach_unten,
                                                USHORT nach_oben_wegen_Zeit,
                                                USHORT nach_unten_wegen_Zeit,
                        USHORT* p_fahre_nach_oben,
                        USHORT* p_fahre_nach_unten,
                        STATE* p_state	)
{

    // 5.)	switch-case-Konstrukt zur "Verwaltung" der Zustaende
    switch (*p_state) {
  //unsigned short akt_zeit;

        // 6.)	Ein CASE je Zustand
        case steht:

            // 7a.)  .... Ausgabesignale bestimmen
            *p_fahre_nach_unten=0; *p_fahre_nach_oben=0;

            // 8.)    Eingabesignale auswerten und Zustandswechsel herbei fuehren
            //         Ein IF je Pfeil
            if (  (ist_unten == 0) && (nach_unten == 1) && (nach_oben == 0)) {
                *p_state = runter; // Wechsel in den Zustand "runter"
            }
            if (  (ist_oben == 0) && (nach_oben == 1) ){
                *p_state = hoch;  // Wechsel in den Zustand "hoch"
            }

            // Diese if-Anweisung kann entfallen, da sie cstate nicht veraendert.
            if ( !(    ((ist_unten == 0) && (nach_unten == 1) && (nach_oben == 0))
                    || ((ist_oben == 0) && (nach_oben == 1)) )      ) {
                *p_state = steht; // Bleibe im Zustand "steht"
            }
                        if(nach_oben_wegen_Zeit!=0)
                            *p_state=hoch;
                        if(nach_unten_wegen_Zeit!=0)
                            *p_state=runter;
                        if( (akt_zeit.hh==hoch_zeit.hh) && (akt_zeit.mm==hoch_zeit.mm)&&(akt_zeit.ss==hoch_zeit.ss))
                            *p_state=hoch;
                        if( (akt_zeit.hh==runter_zeit.hh) && (akt_zeit.mm==runter_zeit.mm)&&(akt_zeit.ss==runter_zeit.ss))
                            *p_state=runter;
            break;

        case runter:

            // 7a.)  Ausgabesignale bestimmen
            *p_fahre_nach_unten=1; *p_fahre_nach_oben=0;


            // 8.)    Eingabesignale auswerten und Zustandswechsel herbei fuehren
            if (ist_unten == 1) {
                *p_state = steht; // Wechsel in den Zustand "steht"
            }
            if( (akt_zeit.hh==hoch_zeit.hh) && (akt_zeit.mm==hoch_zeit.mm)&&(akt_zeit.ss==hoch_zeit.ss))
                *p_state=hoch;
            // Diese if-Anweisung kann entfallen, da sie cstate nicht veraendert.
            if (ist_unten == 0) {
                *p_state = runter; // Bleibe im Zustand "runter"
            }
                      /*  if(nach_oben_wegen_Zeit!=0)
                            *p_state=hoch;
                        if(nach_unten_wegen_Zeit!=0)
                            *p_state=runter;
                        if( (akt_zeit.hh==hoch_zeit.hh) && (akt_zeit.mm==hoch_zeit.mm)&&(akt_zeit.ss==hoch_zeit.ss))
                            *p_state=hoch;
                        if( (akt_zeit.hh==runter_zeit.hh) && (akt_zeit.mm==runter_zeit.mm)&&(akt_zeit.ss==runter_zeit.ss))
                            *p_state=runter;*/

            break;

        case hoch:

            // 7a.)  Ausgabesignale bestimmen
            *p_fahre_nach_unten=0; *p_fahre_nach_oben=1;

            // 8.)    Eingabesignale auswerten und Zustandswechsel herbei fuehren
            if (ist_oben == 1){
                *p_state = steht; // Wechsel in den Zustand "steht"
            }

            // Diese if-Anweisung kann entfallen, da sie cstate nicht veraendert.
            if (ist_oben == 0){
                *p_state = hoch; // Bleibe im Zustand "hoch"
            }

                       /* if(nach_oben_wegen_Zeit!=0)
                            *p_state=hoch;
                        if(nach_unten_wegen_Zeit!=0)
                            *p_state=runter;
                        if( (akt_zeit.hh==hoch_zeit.hh) && (akt_zeit.mm==hoch_zeit.mm)&&(akt_zeit.ss==hoch_zeit.ss))
                            *p_state=hoch;
                        if( (akt_zeit.hh==runter_zeit.hh) && (akt_zeit.mm==runter_zeit.mm)&&(akt_zeit.ss==runter_zeit.ss))
                            *p_state=runter;*/
                         break;

        // 9.) nicht erlaubte Zustaende "abfangen"
        default:
            *p_state = runter;

    } // end switch
} // end steuerungsfunktion()
void timer1_oco1_isr()
{
    unsigned char stringbuf[100];
    unsigned short int buf;

    zt++;

    if(zt==ZT_MAXW){
        zt=0;
        akt_zeit.ss++;
    }

    if(akt_zeit.ss==SS_MAXW){
        akt_zeit.ss=0;
        akt_zeit.mm++;
    }

    if(akt_zeit.mm==MM_MAXW){
        akt_zeit.mm=0;
        akt_zeit.hh++;
    }
    if(akt_zeit.hh==HH_MAXW){
        akt_zeit.hh=0;
    }

    sprintf(stringbuf,"zt=%d  Uhrzeit: %d:%d:%d\n",zt,akt_zeit.hh,akt_zeit.mm,akt_zeit.ss);
    // Achtung die Verwendung von putstring() kann in der Simulationsumgebung
    // zu einem Deadlock fuehren, d.h. alles bleibt einfach stehen.
    // Dahr ist dies hier (zur Sicherheit) auskommentiert.
    // putstring(stringbuf);

    // Zuruecksetzen des Interrupt-Flags
    buf = io_in16(TIFR1);
    buf = buf & ~(1 << OCIF1);
    io_out16(TIFR1, buf);

}

void timer1_init(){
    unsigned short buf;
    // TCRA1
    // Clock Source auf intern/8 Prescaler
    // Timer Modus Fast-PWM
    buf = (1 << PS11) | (1 << TM10);
    io_out16(TCRA1, buf);
    // TCRB1
    // Counter Enable und Signalausgabe (OCO1) enablen
    buf = (1 <<CE1);
    io_out16(TCRB1, buf);
    // TIMR1
    // Kein Interrupt enable
    buf = (1<<OCIE1); // ocer1 enable später
    io_out16(TIMR1, buf);
    // CMPA1

    buf = 5000;
    io_out16(CMPA1, buf);
    // DIR1
    // Da das OCO1-Signal intern am Port 1 Bit 15 anliegt und ausgegeben werden soll
    // muss dieses Portbit auf Ausgang konfiguriert werden
   /* buf = io_in16(DIR1);
    buf = buf | (1 << OCIE1);
    io_out16(DIR1, buf);*/


}



void emain(void* arg)
{
    STATE cstate;		// Variable für den Zustand das Automaten.
unsigned short int buf;
    // Variablen für die Eingabesignale. Eine Variable fuer jedes Signal.
    USHORT		nach_oben;
    USHORT		nach_unten;
    USHORT		ist_oben;
    USHORT		ist_unten;
        USHORT           nach_oben_wegen_Zeit;
        USHORT           nach_unten_wegen_Zeit;
    // Variablen für die Ausgabesignale. Eine Variable fuer jedes Signal.
    USHORT		fahre_nach_oben;
    USHORT		fahre_nach_unten;

    USHORT		input, output, last_output;
     akt_zeit.hh=0;
     akt_zeit.mm=0;
     akt_zeit.ss=0;
     hoch_zeit.hh=1;
     hoch_zeit.mm=3;
     hoch_zeit.ss=0;
     runter_zeit.hh=2;
     runter_zeit.mm=5;
     runter_zeit.ss=5;


    INIT_BM_WITH_REGISTER_UI;	// Nur fuer Simulation

    // Zur Sicherheit vor Initialisierung den Interupt des PIC generell deaktivieren
    buf = io_in16(PICC);
    buf = buf &  ~(1 << PICE);
    io_out16(PICC, buf);

    // Timer 1 initialisieren
    timer1_init();

    // ISR registrieren
    setInterruptHandler(IVN_OC1, timer1_oco1_isr);

    // Uhrzeiterfragen ohne weitere Ueberpruefung
    /*putstring("Bitte die aktuelle Uhrzeit im Format hh:mm:ss eingeben\n");
    getstring(stringbuf);
    sscanf(stringbuf,"%d:%d:%d",&hh, &mm, &ss);*/

    // Interrupt des PIC jetzt zulassen
    buf = buf | (1 << PICE);
    io_out16(PICC, buf);

    // 1.)	Hardware konfigurieren
    io_out16(DIR1, 0xFF00); // Ausgang: Bits 15 bis 8   Eingang: Bits 7 bis 0

    // 2.)	 Definition des Startzustandes. Entspricht dem asynchronen Reset in VHDL.
    cstate = runter;

    // 3.) Unendliche Schleife. Ein Schleifendurchlauf entspricht einem Zyklus des Automaten
    while (1) {

        SYNC_SIM; // Nur fuer Simulation

        // 4.)	Einlesen der Eingabesignale einmal je Zyklus
        input = io_in16(IN1);

        // extrahieren von "ist_oben" (BIT_POS_IST_OBEN)
        ist_oben = (input >> BIT_POS_IST_OBEN) & 0x01;

        // extrahieren von "ist_unten" (BIT_POS_IST_UNTEN)
        ist_unten = (input >> BIT_POS_IST_UNTEN) & 0x01;

        // extrahieren von "nach_oben" (BIT_POS_NACH_OBEN)
        nach_oben = (input >> BIT_POS_NACH_OBEN) & 0x01;

        // extrahieren von "nach_unten" (BIT_POS_NACH_UNTEN)
        nach_unten = (input >> BIT_POS_NACH_UNTEN) & 0x01;

        // Aufruf der Steuerungsfunktion
                steuerungsfunktion    (	ist_oben, ist_unten, nach_oben, nach_unten,nach_oben_wegen_Zeit,
                                         nach_unten_wegen_Zeit,
                            &fahre_nach_oben, &fahre_nach_unten, &cstate	);


        // 7b.) Ausgabesignale ausgeben
        output=fahre_nach_unten<<BIT_POS_FAHRE_NACH_UNTEN;
        output=output | (fahre_nach_oben<< BIT_POS_FAHRE_NACH_OBEN);


        // Nur wirklich ausgeben wenn notwendig
        // Optimierung mittels bedigter Portausgabe
        if (last_output != output) {
            output=output | (1<< BIT_POS_MOTOR_AN);   // Nur fuer Bandmodell
            io_out16(OUT1, io_in16(OUT1) & 0x00FF);
            io_out16(OUT1, io_in16(OUT1) |  output);
            last_output = output;
        }
    } // end while
} // end main
#endif // V3_Aufgabe_1


#ifdef V3_Aufgabe_2_und_3
#include "user_conf.h"

typedef struct {
    unsigned char hh;
    unsigned char mm;
    unsigned char ss;
} uhrzeit;




void do_param(unsigned char* auszuwertende_nachricht, uhrzeit* akt, uhrzeit* hoch, uhrzeit* runter) {
    // Diese Funktion muss noch mit Leben gefuellt werden.
    // ...
}



// Vorgegebene globale Variablen und Makros
// Diese sind zum Teil auch in den Loesungen zu den relevanten Uebungsaufgaben schon vorhanden
#define MAX_MESSAGE_SIZE 100

unsigned char		byte_received;
unsigned char		nachricht[MAX_MESSAGE_SIZE];
unsigned char		flag_ready;
uhrzeit akt_zeit, hoch_zeit, runter_zeit;

// Hier muessen noch weitere globale Variablen und Makros eingefuegt werden
// ...

USHORT hilfe=0;
USHORT buf=0;
USHORT i=0;


void ISR_EXT_INT0()
{
    byte_received = io_in8(SPDR1);
    nachricht[i]= byte_received ;
    i++;
            if(i==16)i=0;// zzm 2 mal testen
hilfe=io_in8(SPSR1);
hilfe=hilfe & ~(1<<SPIF1);
io_out8(SPSR1,hilfe);
return;
}

void init_spi1(){
    io_out8(SPCR1,(1<<SPIE1)|(1<<SPE1));
}


void emain(void* arg)
{
    char string[300];

    INIT_BM_WITH_REGISTER_UI;

    // Hier die notwendigen Initialisierungen einfuegen.
    // ...
    // Zur Sicherheit vor Initialisierung den Interupt des PIC generell deaktivieren
       init_spi1();

    // Counter Enable
    buf=io_in16(PICC);
    buf = (1 <<PICE);
    io_out16(PICC, buf);

    // ISR registrieren
    setInterruptHandler(IVN_SPI1,ISR_EXT_INT0);

    // Interrupt des PIC jetzt zulassen
    buf=io_in16(PICC);
    buf = buf | (1 << PICE);
    io_out16(PICC, buf);
    while(1) {
#ifndef USER_PROG_2
        putstring("Sie haben USER_PROG_2 nicht definiert\n");
#endif
        putstring((char*)nachricht);
        if(flag_ready==1){
            putstring((char*)nachricht);
            putstring("\n");

            sprintf(string, "Akt:%d:%d:%d  Hoch:%d:%d:%d  Runter:%d:%d:%d\n", akt_zeit.hh,akt_zeit.mm,akt_zeit.ss, hoch_zeit.hh,hoch_zeit.mm,hoch_zeit.ss, runter_zeit.hh,runter_zeit.mm,runter_zeit.ss);
            putstring(string);
            flag_ready=0;
        }
    }

}


void master_transmit(char x){
    io_out8(SPDR2,x);
    while(!((io_in8(SPSR2))&(1<<SPIF2)));
}
//################AB HIER STEHT ALLES FUER DAS SENDER-PROGRAMM #################################################

void init_spi2(){
    io_out8(SPCR2,((1<<SPE2)|(1<<MSTR2)));
}

void emain_sender(void* arg)
 {
     unsigned char i;
     unsigned char parametriere_akt_zeit[]		=	"#A000005";
     unsigned char parametriere_hoch_zeit[]		=	"#B000105";
     unsigned char parametriere_runter_zeit[]	=	"#C000159";


     // Hier die notwendigen Initialisierungen einfuegen.
     // ...

     init_spi2();


     buf=io_in8(SPCR2);
       buf = buf | ( 1 << notSS2 );
       io_out8(SPCR2,buf);

       buf=io_in8(SPCR2);
       buf = buf & ~( 1 << notSS2);
       io_out8(SPCR2, buf);




     while(1) {
         i=0;
         do  {

             master_transmit( parametriere_runter_zeit[i]);

             // Damit der Empfaenger genuegen Zeit zum Reagieren (Einlesen des Bytes) hat
             // muss hier geweartet werden.
             ms_wait(20);

             i++;

         } while(i<8);

      }

 }


#endif //V3_Aufgabe_2_und_3



 #ifdef nachrichtenempfang_ueber_ports
// Sinnvoll zu nutzende Makros
#define COM_SIGNAl_PIN				0		// Pin ueber den der Interrupts ausgeloest wird
#define COM_DATA_IN_REGISTER		IN0		// Register ueber den das Byte eingelesen wird
#define MAX_MESSAGE_SIZE			100		// Maximale Laenge einer Nachricht
#define STARTBYTE					0xFE	// Wert des Start-Bytes
#define ENDBYTE						0xEF	// Wert des Ende-Bytes


typedef enum {warte_auf_start_byte, warte_auf_end_byte} STATE_N;


// Globale Variablen fuer die ISR
unsigned char		nachricht[MAX_MESSAGE_SIZE];
unsigned char		flag_ready;
STATE_N				comstate=warte_auf_start_byte;
unsigned long int	byte_counter;



void init_gpio_0_1()
{
    unsigned short hilfe = 0;

    // ### PORT 1
    // Interrupt fuer Bit 0 von PORT1 enable
    hilfe = io_in16(EIE1) | (1 << COM_SIGNAl_PIN);
    io_out16(EIE1, hilfe);

    // Das Bit 0 von PORT 1 ist Eingang
    hilfe = io_in16(DIR1) & ~(1 << COM_SIGNAl_PIN);
    io_out16(DIR1, hilfe);


    // ### PORT 0
    // Die unter 8 Bit von PORT0 sind Eingang
    hilfe = io_in16(DIR0) & 0xFF00;

    io_out16(DIR1, hilfe);

}


void steuerungsfunktion(	unsigned char byte_received, unsigned long int* byte_zaehler, unsigned char* 						empfangene_nachricht, unsigned char* ready, STATE_N* state)
{

    switch (*state) {

        case warte_auf_start_byte:
            // Uebergang nach warte_auf_end_byte
            if ( byte_received == STARTBYTE) {
                // Etwas tun am Uebergang.
                *byte_zaehler=0;
                empfangene_nachricht[*byte_zaehler]=byte_received;
                *byte_zaehler=*byte_zaehler+1;

                // Zustandswechsel
                *state = warte_auf_end_byte;
            }
            break;

        case warte_auf_end_byte:
            // Uebergang nach warte_auf_start_byte
            if (byte_received == ENDBYTE)  {
                // Etwas tun am Uebergang.
                empfangene_nachricht[*byte_zaehler]=byte_received;
                *byte_zaehler=*byte_zaehler+1;

                *ready=1;

                // Zustandwechsel
                *state = warte_auf_start_byte;
            }

            if (*byte_zaehler == MAX_MESSAGE_SIZE-1) {
                // Die Nachricht ist zu lang und kann dahr nicht gueltig sein!
                // Zustandwechsel
                *state = warte_auf_start_byte;
            }

            // Uebergang auf sich selbst nur damit etwas getan wird.
            if (byte_received == STARTBYTE) {
                // Etwas tun am Uebergang.
                *byte_zaehler=0;
                empfangene_nachricht[*byte_zaehler]=byte_received;
                *byte_zaehler=*byte_zaehler+1;

                // Zustandwechsel
                *state = warte_auf_end_byte;	// Ist ueberfluessing dient aber hoffentlich
                                        // dem Verstaendnis
            }

            // Uebergang auf sich selbst nur damit etwas getan wird.
            if ((byte_received != STARTBYTE) && (byte_received != ENDBYTE)
                && (*byte_zaehler < MAX_MESSAGE_SIZE-1)) {
                // Etwas tun am Uebergang.
                empfangene_nachricht[*byte_zaehler]=byte_received;
                *byte_zaehler=*byte_zaehler+1;

                // Zustandwechsel
                *state = warte_auf_end_byte;	// Ist ueberfluessing dient aber hoffentlich
                                        // dem Verstaendnis
            }

            break;

        // 9.) nicht erlaubte Zustaende "abfangen"
        default:
            *state = warte_auf_start_byte;
    } // switch

}



void ISR_EXT_INT0()
{
    unsigned short int hilfe = 0;
    unsigned char buf;

    // Einlesen des Datenbytes
    buf=(unsigned char) (io_in16(COM_DATA_IN_REGISTER) & 0x00FF);

    // Aufruf der Steuerungsfunktion
    steuerungsfunktion(buf, &byte_counter, &(nachricht[0]), &flag_ready, &comstate);

    // Zureucksetzen des Interrupt-Flags
    hilfe = io_in16(EIF1) & ~(1<<COM_SIGNAl_PIN);
    io_out16(EIF1, hilfe);
    return;
}


void emain(void* arg)
{
     unsigned short int buf;

     INIT_REGISTER_UI_WITHOUT_BM

     // Zur Sicherheit vor Initialisierung den Interrupt des PIC generell deaktivieren
     buf = io_in16(PICC);
     buf = buf &  ~(1 << PICE);
     io_out16(PICC, buf);

     // Initialisieren der Ports
     init_gpio_0_1();

     // Registrieren der ISRs in der Interupt-Vektor-Tabelle
     setInterruptHandler(IVN_EI100, ISR_EXT_INT0);

     // Interrupt des PIV jetzt zulassen.
     buf = buf | (1 << PICE);
     io_out16(PICC, buf);


     while(1)
     {

     }

}
#endif // nachrichtenempfang_ueber_ports


#ifdef timer_als_taktsignalgenerator

// Globale Variablen zur Kommunikation mit der ISR
unsigned long int zt=0, hh=0, mm=0, ss=0;

void timer1_init()
{
    /*	Zur Berechnung der Werte fuer den Prescaler und den Compare-Match:
        Bei einer Frequenz von 4 Mhz zaehlt der Timer mit einem Takt von 0,25us.
        Er kann mit seinen 65536 moeglichen Zaehlstaenden eine maximale Interrupt-Periode von 65536 * 0,25us = 16384us realisieren.
        Dies ist zu schnell. => Der Zaheler muss mittels des Prescalers langsamer eingestellt werden.
        Die ideale Untersetzung waere  50000us / 16384us = 3,0517.
        Da es diese Unterssetzung (Prescaler-Wert) nicht gibt waehlen wir den naechst groesseren Wert also 8.
        Der Zaehler zaehlt jetzt mit einem Takt vom 2us. => Die Interrupts haben bei einem Compare-Match-Wert von 65535
        eine Periode von 131072 us.Der Compare-Match-Wert muss auf 50000us/131072us*65536us = 25000 eingestellt werden.
    */

    unsigned short buf = 0;

    // TCRA1
    // Clock Source auf intern/8 Prescaler
    // Timer Modus Clear-Timer-On-Compare-Match
    buf = (1 << PS11) | (1 << TM10);
    io_out16(TCRA1, buf);

    // TCRB1
    // Counter Enable
    buf = (1 <<CE1);
    io_out16(TCRB1, buf);

    // TIMR1
    // Compare Match Interrupt enable
    buf = (1 << OCIE1);
    io_out16(TIMR1, buf);

    // CMPA1
    // Compare Match Register auf ...
    buf = 25000;
    io_out16(CMPA1, buf);
}

// Makros damit man beim Testen nicht so lange warten muss
// Die korrekten Werte stehen als Kommentare jeweils dahinter
#define ZT_MAXW	3	//20
#define SS_MAXW	3	//60
#define MM_MAXW	3	//60
#define HH_MAXW	3	//24

//	Interrupt Service Routine
void timer1_oco1_isr()
{
    unsigned char stringbuf[100];
    unsigned short int buf;

    zt++;

    if(zt==ZT_MAXW){
        zt=0;
        ss++;
    }

    if(ss==SS_MAXW){
        ss=0;
        mm++;
    }

    if(mm==MM_MAXW){
        mm=0;
        hh++;
    }
    if(hh==HH_MAXW){
        hh=0;
    }

    sprintf(stringbuf,"zt=%d  Uhrzeit: %d:%d:%d\n",zt,hh,mm,ss);
    // Achtung die Verwendung von putstring() kann in der Simulationsumgebung
    // zu einem Deadlock fuehren, d.h. alles bleibt einfach stehen.
    // Dahr ist dies hier (zur Sicherheit) auskommentiert.
    // putstring(stringbuf);

    // Zuruecksetzen des Interrupt-Flags
    buf = io_in16(TIFR1);
    buf = buf & ~(1 << OCIF1);
    io_out16(TIFR1, buf);

}



 void emain(void* arg)
 {
    unsigned short buf = 0;
    unsigned char stringbuf[100];

    INIT_BM_WITH_REGISTER_UI; // Nur zur Simulation

    // Zur Sicherheit vor Initialisierung den Interupt des PIC generell deaktivieren
    buf = io_in16(PICC);
    buf = buf &  ~(1 << PICE);
    io_out16(PICC, buf);

    // Timer 1 initialisieren
    timer1_init();

    // ISR registrieren
    setInterruptHandler(IVN_OC1, timer1_oco1_isr);

    // Uhrzeiterfragen ohne weitere Ueberpruefung
    putstring("Bitte die aktuelle Uhrzeit im Format hh:mm:ss eingeben\n");
    getstring(stringbuf);
    sscanf(stringbuf,"%d:%d:%d",&hh, &mm, &ss);

    // Interrupt des PIC jetzt zulassen
    buf = buf | (1 << PICE);
    io_out16(PICC, buf);

    while(1);
 }
#endif // timer_als_taktsignalgenerator
