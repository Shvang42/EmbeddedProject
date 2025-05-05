/**
main.c
Author: Shivang Patel, Phillip Amaro

Main method for Residential Boiler System

Last Revision: 3/4/25

*/


#include <msp430.h>
#include "intrinsics.h"
#include "sensors.h"
#include "RGBLED.h"
#include "solenoid.h"
#include "callForHeat.h"
#include "ignitorLED.h"
#include "servo.h"

bool idle = true;
bool spark = false;

int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;               

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port setting
    PM5CTL0 &= ~LOCKLPM5;                   
    
    initSensorsADC();
    initRGB();
    initSolenoid();
    initServo();
    initCFH();
    initIgnitorLED();

    setLedState("idle");
    while(1) {
        if(callForHeatCheck()) {
            idle = false;
            setLedState("not idle");
            ignitionProcess();
        }
    }
    
}

static void ignitionProcess() {
    while(idle == false) {
        // timer started, spark on and open pilot valve, then check for flame
        // timer on
        spark = true;
        pilotOn();
        if(readThermocouple()) {
            // turn ignitor led on
            flamePresent();
            spark == false;
            servo(100); // open main gas valve to 100%
            __delay_cycles(2000); // wait 2 seconds for flame stabilization
            unsigned int flameLosses = 0;
            while(callForHeatCheck()) {
                if(readThermocouple() == false) {
                    flameLost();
                    pilotOff();
                    servo(0);
                    flameLosses++;
                    for(int i = 0; i < 6; i++) {
                        if(readThermocouple()){
                            flamePresent();
                            flameLosses = 0;
                            break;
                        }
                        else {
                            flameLost();
                            flameLosses++;
                        }
                    }
                    if(flameLosses > 5) {
                        // delay 5 mins
                        __delay_cycles(50000);
                        ignitionProcess();
                    }
                    else {
                        ignitionProcess();
                    }
                }
            }
            flameLost();
            pilotOff();
            servo(0);
            setLedState("idle");
            idle = true;
        }
        else {
            flameLost();
            // timer off
            spark = false;
            pilotOff();
            // 5 min delay and retry
            __delay_cycles(50000);
            ignitionProcess();
        }

    }
}