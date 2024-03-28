## DRV8825-PIC16F18146-MAIN ##
Basic driver and interface example code for the DRV8825 Stepper motor driver IC for the PIC16F14146 based upon the development kit that I designed.


### CHANGELOG ###
* v1.0 - 3/27/2024 - MSD - Initial compiling code to set the foundataions for the project. Will compile and outputs on the appropriate pin. Need to test further.
* v1.1 - 3/28/2024 - MSD - Added ADC reading of RC5, PWM output and mapping the ADC range to a range that the PWM will accept. Outputting the ADC raw value over the UART so it can be monitored via an external utility for now. The PWM output is RC3 in this example.


