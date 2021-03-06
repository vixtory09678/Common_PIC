/*
    robotics-za.blogspot.com
    https://github.com/vixtory09678/Common_PIC
*/

#include "lib/24FJ48GA002.h"
#include "lib/BL_Support.h"

#use delay(internal = 8 MHz, clock = 32MHz)
#PIN_SELECT U1RX = PIN_B12 // pin_b14
#PIN_SELECT U1TX = PIN_B13 // pin_b15
#use rs232(UART1, BAUD = 115200, XMIT = PIN_B13, RCV = PIN_B12)

#PIN_SELECT INT1 = PIN_B4
#PIN_SELECT INT2 = PIN_B5

#PIN_SELECT oc1 = PIN_B2

#define TIME_PERIOD 625
#define RESOLUTION 600f
#define Lead 8f // Lead length
#define SET_POINT 400f

long count = 0;
float time = 0.0;
float u = 12.0;
float y = 0.0;

boolean trig = false;

float findDistanceZ(long pulse)
{
    return (pulse / 2.0) / RESOLUTION * Lead;
}

void printFloat(float n)
{
    long dec = (int)n;
    long degit = (n - dec) * 100;

    degit = (degit < 0) ? abs(degit) : degit;
    printf("%d.%d%d", dec, degit / 10, degit % 10);
}

#INT_TIMER3
void TIMER3_isr(void)
{
    if (trig)
    {
        time += 0.01;
        y = findDistanceZ(count);
        printFloat(time);
        printf(",");
        printFloat(u);
        printf(",");
        printFloat(y);
        printf("\n");

        if (time > 10.0)
        {
            if (trig == true)
            {
                printf("end\n");
            }
            trig = false;
        }
    }
}

#INT_EXT1
void INT_EXT_INPUT1(void)
{
    if (trig)
    {
        if (input(PIN_B5) == 1)
        {
            count++;
        }
        else
        {
            count--;
        }
    }
}

void setupEncoderInterrupt()
{
    enable_interrupts(INT_EXT1);
    ext_int_edge(1, H_TO_L);
}

void initTimer2()
{
    setup_timer2(TMR_INTERNAL | TMR_DIV_BY_256, TIME_PERIOD);
    enable_interrupts(INT_TIMER2);
}

void main(void)
{

    // initialize count to zero
    count = 0;
    disable_interrupts(GLOBAL);
    initTimer2();
    setupEncoderInterrupt();
    enable_interrupts(GLOBAL);

    while (TRUE)
    {
        // press SW3 to start sampling log
        if (input(PIN_B6) == 0)
        {
            count = 0;
            trig = true;
            time = 0.0;
            y = 0.0;
        }
    }
}
