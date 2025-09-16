#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <Arduino.h>

#define DEBOUNCE_DELAY_mS 100 // 100 mS debounce delay.

/***
 * Class Debounce provides general debounce functionality.
 * The input is by a specified input pin.
 * ??? The output is by a callback function. ???
 */
class Debounce {
  public:
    /**
     * inputPin is the pin which is to be debounced.
     * sampleTimemS is the number of mS between each sample of inputPin.
     * lowSamples is the number of samples that inputPin needs to be permanently low before a low is output.
     * highSamples is the number of samples that inputPin needs to be permanently high before a high is output.
     */
    Debounce(uint8_t inputPin, uint16_t sampleTimemS, uint16_t lowSamples, uint16_t highSamples);

    /**
     * A parameterless constructor and associated set... methods.
     */
    Debounce() {};
    void setInputPin(uint8_t inputPin) { this->inputPin = inputPin; }
    void setSampleTimemS(uint16_t sampleTimemS) { this->sampleTimemS = sampleTimemS; }
    void setLowSamples(uint16_t lowSamples) { this->lowSamples = lowSamples; }
    void setHighSamples(uint16_t highSamples) { this->highSamples = highSamples; }

    /**
     * Called repeatedly from the main program loop.
     * Calls sample() when it is time to sample the inputPin.
     */
    void loop();

    /**
     * The state after the bouncing has been removed.
     * Made public so it can be read from the main program.
     */
    int outputState;

  private:
    /**
     * Called every sampleTimemS to read the state of the input pin and determine if any output change has occurred.
     */
    void sample();

    /**
     * Is passed the state of the input pin and returns the output state.
     */
    int process(int inputState);

    int inputState; // The state of the input pin which is bouncing. 0 is low, 1 is high.
    int lastSampledState; // Used to detect if the input pin has changed state since the last sample. 0 is low, 1 is high.

    unsigned long nextUpdate = 0; // Used to ensure that sample() is called every sampleTimemS;

    uint8_t inputPin; // The pin which is to be debounced.
    uint16_t sampleTimemS = 1; // The number of mS between each sample of inputPin.
    uint16_t lowSamples = 100; // The number of samples that inputPin needs to be permanently low before a low is output.
    uint16_t highSamples = 100; // The number of samples that inputPin needs to be permanently high before a high is output.

    unsigned long counter = 0;  // Counts the number of times that process() is called before sample() is called.
    // unsigned long loopsPerSample = 0; // Keeps a ruuning total of changes to the number of loops per sample.

    uint16_t lowTimer = 0; // Counts down from lowSamples. When at zero, the output is set low.
    uint16_t highTimer = 0; // Counts down from highSamples. When at zero, the output is set high.
};

#endif
