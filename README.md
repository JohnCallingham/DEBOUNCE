# Outline
The state of the input pin (high or low) is sampled at a regular interval.

If the input state transitions from low to high then the input must be consistenly high for a number of samples before the output is set high. The number of samples is stored in highSamples.

If the input state transitions from high to low then the input must be consistenly low for a number of samples before the output is set low. The number of samples is stored in lowSamples.

# Operation

Consider the input waveform below which shows a low to high transition with bouncing.

![low to high](assets/Low%20to%20High.png)

When the input pin is sampled and the input is high when the output is low, the high timer is started by writing the value of highSamples to highTimer. The value of highTimer is decremented by one when each sample is taken. If the value of highTimer reduces to zero, then the output is set high.

If any sample of the input pin sees a transition before the high timer has reduced to zero, then the high timer is restarted by writing the value of highSamples to highTimer. In this way the output can only be set high if the input has been high for the number of samples indicated by highSamples. When the high timer expires a check is made to ensure that the input state is still high before setting the output high.

