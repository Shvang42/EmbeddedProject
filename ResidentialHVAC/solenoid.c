#include <msp430.h>
#include "solenoid.h"

void initSolenoid() {
    P2DIR |= BIT5;
    P2OUT &= ~BIT5;
}

void pilotOn() {
    P2OUT |= BIT5;
}

void pilotOff() {
    P2OUT &= ~BIT5;
}

void togglePilot() {
    P2OUT ^= BIT5;
}