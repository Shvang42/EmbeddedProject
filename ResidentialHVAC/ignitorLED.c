#include <msp430.h>
#include <stdbool.h>
#include "ignitorLED.h"
#include "msp430fr2355.h"

void initIgnitorLED() {
    P2DIR |= BIT0;
    P2OUT &= ~BIT0;
}

void flamePresent() {
    P2OUT |= BIT0;
}

void flameLost() {
    P2OUT &= ~BIT0;
}