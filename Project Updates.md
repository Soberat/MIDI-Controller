# Week 1

During the first week of work on controller we decided to start with the basics - our output elements, such as:

- Play/Pause buttons,
- Cue buttons
- Volume/Gain potentiometers,
- Crossfader potentiometer
- Load buttons 
- Modifier buttons
- Browser rotary encoder.

Here they are marked on the breadboard model:
![Pic](https://github.com/Soberat/MIDI-Controller/blob/main/Images/Outputs.jpg)

## Code

Currently the code is extremely simple thanks to the Control Surface library - we just declare our interface (in our case a USB MIDI interface), multiplexer and outputs, such as CCButton (CC stands for Control Change and is one of 3 types. The message structure is still the same as any other MIDI message, therefore it isn't important whether we use the Note, CC or PB type) and we call begin() and loop() library functions. 
Parameters for declaring an outputs are:
- input pins - depending on the type of device there might be 1 pin (ex. button) or more (ex. rotary encoder),
- structure describing which note and channel this device will report its' status on - for example note 77 on channel 1 will be {77, CHANNEL_1}

Now every time Control_Surface.loop() is called all our elements are read and if they have new data, a MIDI message is sent.

## Issues

### Grounding
Currently the project is fully assembled on a breadboard. While this is good for prototyping, this introduces a lot wires and as a result - noise. Since all elements share the same ground via the breadboard power lines there is some unwanted behavior. For example, moving one potentiometer may affect the others, even though they are stationary.

### ADC reference voltage
Teensy 3.2 operates at 3.3 volts. Most of our components would work perfectly fine in that range, however WS2812B LEDs would not. Since we would have to step up voltage before each LED it is easier for us to power everything off the USB voltage, which is 5V. We can do this since Teensy 3.2 has 5V tolerant pins, however the ADC reference voltage is still 3.3V. As a result, our potentiometers don't always reflect the software value of the faders. This is something that will be fixed when this project will be printed on a PCB, however it would complicate things too much at the current stage of the project.
