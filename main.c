/*
 * File:   main.c
 * Author: Mike Dawson
 *
 * Created on March 27, 2024
 * Refer to the README.md file for the change log.
 */

#include "globals.h" //A single header file to store references to all necessary headers and other relevant information for simplicity
/*
 *  Define the OUTPUTS for the stepper driver
 */
#define ENABLE RC4 //Active LOW
#define DIRECTION RA4
#define STEP RC3 //Output that controls the stepper speed

#define DELAY_TIME 125

/*
 *  Define the INPUTS for the stepper driver
 */
#define SPEED RC5 //This will be an ADC input

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
    ANSELC = 0x20; //Bit mask to select RC5 as an analog port
    TRISC = 0x0; 
    
    /* Configure the PWM support for the STEP output        
    RC3PPS = 0x0A; //Configures RC3 with an output source of CCP2 for PWM
    TRISCbits.TRISC3 = 1; //Sets RC3 as an output temporarily for PWM configuration
    T2PR = 0x64; //PWM period value of 100
    CCP2CON = 0x8C; // Enable | FMT = 0 | PWM Mode
    CCPR2 = 0x32; //Configures the Pulse-Width register for 0%. Full range is 0x00 to 0x64 as a percentage value (0 to 100)
    PIR2bits.TMR2IF = 0; //Clears the interrupt flag of timer 2
    T2CLKCON = 0x01; //Sets Fosc/4 as the timer source
    T2CON = 0x00; //Sets a 1:1 pre-scaler
    T2ON = 1; //Enables the timer for the PWM output
    TRISCbits.TRISC3 = 0; //Sets RC3 back to an output and enables it for the PWM */
        
}





void main(void) {
    /* Here we will initialize the UART port */
    CONSOLE_SETUP();

    /* Run the configuration for the PORTS */
    CONFIGURE_PORTS();
    
    /* Setup the initial starting configuration of the stepper driver*/
    ENABLE = 0;
    DIRECTION = 0;
    
    
    while(1)
    {
        RC3 = 0;
        __delay_ms(DELAY_TIME);
        RC3 = 1;
        __delay_ms(DELAY_TIME);
    }
}
