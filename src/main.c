#include <24FJ48GA002.h>
#include "BL_Support.h"
#include <stdint.h>
#use delay(internal = 8 MHz, clock = 32MHz)
#PIN_SELECT U1RX = PIN_B12 //PIN_B14 //
#PIN_SELECT U1TX = PIN_B13 //PIN_B15 //

#use rs232(UART1, BAUD = 256000, XMIT = PIN_B13, RCV = PIN_B12)

int main(void)
{
    return 0;
}