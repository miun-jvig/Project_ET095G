#include "RGBled.h"

// constructor with initializer
RGBled::RGBled(PinName redpin, PinName greenpin, PinName bluepin)
: _redPin(redpin), _greenPin(greenpin), _bluePin(bluepin) {
    
}

/*
    Colour Ramping for Data Visualisation, algorithm written by Paul Bourke
    (http://paulbourke.net/miscellaneous/colourspace/):
    
    Changes the RGB values of RGBled::colour (red, green, blue) given a scalar
    startValue in the range [minValue, maxValue]. The colour is clipped at the end of the
    scales if startValue is outside the range.
*/

void RGBled::setColourRange(float startValue, float minValue, float maxValue){
    colour.red = 1.0;
    colour.green = 1.0;
    colour.blue = 1.0;
    float deltaColour;

    if (startValue < minValue){
        startValue = minValue;
    }
    if (startValue > maxValue){
        startValue = maxValue;
    }
    deltaColour = maxValue - minValue;

    if (startValue < (minValue + 0.25 * deltaColour)) {
        colour.red = 0;
        colour.green = 4 * (startValue - minValue) / deltaColour;
    } 
    else if (startValue < (minValue + 0.5 * deltaColour)) {
        colour.red = 0;
        colour.blue = 1 + 4 * (minValue + 0.25 * deltaColour - startValue) / deltaColour;
    } 
    else if (startValue < (minValue + 0.75 * deltaColour)) {
        colour.red = 4 * (startValue - minValue - 0.5 * deltaColour) / deltaColour;
        colour.blue = 0;
    } 
    else {
        colour.green = 1 + 4 * (minValue + 0.75 * deltaColour - startValue) / deltaColour;
        colour.blue = 0;
    }
}

/*
    Inverting the values since the RGB LED is a common anode ("0" is on, "1" is off).
*/
void RGBled::write(float red, float green, float blue){
    _redPin =  1.0 - red;
    _greenPin = 1.0 - green;
    _bluePin = 1.0 - blue;
}