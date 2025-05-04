#include <msp430.h>
#include "sensors.h"

// Thermistor, Thermocouple, and Potentiometer
// Thermistor       --> 1.4 (A4)
// Thermocouple     --> 1.3 (A3)
// Potentiometer    --> 1.5 (A5)

unsigned int readThermistor() {
    unsigned int result;
    result = readADC('4');
}

unsigned int readThermocouple() {
    unsigned int result;
    result = readADC('3');
}

unsigned int readPot() {
    unsigned int result;
    result = readADC('5');
}


void initSensorsADC() {
    // Configure ADC Pins
    P1SEL0 |= BIT3 | BIT4 | BIT5;
    P1SEL1 |= BIT3 | BIT4 | BIT5;

    // Configure ADC
    // ADCON, S&H=16 ADC clks
    ADCCTL0 |= ADCSHT_2 | ADCON;
    // ADCCLK = MODOSC; sampling timer
    ADCCTL1 |= ADCSHP;

    // clear ADCRES in ADCCTL
    // 12-bit conversion results
    ADCCTL2 &= ~ADCRES;
    ADCCTL2 |= ADCRES_2;

    // Enable ADC conv complete interrupt
    ADCIE |= ADCIE0;

}

unsigned int readADC(char channel) {
    // Depending on what channel needs to be listened to, that channel will be chosen
    // No else if on condition '5' since there are only 3 inputs char channel can be
    if(channel == '4') {
        // A4 ADC input select; Vref=AVCC
        ADCMCTL0 |= ADCINCH_4;
    }
    else if (channel == '3') {
        // A3 ADC input select; Vref=AVCC
        ADCMCTL0 |= ADCINCH_3;
    }
    else {
        // A5 ADC input select; Vref=AVCC
        ADCMCTL0 |= ADCINCH_5;
    }


    ADCFinished = 0;
    // Sampling and conversion start
    ADCCTL0 |= ADCENC | ADCSC;
    while(ADCFinished != 1);
    return ADCResult;

}

// ADC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC_VECTOR))) ADC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
    {
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG:
            break;
        case ADCIV_ADCTOVIFG:
            break;
        case ADCIV_ADCHIIFG:
            break;
        case ADCIV_ADCLOIFG:
            break;
        case ADCIV_ADCINIFG:
            break;
        case ADCIV_ADCIFG:
            ADC_Result = ADCMEM0;
            ADCFinished = 1;
            __bic_SR_register_on_exit(LPM0_bits);            // Clear CPUOFF bit from LPM0
            break;
        default:
            break;
    }
}