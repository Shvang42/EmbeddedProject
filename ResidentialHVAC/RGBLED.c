#include <msp430.h>
#include "RGBLED.h"

void setLedState(char state) {
    if(state == "idle") {
        // set to blue since idle
        setRGBLED(137, 175, 240);
    }
    else { // any char beside idle will be considered not idle or active, set to green
        setRGBLED(86, 209, 90);
    }
}

void setRGLED(char Red, char Green, char Blue) {
    TB3CCR3 = Red << 2;
    TB3CCR2 = Green << 2;
    TB3CCR1 = Blue << 2;
}

void initRGB() {
    P6DIR |= BIT0 | BIT1 | BIT2;
    P6SEL1 &= ~(BIT0 | BIT1 | BIT2);
    P6SEL0 |= BIT0 | BIT1 | BIT2;

    TB3CCR0 = 1024-1;                         // PWM Period
    TB3CCTL1 = OUTMOD_3;                      // CCR1 set/reset
    TB3CCR1 = 750;                            // CCR1 PWM duty cycle
    TB3CCTL2 = OUTMOD_3;                      // CCR2 set/reset
    TB3CCR2 = 250;                            // CCR2 PWM duty cycle
    TB3CCTL3 = OUTMOD_3;                      // CCR3 set/reset
    TB3CCR3 = 500;                            // CCR3 PWM Duty Cycle
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR

}