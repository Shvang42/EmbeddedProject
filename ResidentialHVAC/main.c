/**
main.c
Author: Shivang Patel, Phillip Amaro

Main method for Residential Boiler System

Last Revision: 3/8/25

*/


#include <msp430.h>
#include "sensors.h"
#include "RGBLED.h"

volatile unsigned char idle = 0;

int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;               

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port setting
    PM5CTL0 &= ~LOCKLPM5;                   
    
    initSensorsADC();
    initRGB();
    pilotValveInit();
    

}
/**
Homework2.c code below

#define DELAYCYCLES 50000

volatile unsigned char redLedActive = 0;
volatile unsigned char greenLedActive = 0;

void configureButtons();
void configureLEDS();

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    configureButtons();
    configureLEDs();
    __enable_interrupt();

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    unsigned long count = 0;
    unsigned char ledState = 0;             // keep track of whether or not to turn on or off the LED for both LEDs

    while(1)
    {
        // 1. Determine if Button 4.1 is pressed
        
            // 1.1 If Pressed, then toggle the LED.

            // 1.2 If Not, Turn LED off

        // 2. Determine if Button 2.3 is pressed

            // 2.1 If Pressed, then toffle the LED on

            // 2.2 If not, Turn LED Off.

        // 3. Wait to blink the LED again without using __delay_cycles.

        count++;

        if(count >= DELAYCYCLES) {
            ledState = !ledState;       // Toggle LED State

            // Toggle P6.0 using exclusive-OR
            // reset count to blink led
            if(redLedActive) {          // If interrupt triggered
                if(ledState) {          // Toggling led on and off check
                    P1OUT |= BIT0;      // Turn on
                }
                else {
                    P1OUT &= ~BIT0;     // Turn off
                }
            }
            else {
                P1OUT &= ~BIT0;         // Turn off LED
            }
            if(greenLedActive) {
                if(ledState) {
                    P6OUT |= BIT6;
                }
                else {
                    P6OUT &= ~BIT6;
                }
            }
            else {
                P6OUT &= ~BIT6;         // Turn off LED
            }

            count = 0;
        }

    }
}


void configureButtons(){

    // 1. Configure the pins for Buttons as Inputs

    // 2. Enable the Pullup Resistors on those pins 

    // 3. Configure the pullup Resistors on those pins

    // Configure Button 1 as Input with Pull-Up Resistor
    P4DIR &= ~BIT1;             // Set P1.3 as input
    P4REN |= BIT1;
    P4OUT |= BIT1; 
    P4IES |= BIT1;
    P4IE |= BIT1;
    P4IFG &= ~BIT1;

    // Configure Button 2 as Input with Pull-Up Resistor
    P2DIR &= ~BIT3;             // Configure as Input
    P2REN |= BIT3;              // Enable as Resistor
    P2OUT |= BIT3;
    P2IES |= BIT3;
    P2IE |= BIT3;
    P2IFG &= ~BIT3;

}

void configureLEDs(){

    // 1. Configure LED Pins as Outputs

    // 2. Set an initial state for the LEDs

    // Configure red LED
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction

    // Set select lines for the port Mux to be an I/O
    P1SEL0 &= ~BIT0;
    P1SEL1 &= ~BIT0;

    // Configure green LED
    P6OUT &= ~BIT6;
    P6DIR |= BIT6;

    // Set select lines for the port Mux to be an I/O
    P6SEL0 &= ~BIT6;
    P6SEL1 &= ~BIT6;

}

#pragma vector=PORT4_VECTOR
__interrupt void Port_4_ISR(void) {
    if(P4IFG & BIT1) {          // Interrupt Tripped
        P4IFG &= ~BIT1;         // Clear Interrupt Flag

        P4IES ^= BIT1;          // detect press and release, rise/falling

        redLedActive = !(P4IN & BIT1); // state of button

    }
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2_ISR(void) {
    if(P2IFG & BIT3) {          // Interrupt Tripped
        P2IFG &= ~BIT3;         // Clear Interrupt Flag

        P2IES ^= BIT3;          // detect press and release, rise/falling

        greenLedActive = !(P2IN & BIT3); // state of button

    }
}

*/