#include <msp430.h>
#include <stdbool.h>
#include "callForHeat.h"
#include "sensors.h"

void initCFH() {
    PIDIR &= ~BIT2;
    P1REN |= BIT2;
    P1OUT |= BIT2;
}

bool callForHeatCheck() {
    if(readThermistor() == readPot()) {
        return false;
    }
    if(P1in & BIT2) {
        return true;
    }
    else {
        return false;
    }
}