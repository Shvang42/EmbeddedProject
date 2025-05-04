#include <msp430.h>
#include "servo.h"
#include "msp430fr2355.h"

void initServo() {
    P5DIR |= BIT0;
    P5SEL0 |= BIT0;
    P5SEL1 &= ~BIT0;

    TB0CTL = TBSSEL__SMCLK | MC__UP | TBCLR;
    TB0CCR0 = PWM_PERIOD - 1;
    TB0CCTR5 = MIN_PULSE;
    TB0CCTL5 = OUTMOD_7;
}

int servo(int position) {
    
    unsigned int pulseWidth = MIN_PULSE + ((MAX_PULSE - MIN_PULSE) * position/100);
    TB0CCR5 = pulseWidth;

    return position;
}