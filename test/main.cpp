#include <Arduino.h>
#include "Debounce.h"

/**
 * Different patterns to output.
 * Output different patterns on different pins to allow
 * complete testing without needing to make any code changes.
 */
#define PATTERN_1_PIN A0
#define PATTERN_2_PIN A1
#define PATTERN_3_PIN A2
#define PATTERN_4_PIN A3

#define DEBOUNCE_INPUT_PIN D12
#define DEBOUNCE_SAMPLE_TIME_mS 1
#define DEBOUNCE_LOW_SAMPLES 100
#define DEBOUNCE_HIGH_SAMPLES 100

// The pin for the debounced output.
#define DEBOUNCE_OUTPUT_PIN D1

// Create a Debounce object.
Debounce debounce(DEBOUNCE_INPUT_PIN, DEBOUNCE_SAMPLE_TIME_mS, DEBOUNCE_LOW_SAMPLES, DEBOUNCE_HIGH_SAMPLES);

TaskHandle_t outputPattern1Handle = NULL;
TaskHandle_t outputPattern2Handle = NULL;
TaskHandle_t outputPattern3Handle = NULL;
TaskHandle_t outputPattern4Handle = NULL;

void outputPattern1Task (void *Parameter) {
  // Pattern 1. Low to high.
  pinMode(PATTERN_1_PIN, OUTPUT);

  for (;;) {
    // Serial.printf("\n%d in pattern 1", millis());

    digitalWrite(PATTERN_1_PIN, LOW); // Output is low for 1,000 mS.
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    digitalWrite(PATTERN_1_PIN, HIGH); // Output is high for 20 mS.
    vTaskDelay(20 / portTICK_PERIOD_MS);

    digitalWrite(PATTERN_1_PIN, LOW); // Output is low for 20 mS.
    vTaskDelay(20 / portTICK_PERIOD_MS);

    digitalWrite(PATTERN_1_PIN, HIGH); // Output is high for 20 mS.
    vTaskDelay(20 / portTICK_PERIOD_MS);

    digitalWrite(PATTERN_1_PIN, LOW); // Output is low for 20 mS.
    vTaskDelay(20 / portTICK_PERIOD_MS);

    digitalWrite(PATTERN_1_PIN, HIGH); // Output is high for 500 mS.
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void outputPattern2Task (void *Parameter) {
  // Pattern 2. High to low.
  pinMode(PATTERN_2_PIN, OUTPUT);

  for(;;) {
    digitalWrite(PATTERN_2_PIN, HIGH); // Output is high for 1,000 mS.
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    digitalWrite(PATTERN_2_PIN, LOW); // Output is low for 20 mS.
    vTaskDelay(20 / portTICK_PERIOD_MS);

    digitalWrite(PATTERN_2_PIN, HIGH); // Output is high for 20 mS.
    vTaskDelay(20 / portTICK_PERIOD_MS);

    digitalWrite(PATTERN_2_PIN, LOW); // Output is low for 20 mS.
    vTaskDelay(20 / portTICK_PERIOD_MS);

    digitalWrite(PATTERN_2_PIN, HIGH); // Output is high for 20 mS.
    vTaskDelay(20 / portTICK_PERIOD_MS);

    digitalWrite(PATTERN_2_PIN, LOW); // Output is low for 500 mS.
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void outputPattern3Task (void *Parameter) {
  // Pattern 3. Low to low.
  pinMode(PATTERN_3_PIN, OUTPUT);

  for(;;) {
    digitalWrite(PATTERN_3_PIN, LOW); // Output is low for 1,000 mS.
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    // Output is high for 20 mS.
    digitalWrite(PATTERN_3_PIN, HIGH);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // Output is low for 20 mS.
    digitalWrite(PATTERN_3_PIN, LOW);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // Output is high for 20 mS.
    digitalWrite(PATTERN_3_PIN, HIGH);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // Output is low for 20 mS.
    digitalWrite(PATTERN_3_PIN, LOW);
    vTaskDelay(20 / portTICK_PERIOD_MS);
    
    // Output is high for 20 mS.
    digitalWrite(PATTERN_3_PIN, HIGH);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // Output is low for 500 mS.
    digitalWrite(PATTERN_3_PIN, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void outputPattern4Task (void *Parameter) {
  // Pattern 4. High to high.
  pinMode(PATTERN_4_PIN, OUTPUT);

  for(;;) {
    digitalWrite(PATTERN_4_PIN, HIGH); // Output is high for 1,000 mS.
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    // Output is low for 20 mS.
    digitalWrite(PATTERN_4_PIN, LOW);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // Output is high for 20 mS.
    digitalWrite(PATTERN_4_PIN, HIGH);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // Output is low for 20 mS.
    digitalWrite(PATTERN_4_PIN, LOW);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // Output is high for 20 mS.
    digitalWrite(PATTERN_4_PIN, HIGH);
    vTaskDelay(20 / portTICK_PERIOD_MS);
    
    // Output is low for 20 mS.
    digitalWrite(PATTERN_4_PIN, LOW);
    vTaskDelay(20 / portTICK_PERIOD_MS);

    // Output is high for 500 mS.
    digitalWrite(PATTERN_4_PIN, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  /**
   * Create four tasks to output four different waveform patterns on four different pins.
   * This will enable all waveforms to be tested.
   */
  xTaskCreatePinnedToCore(
    outputPattern1Task,      // Task function
    "outputPattern1",   // Task name
    10000,           // Stack size (bytes)
    NULL,            // Parameters
    1,                   // Priority
    &outputPattern1Handle,  // Task handle
    1                  // Core 1
  );

  xTaskCreatePinnedToCore(
    outputPattern2Task,      // Task function
    "outputPattern2",   // Task name
    10000,           // Stack size (bytes)
    NULL,            // Parameters
    1,                   // Priority
    &outputPattern2Handle,  // Task handle
    1                  // Core 1
  );

  xTaskCreatePinnedToCore(
    outputPattern3Task,      // Task function
    "outputPattern3",   // Task name
    10000,           // Stack size (bytes)
    NULL,            // Parameters
    1,                   // Priority
    &outputPattern3Handle,  // Task handle
    1                  // Core 1
  );

  xTaskCreatePinnedToCore(
    outputPattern4Task,      // Task function
    "outputPattern4",   // Task name
    10000,           // Stack size (bytes)
    NULL,            // Parameters
    1,                   // Priority
    &outputPattern4Handle,  // Task handle
    1                  // Core 1
  );

  pinMode(DEBOUNCE_INPUT_PIN, INPUT_PULLUP);
  pinMode(DEBOUNCE_OUTPUT_PIN, OUTPUT);
}

void loop() {
  /**
   * For testing each of the waveform pattern pins is, in turn, physically
   * connected to the debounce input pin and to the probe shown on the top oscilloscope trace.
   * The debounce output pin is connecetd to the probe shown on the lower oscilloscope trace.
   */
  debounce.loop();

  int outputState = debounce.outputState;

  digitalWrite(DEBOUNCE_OUTPUT_PIN, outputState);

}
