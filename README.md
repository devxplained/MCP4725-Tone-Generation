# MCP4725 Tone Generation
This is an example to show how to use the MCP4725 together with an Arduino to generate tones.
The MCP4725 is a 12-bit DAC form Microchip that can be controlled via I2C.

The example play the beginning of Beethoven's Ode to Joy, which is also known as the European Hymn.
It uses the [Adafruit's MCP4725 Arduino library](https://github.com/adafruit/Adafruit_MCP4725)

## The Tone Generation Process
The example outputs each tone as a sine wave. It tries to match the specified frequency, however the example is not tuned for maximum accuracy.
It uses a simple calibration function that determines how long it takes to transmit a sample to the DAC via I2C. This information is later used to determine how many samples per period can be outputted while still matching the frequency. The number of samples per sine wave period will scale automatically with the specified frequency. For a 1 Hz signal the sine wave will be outputted at a higher accuracy than for a higher frequency signal. The number of samples per sine wave period will always be a multiple of four to ensure that the most characteristic points of the sine wave (maximum, minimum and the two zero crossings) are always outputted correctly.
The samples are precalculated and stored in a buffer before they are outputted as the Arduino is not fast enough for calculating the values on-the-fly.

**Note**  
If you need more exact timings could just calculate the amount of possible samples per period with a bit of safe margin and then use a timer interrupt or the micros() function instead of delayMicroseconds() while outputing the precalculated samples.

## References
* [Manufacturer's Website](https://www.microchip.com/wwwproducts/en/en532229)
* [MCP4725 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/22039d.pdf)
* [Adafruit MCP4725 Arduino Library](https://github.com/adafruit/Adafruit_MCP4725)
