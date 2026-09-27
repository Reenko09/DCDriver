#ifndef DCDriver_H
#define DCDriver_H

#include <Arduino.h>

class DCDriver{
    private:
        enum DriverState {UNINITIALIZED, CLOCKWISE, COUNTER_CLOCKWISE, BRAKING, STOPPED};
        DriverState _driverState {UNINITIALIZED};

        uint8_t _enableValue {0};
        uint8_t _enablePin {255};

        uint8_t _inputPin1 {255};
        uint8_t _inputPin2 {255};
    
    public:
        //Default constructor
        DCDriver() = default;

        /**
         * @brief Start the class param
         * @param motorInputPin1 Set the GPIO to control Driver InputPin A
         * @param motorInputPin2 Set the GPIO to control Driver InputPin B
         * @param enablePin [OPTIONAL] Set the PWM control pin, if it have a one
         */
        void begin(uint8_t motorInputPin1, uint8_t motorInputPin2, uint8_t enablePin = 255);
        
        /**
         * @brief Update the motor speed.
         * @param enableValue Speed value [0 - 255].
         */
        void setSpeed(uint8_t enableValue);
        
        /**
         * @brief Turn on the clockwise activation with a custom speed.
         * @param enableValue Motor speed value [0 - 255] (PWM).
         */
        void clockwise(uint8_t enableValue);
        
        /**
         * @overload
         * @brief Turn on the clockwise activation with the last set speed.
         * @note Speed defaults to 0 until setSpeed() or the parameterized clockwise() / counterClockwise() is called at least once.
         */
        void clockwise();
        
        /**
         * @brief Turn on the counter-clockwise activation with a custom speed.
         * @param enableValue Motor speed value [0 - 255] (PWM).
         */
        void counterClockwise(uint8_t enableValue);
        
        /**
         * @overload 
         * @brief Turn on the counter-clockwise activation with the last set speed.
         * @note Speed defaults to 0 until setSpeed() or the parameterized clockwise() / counterClockwise() is called at least once.
        */
        void counterClockwise();
        
        /**
         * @brief Active brake for the motor, acting by causing a short in the motor on itself coil making it stop fast 
         */
        void brake();

        /**
         * @brief Passive brake for the motor, letting it stop slowly
         */
        void stop();

        /**
         * @brief Return if the Enable pin is assigned
         * @return true if an enable pin was set via begin(); false otherwise 
         * @note Enable pin must be assigned as the 3° param on begin(a, b, en) method 
         */
        bool isEnablePinAssigned();

};

#endif