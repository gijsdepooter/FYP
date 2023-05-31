# FYP
Developing a Single Channel Ultrasound Device

This project is being done with the Imperial College London Bioengineering Department, in collaboration with Prof Manos Drakakis and PhD Momen Kamal Tageldeen

This is a Repo for the firmware that I am developing for an US scanner.

There are a few main parts of the US hardware:

1. The Pulser 
2. The MUX
3. The VGA (voltage gain amplifier)
4. The ADC


**PULSER**

The pulser is responsible for sending high voltage pulses to the piezo transducers in the US probe. I am using the HV7361 from microchip. It takes simple 3 bit digital instructions. These controlls are sent from the raspberry pi pico using the PIO interface to achieve precise timings.

**VGA**

The VGA controlls the amplification of the US signal and corrects for an attenuation of approximately 1dB/MHz/cm in tissue. The TGC profile is set by the MCP4921 DAC, controlled over SPI.
This is a 12 bit DAC that is controlled using the PIO interface of the rapsberry pi pico to achieve the desired speed.

**ADC** 

This project uses the LTC2236, a 10 bit DAC that can sample up to 65Msps. The ADC has a parallel output. The raspberry pi zero is used to decode the parallel ouptut using DMA and the secondary memory interface (SMI). Most of the code that controlls the ADC is from https://github.com/jbentham/rpi, and merely adapted to suit the needs of the IC of choice.

**MUX**

The multiplexer unit is an optional IC to leverage the single channel architecture of this board to controll multiple transducer channels. This allows for contructing B-Mode images with linear and phased arrays.
