#include <16F877A.h>
#device ADC=10

#FUSES PUT                      //Power Up Timer
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOPROTECT                //Code not protected from reading

#use delay(crystal=8MHz)
#use FIXED_IO( A_outputs=PIN_A5)
#use FIXED_IO( B_outputs=PIN_B2, PIN_B3)
#define liga   PIN_B0
#define desliga   PIN_B1
#define LED   PIN_B3
#define LEDL  PIN_B2
#define buzzer    PIN_A5




