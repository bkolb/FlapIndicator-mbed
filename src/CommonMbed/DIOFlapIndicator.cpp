#include "DIOFlapIndicator.h"


#define WRITE_LED(LED) \
    leds.LED.write(static_cast<int>(newState.LED))



DIOFlapIndicator::DIOFlapIndicator(LedMapping& leds):
    AbstractFlapIndicator(),
    leds(leds) 
{}

        
void DIOFlapIndicator::updateState(flapState_t newState){
    WRITE_LED(led1);
    WRITE_LED(led2);
    WRITE_LED(led3);
    WRITE_LED(led4);
    WRITE_LED(led5);
    WRITE_LED(ledL);
}