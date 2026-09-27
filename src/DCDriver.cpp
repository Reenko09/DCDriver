#include "DCDriver.h"


void DCDriver::begin(uint8_t motorInputPin1, uint8_t motorInputPin2, uint8_t enablePin) 
{
    // The function will not execute if it had alread begin before
    if (_driverState != UNINITIALIZED) return;

    _inputPin1 = motorInputPin1;
    _inputPin2 = motorInputPin2;
    _enablePin = enablePin;

    pinMode(_inputPin1, OUTPUT);
    pinMode(_inputPin2, OUTPUT);

    if (enablePin != 255){
        _enableValue = 0;
        pinMode(_enablePin, OUTPUT);
        analogWrite(_enablePin, 0);
    }
    else
        _enableValue = 255;
    
    //Set the first driverState after the object begin
    stop();
}

void DCDriver::setSpeed(uint8_t enableValue){
    // Saves the speed new value on class variable
    if ( _enableValue == enableValue) return; 
    _enableValue = enableValue;

    // Update the pin write if the motor state, if it applies to the present driver state
    if (isEnablePinAssigned() && (_driverState == CLOCKWISE || _driverState == COUNTER_CLOCKWISE))
        analogWrite(_enablePin, _enableValue);
}

void DCDriver::clockwise(uint8_t enableValue) {
    // If the motor is already on this orientation AND with this same speed, quit the function
    if (_driverState == CLOCKWISE && _enableValue == enableValue) return;
    
    _enableValue = enableValue;
    _driverState = CLOCKWISE;

    digitalWrite(_inputPin1, LOW);
    digitalWrite(_inputPin2, HIGH);
    if (isEnablePinAssigned()) 
        analogWrite(_enablePin, _enableValue);
}
void DCDriver::clockwise() { clockwise(_enableValue); }             

void DCDriver::counterClockwise(uint8_t enableValue) {
    // If the motor is already on this orientation AND with this same speed, quit the function
    if (_driverState == COUNTER_CLOCKWISE && _enableValue == enableValue) return;
    
    _driverState = COUNTER_CLOCKWISE;
    _enableValue = enableValue;

    digitalWrite(_inputPin1, HIGH);
    digitalWrite(_inputPin2, LOW);
    if (isEnablePinAssigned()) 
        analogWrite(_enablePin, _enableValue);
}
void DCDriver::counterClockwise() {counterClockwise(_enableValue);}

void DCDriver::brake() {
    // Return if the motor is already braking
    if (_driverState == BRAKING) return;
    
    _driverState = BRAKING;

    digitalWrite(_inputPin1, HIGH);
    digitalWrite(_inputPin2, HIGH);
    if ( isEnablePinAssigned() )
        analogWrite(_enablePin, 255);
}

void DCDriver::stop() {
    // Return if the motor is already stopped
    if (_driverState == STOPPED) return;
    
    _driverState = STOPPED;

    digitalWrite(_inputPin1, LOW);
    digitalWrite(_inputPin2, LOW);
    if ( isEnablePinAssigned() )
        analogWrite(_enablePin, 0);
}

bool DCDriver::isEnablePinAssigned() {
    return _enablePin != 255;
}
