/*
 * File:   main.c
 * Author: Mike Dawson
 *
 * Created on March 27, 2024
 * Refer to the README.md file for the change log.
 */

#include "globals.h" //A single header file to store references to all necessary headers and other relevant information for simplicity

uint16_t ADC_DATA = 0;
double_t ADC_CONVERTED = 0.0;
long PWM_VALUE = 0;

#define DELAY_TIME 125


/*
 *  Define the OUTPUTS for the stepper driver
 */
#define ENABLE RC4 //Active LOW
#define DIRECTION RA4
#define STEP RC3 //Output that controls the stepper speed



/*
 *  Define the INPUTS for the stepper driver
 */


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
    
    /* Configure the PWM support for the STEP output */       
    RC3PPS = 0x0A; //Configures RC3 with an output source of CCP2 for PWM
    TRISCbits.TRISC3 = 1; //Sets RC3 as an output temporarily for PWM configuration
    T2PR = 0x64; //PWM period value of 100
    CCP2CON = 0x8C; // Enable | FMT = 0 | PWM Mode
    CCPR2 = 0x0; //Configures the Pulse-Width register for 0%. Full range is 0x00 to 0x64 as a percentage value (0 to 100)
    PIR2bits.TMR2IF = 0; //Clears the interrupt flag of timer 2
    T2CLKCON = 0x01; //Sets Fosc/4 as the timer source
    T2CON = 0x00; //Sets a 1:1 pre-scaler
    T2ON = 1; //Enables the timer for the PWM output
    TRISCbits.TRISC3 = 0; //Sets RC3 back to an output and enables it for the PWM
    
    /* Configure the ADC input for RC5 */
    ADCON0bits.FM = 0x1; //Right justify
    ADCON0bits.CS = 1; //ADCRC Clock
    ADCON0bits.IC = 0; //Single input mode
    ADPCH = 0x15; //Sets RC5 as the positive input
    TRISCbits.TRISC5 = 1; //Sets RC5 as an input
    ANSELCbits.ANSELC5 = 1; //Selects RC5 as an analog input
    ADACQ = 32; //Sets the acquisition time
    ADCON0bits.ON = 1; //Enables the ADC
        
}





void main(void) {
    /* Here we will initialize the UART port */
    CONSOLE_SETUP();

    /* Run the configuration for the PORTS */
    CONFIGURE_PORTS();
    
    /* Setup the initial starting configuration of the stepper driver*/
    ENABLE = 1;
    DIRECTION = 0;
    
    
    while(1)
    {
        ADCON0bits.GO = 1; //Start a conversion
        while (ADCON0bits.GO); //Wait for the conversion to be completed
        ADC_DATA = ADRES;
        PWM_VALUE = map(ADC_DATA, 0, 4095, 0, 100);
        CCPR2 = PWM_VALUE; //Sets the PWM output to the new ADC mapped value
        
        
        /* We will send the ADC raw value over UART so we can monitor it externally */
        char ADC_STRING[32];
        sprintf(ADC_STRING, "%d \r", ADC_DATA);
        CONSOLE_SEND_STRING(ADC_STRING);
        
        //char ADC_VOLTS[16];
        //ADC_CONVERTED = (ADC_DATA / 4095) * 3.3;       
        //sprintf(ADC_VOLTS, "%.2f \n", ADC_CONVERTED);
        //CONSOLE_SEND_STRING(ADC_VOLTS);        
        
        //char PWM_STRING[32];
        //sprintf(PWM_STRING, "%ld \n\n", PWM_VALUE);
        //CONSOLE_SEND_STRING(PWM_STRING);
        __delay_ms(250); //Introduce a slight delay to slow down the text on the UART
                
        
    }
}
