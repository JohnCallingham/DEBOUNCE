#include "Debounce.h"

Debounce::Debounce(uint8_t inputPin, uint16_t sampleTimemS, uint16_t lowSamples, uint16_t highSamples) {
  this->inputPin = inputPin;
  this->sampleTimemS = sampleTimemS;
  this->lowSamples = lowSamples;
  this->highSamples = highSamples;
}

void Debounce::loop() {
  counter++; // Used to calculate how many calls to loop() are required before sample() is called.

  // Implement a non blocking delay for sampleTimemS.
  if (millis() < nextUpdate) return;
  nextUpdate = millis() + sampleTimemS;

  // sampleTimemS has passed since the last call to sample().
  sample();
}

void Debounce::sample() {

  // Serial.printf("\n%d in sample(), counter = %d", millis(), counter);
  counter = 0;

   // Take a sample of the state of inputPin.
  inputState = digitalRead(inputPin);

  // Run the debounce process with this sample.
  outputState = process(inputState);
}

int Debounce::process(int inputState) {
  /**
   * If the high timer is running, decrement it.
   * If the high timer has counted down to 0,
   *  and the input is still high, set the output high.
   */
  if (highTimer > 0) {
    highTimer--;
    if ((highTimer == 0) && (inputState == 1)) {
      outputState = 1;
    }
  }

  /**
   * If the low timer is running, decrement it.
   * If the low timer has counted down to 0,
   *  and the input is still low, set the output low.
   */
  if (lowTimer > 0) {
    lowTimer--;
    if ((lowTimer == 0) && (inputState == 0)) {
      outputState = 0;
    }
  }

  /**
   * If the high timer is not running, and the output state is low,
   *  and the input state goes high, start the high timer.
   */
  if ((highTimer == 0) && (outputState == 0) && (inputState == 1)) {
    highTimer = highSamples;
  }

  /**
   * If the low timer is not running, and the output state is high,
   *  and the input state goes low, start the low timer.
   */
  if ((lowTimer == 0) && (outputState == 1) && (inputState == 0)) {
    lowTimer = lowSamples;
  }

  /**
   * If there is a transition and either timer is running,
   *  restart that timer.
   */
  if (inputState != lastSampledState) {
    if (highTimer > 0) {highTimer = highSamples;}
    if (lowTimer > 0) {lowTimer = lowSamples;}
  }

  /**
   * Store this sample's input state for the next sample.
   */
  lastSampledState = inputState;

  return outputState;
}
