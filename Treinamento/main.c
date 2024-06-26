#include <main.h>
#include "lcd_8bits.c"

int1 tempo_finalizado = 0;
int1 em_processo = 0;
const int8 CONTADOR_TEMPO_INIT = 125;
const int16 VALOR_ALCOOL_PERMITIDO = 700;
int8 contador_tempo = CONTADOR_TEMPO_INIT;
int16 leitura_potenciometro = 0, VP = VALOR_ALCOOL_PERMITIDO;

#INT_TIMER0
void TIMER0_isr(void) 
{
    set_timer0(get_timer0() + 6);
    contador_tempo--;
    if (contador_tempo == 0)
    {
        contador_tempo = CONTADOR_TEMPO_INIT;
        tempo_finalizado = 1;
    }
}

void main()
{
    setup_adc_ports(AN0_AN1_AN3);
    setup_adc(ADC_CLOCK_INTERNAL);
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_16 | RTCC_8_BIT); 

    lcd_init();
   
    
    printf(lcd_write_dat, "AM:");
    lcd_gotoxy(10,1);
    
    printf(lcd_write_dat, "AP:");
    lcd_gotoxy(1,2);
    
    printf(lcd_write_dat, "P:OF");
    lcd_gotoxy(7,2);
    
    printf(lcd_write_dat, "VU:OF");
    lcd_gotoxy(13,2);
    
    enable_interrupts(INT_TIMER0);
    enable_interrupts(GLOBAL);


    while (TRUE)
    {
        if (tempo_finalizado)
        {
            tempo_finalizado = 0;
            set_adc_channel(1);
            delay_us(40);
            leitura_potenciometro = read_adc();
            lcd_gotoxy(4, 1);
            printf(lcd_write_dat, "%04lu", leitura_potenciometro);
            lcd_gotoxy(13, 1);
            printf(lcd_write_dat, "%04lu", VP);

        }

        if (input(liga) == 0)
        {
            em_processo = 1;
            lcd_gotoxy(4, 2);
            printf(lcd_write_dat, "N");
            output_high(LEDL);
            
        }

        if (input(desliga) == 0)
        {
            em_processo = 0;
            output_low(buzzer);
            output_low(LED);
            output_low(LEDL);
            lcd_gotoxy(4, 2);
            printf(lcd_write_dat, "F");

            lcd_gotoxy(11, 2);
            printf(lcd_write_dat, "F");
        }

        if (em_processo)
        {
            if(leitura_potenciometro >= VP)
            {
               output_high(buzzer);
               output_high(LED);
               lcd_gotoxy(11, 2);
               printf(lcd_write_dat, "N");
            }
            else
            {
               output_low(buzzer);
               output_low(LED);
               lcd_gotoxy(11, 2);
               printf(lcd_write_dat, "F");
            }
        }
    }
}


