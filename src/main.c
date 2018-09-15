#include <24FJ48GA002.h>
#include "BL_Support.h"

#use delay(internal = 8 MHz, clock = 32MHz)
#PIN_SELECT U1RX = PIN_B12 // pin_b14
#PIN_SELECT U1TX = PIN_B13 // pin_b15
#use rs232(UART1, BAUD = 9600, XMIT = PIN_B13, RCV = PIN_B12)

#PIN_SELECT oc1 = PIN_B2

#define TIME_PERIOD 250

#INT_TIMER2
void TIMER2_is()
{
    output_toggle(PIN_A2);
}

void init_timer23()
{
    setup_timer2(TMR_INTERNAL | TMR_DIV_BY_64, TIME_PERIOD);
    enable_interrupts(INT_TIMER2);
}

void main(void)
{
    output_bit(PIN_A2, 1);
    disable_interrupts(GLOBAL);
    init_timer23();
    enable_interrupts(GLOBAL);

    setup_compare(1, COMPARE_PWM | COMPARE_TIMER2);
    set_pwm_duty(1, 250);

    while (TRUE)
        ;
}