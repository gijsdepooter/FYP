# FYP
Developing a Single Channel Ultrasound Device

This project is being done with the Imperial College London Bioengineering Department, in collaboration with Prof Manos Drakakis and PhD Momen Kamal Tageldeen

This is a Repo for the firmware that I am developing for an US scanner.

There are a few main parts of the US hardware:

1. The Pulser 
2. The MUX
3. The PGA (programmable gain amplifier)
4. The ADC


**PULSER**

The pulser is responsible for sending high voltage pulses to the piezo transducers in the US probe. The pulser hardware I have chosen is the MD1822 together with the TC7920. I am aiming to have a TX of 140Vpp at 3 level PWM.


