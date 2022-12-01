#include "mbed.h"

class RGBled{
public:
    // Parameterised constructor
    RGBled(PinName redpin, PinName greenpin, PinName bluepin);
    
    struct Colour{
        float red;
        float green;
        float blue;
    };
    
    void setColourRange(float startValue, float maxValue, float minValue); 
    void write(float red, float green, float blue);
    Colour getColour(){ return colour; }
private:
    // Private declarations for RGBled, three separate PwmOut.    
    PwmOut _redPin;
    PwmOut _greenPin;
    PwmOut _bluePin;
    
    Colour colour;
};