#include <msp430.h>
#include "solenoid.h"

void initSolenoid() {
    P2DIR &= ~BIT5;
    P2REN |= BIT5;
    P2OUT |= BIT5;
}

void isSolenoidOn() {
    if(P2IN & BIT5) {
        return true;
    }
    else {
        return false;
    }
}