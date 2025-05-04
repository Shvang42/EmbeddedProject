#include <msp430.h>
#include <stdbool.h>
#include "ignitorLED.h"
#include "msp430fr2355.h"

static unsigned int seed = 0;

void initIgnitorLED() {
    // initialize random seed via timer
    seed = TB0R;

    P2DIR |= BIT0;
    P2OUT &= ~BIT0;
}

// method for random was made through the help of claude.ai
int randomNumber() {
    // update seed for better randomness
    seed = seed * 1103515245 + 12345;

    return ((seed >> 16) & 0x7FFF) % 100;
}

bool flameProved() {
    int random = randomNumber();

    if(number < 95) {
        P2OUT |= BIT0;
        return true;
    }
    else {
        P2OUT &= ~BIT0;
        return false;
    }
}