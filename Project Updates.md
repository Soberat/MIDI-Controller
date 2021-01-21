# Week 5 - part 2 

Now it's time to use I2S! I2S is short for Inter-IC Sound. It's basically I2C tuned to work better for sound applications.

In our case it is super easy to use I2S - we just use [Teensy Audio Library](https://www.pjrc.com/teensy/gui/index.html?info=AudioOutputI2S) with the included design tool, which for us just uses an USB input and I2S hardware stereo output. Few lines of code and we have a perfectly working native USB Audio interface! We can even change the name that is displayed natively in the operating system. 

![](https://github.com/Soberat/MIDI-Controller/blob/main/Images/Interface.png)

How does it work? Well, using a single I2S interface we are limited to 2 outputs and 2 inputs, and our PCM5102 module only has outputs. However, they work perfectly as we'd expect. Here's a showcase of a testing setup:

![](https://i.imgur.com/gfrQjFE.jpg)
Do you think this isn't clear and is messy? We agree, so let's take look at a simplified diagram:

![](https://i.imgur.com/f34xTCz.png)

Basically, we play audio on another PC throught our I2S interface, it is received as input by another audio interface, which is passed to another computer. On the second computer we can observe the signal strength:

![](https://i.imgur.com/VKN8x8e.gif)

Now, what is the sound quality of the module? It's good enough for usage with a PC, however it has a couple problems:
- Noise - interface and our board elements shouldn't share ground, otherwise they will introduce a lot of noise
- Power - it can easily power some desktop speakers, however when talking professional applications this has a small voltage supply range and high noise. It could be used only as an audio interface with very low output voltages, then it should be amplified by proper audio equipment.

Otherwise, this is exactly what we expected from this module and it seems like a compelling option to be implemented in the final project.

# Week 5
We applied what we achieved earlier and now we have our track information on our displays :)

[Youtube link since gif was too large (sound not available due to copyright reasons)](https://www.youtube.com/watch?v=enf4cnDGF1E&feature=youtu.be)

It was quite easy to do thanks to Adafruit display libraries, and our I2C multiplexer requires only initialization and a simple transaction to work properly. Also, as simple as it may seem, consistent and elegant line breaking is really hard to implement - [here's](http://defoe.sourceforge.net/folio/knuth-plass.html) a nice writeup on Knuth-Plass line breaking algorithm that we would like to implement in the project at some point.


# Week 4
After a few weeks worth of tedious debugging we have completed probably the most important part of the project - debugging of the Traktor Numark Mixdeck proprietary protocol.
It is important because this information we're acquiring here is not available as an output option to any custom MIDI controller like ours. This makes our project a truly unique one!
Here we can observe how changes in the program are printed out in the serial monitor below:
![](https://github.com/Soberat/MIDI-Controller/blob/main/Images/numark.gif)

We can see the most important information being updated message-by-message (although we display debug information only every 1 second to reduce clutter). Loading a track into a deck will notify the deck, and it will start scanning the System Exclussive messages for data. Other data is sent over typical MIDI messages, however some are coded, like BPM or tempo information. 

Sometime later this week we will be applying all of this to display information on our SSD1306 displays.

# Week 2 & 3

Over the holiday period we managed to achieve full LED functionality. Here's a quick showcase:
![](https://github.com/Soberat/MIDI-Controller/blob/main/Images/leds.gif)

What we're seeing here are VU meters - their function is to visualise whether the sound level of the output is correct (in reference to a specific volume level that professional audio equipment uses). Green LEDs signal everything is good, yellow is a bit too much and red is critically bad.

Following an example from the Control Surface library we create a range handler. It watches a specific range of MIDI notes and is it is called when a note in that range is received. This means all of our MIDI outputs from Traktor have to be in a sequence (currently it is 0 - 19). 
We receive the information about the volume levels straight from Traktor as a value in range 0-127 and we can display it linearly to visualise the levels.

There is also a phase meter implemented, which shows how desynchornised tracks are. Other LEDs notify whether a track is playing on a given deck and another one is a red warning LED showing that a track is about to end.

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
