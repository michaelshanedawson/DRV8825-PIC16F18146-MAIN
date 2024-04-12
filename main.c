/*
 * File:   main.c
 * Author: Mike Dawson
 *
 * Created on March 27, 2024
 * Refer to the README.md file for the change log.
 */

#include "globals.h" //A single header file to store references to all necessary headers and other relevant information for simplicity

#define DELAY_TIME 125


/*
 *  Define the OUTPUTS for the stepper driver
 */
#define ENABLE RC4 //Active LOW
#define DIRECTION RA4 //LOW is CCW and HIGH is CW

/* Declare function prototypes */
void CONFIGURE_PORTS(void);

void CONFIGURE_PORTS(void)
{
    /* Configure PORTA */
    PORTA = 0x00; //Clear port A
    LATA = 0x00; //Clear port A data latch
    ANSELA = 0x00; //Enable digital drivers for port A, a bit value of 1 means the port is analog
    TRISA = 0x00; //Set all of port A to output mode, a bit value of 1 anywhere changes the port to an input
    
    /* Configure PORTC */
    PORTC = 0x00;
    LATC = 0x00;
    ANSELC = 0x00; //We will be setting this later for RC5
    TRISC = 0x00;  //We will be setting this later for RC5
    
    /* Configure TIMER0 output to control the stepper speed */
    RC7PPS = 0x1F; //Configures RC7 as the output pin for TIMER0
    
    T0CON0bits.T0MD16 = 0; //TIMER0 is a 16 bit timer
    T0CON1bits.CS = 0b011; //Selects TIMER0 clock source
    T0CON1bits.T0ASYNC = 1; //TIMER0 is not syncronized to Fosc/4
    T0CON1bits.T0CKPS = 0b0001; //Prescaler rate select
    T0CON0bits.OUTPS = 0b0000; //Postscaler (divider) select
    T0CON0bits.T0EN = 1; //Enables TIMER0
}

void main(void)
{   
    OSCFRQ = 0x5; //Sets HFINTOSC to 32MHz (0x5)
    
    /* Here we will initialize the UART port */
    CONSOLE_SETUP();

    /* Run the configuration for the PORTS */
    CONFIGURE_PORTS();
    
    /* Setup the initial starting configuration of the stepper driver*/
    ENABLE = 0;
    DIRECTION = 1;
}

