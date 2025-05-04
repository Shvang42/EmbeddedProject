/**
main.c
Author: Shivang Patel, Phillip Amaro

Main method for Residential Boiler System

Last Revision: 3/4/25

*/


#include <msp430.h>
#include "sensors.h"
#include "RGBLED.h"
#include "solenoid.h"
#include "callForHeat.h"

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

    while(1) {

    }
    
}