/* 
 * File:   console.c
 * Author: Mike Dawson
 *
 * Created on March 21, 2024, 1:38 PM
 */

#include "globals.h"

/*
 *  Internal function prototypes
 */
void CONSOLE_SETUP(void);
void CONSOLE_SEND_STRING(char* msg);



void CONSOLE_SEND_STRING(char* msg)
{
     while (*msg != 0)
    {
        while ((TX1STA & 0x02) == 0);
        TX1REG = *msg++;
    }
}


 /*
 *  Configure UART pins for the serial console
 *  The DevKit is built to use RC0 (Pin 16) for the TXD and RC1 (Pin 15) for the RXD
 *  The DevKit utilizes an integrated USB to UART chip hardwired to the pins.
 *  The USB to UART interface is the CP2102N-A02-GQFN20R by Silicon Labs.
 */
void CONSOLE_SETUP(void)
{    
    /* Configure the UART for 8N1 asynchronous operation */
    TX1STA = 0x24; 
    RC1STA = 0x90; 
    BAUD2CON = 0x00;
    SP1BRG = 12; //Default core frequency is 16MHz. 25 = 9600, 12 = 19.2K

    /* Configure the pins for the UART port. This will use the integrated USB to UART chip. */
    RX1PPS = RC1;  //RX Pin 
    RC0PPS = 0x13; //TX Pin 
   
    /* enable and clear the receive interrupt */
    RC1IE = 1;
    RC1IF = 0;
    
    /* Hello world! */
    CONSOLE_SEND_STRING("Starting: \n");
    CONSOLE_SEND_STRING(FIRMWARE_NAME);
    CONSOLE_SEND_STRING("\n");
    CONSOLE_SEND_STRING("Firmware version: ");
    CONSOLE_SEND_STRING(VERSION_NUMBER);
    CONSOLE_SEND_STRING("\n\n\r");
}


