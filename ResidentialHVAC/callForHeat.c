#include <msp430.h>
#include <stdbool.h>
#include "callForHeat.h"

void initCFH() {
    PIDIR &= ~BIT2;
    P1REN |= BIT2;
    P1OUT |= BIT2;
}

bool callForHeatCheck() {
    if(P1in & BIT2) {
        return true;
    }
    else {
        return false;
    }
}