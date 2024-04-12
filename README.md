## DRV8825-PIC16F18146-MAIN ##
Basic driver and interface example code for the DRV8825 Stepper motor driver IC for the PIC16F14146 based upon the development kit that I designed. The core idea is to use the driver IC to handle a basic PCB conveyor unit to work with SMT lines for hobbyists and entry level assembly houses. 


### CHANGELOG ###
* v1.0 - 3/27/2024 - MSD - Initial compiling code to set the foundataions for the project. Will compile and outputs on the appropriate pin. Need to test further.
* v1.1 - 3/28/2024 - MSD - Added ADC reading of RC5, PWM output and mapping the ADC range to a range that the PWM will accept. Outputting the ADC raw value over the UART so it can be monitored via an external utility for now. The PWM output is RC3 in this example.
* v1.2 - 4/12/2024 - MSD - Removed the ADC input and the PWM output in favor of a fixed clock output using TIMER0 for the stepper driver. At slower speeds, the DRV8825 IC does heat up relatively fast. If the idea is to have this unit drive slower stepper speeds, add some really good heatsinking and/or active cooling to the driver chip. Adjust the prescaler and postscaler values to adjust the speed. There is a basic worksheet in Excel format that can help determine the needded STEP value. The motor will get warm as well, recommend heatsinking it to reduce wear and tear. The code does need further refinement for speed control.


