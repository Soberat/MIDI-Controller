# MIDI-Controller
Cortex-M4 based Musical Instrument Digital Interface project

Authors:
Mirosław Wiącek - [@Soberat](https://github.com/Soberat)\
Łukasz Kowalczyk - [@lucas6smith](https://github.com/lucas6smith)

Any updates to this project will be located in a separate file (to be created later)

![alt text](https://www.pjrc.com/teensy/teensy32_front_small.jpg "Teensy 3.2")

This project is based around a Teensy 3.2 - a Cortex-M4 equipped board in a very small form factor. It has multiple features, including:
- native USB MIDI support including up to 16 virtual cables (essentially 16 virtual devices),
- a hardware I2S interface for 2-channel USB audio,
- 64K of RAM allowing us to easily drive 2 OLED I2C displays,
- a clock as fast as 120MHz.

All of those features and more allow us to create a high performance, low latency MIDI controller without compromises. It will be used with Traktor Pro 3, a DJing program described in [Traktor Pro Overview.md](https://github.com/Soberat/MIDI-Controller/blob/main/Traktor%20Pro%20Overview.md)

We'll be using the [Control Surface library](https://github.com/tttapa/Control-Surface) licensed under [GPL-3.0 License](https://github.com/tttapa/Control-Surface/blob/master/LICENSE) because of its' capabilities related to reading System Exclusive Messages - a protocol specific message carrying information different than typilcal MIDI message - in our case it will carry information about music loaded in the given deck like artist, title, time, beats per minute (BPM).

## Roadmap:
- [ ] Implement basic input functionality - potentiometers, buttons and rotary encoders
- [ ] Add WS2812 LEDs as outputs in,
- [ ] Implement display functionality,
- [ ] Debug protocol described in [MIDI Protocol.md](https://github.com/Soberat/MIDI-Controller/blob/main/MIDI%20Protocol.md)
- [ ] Verify full project functionality

## Parts used:

- 2 SSD1306 OLED displays:
<img src="https://ae01.alicdn.com/kf/H0a2597f7134d42f89d20ad3b2fd67cafQ.jpg" alt="SSD1306" width="250" height="250">

- TCA9548A I2C multiplexer (required due to displays using the same address):
<img src="https://ae01.alicdn.com/kf/H84c3bcc2504e4c5182b54b8e419428852.jpg" alt="TCA9548A" width="250" height="250">

- CD74HC4067 multiplexer due to large amount of inputs:
<img src="https://ae01.alicdn.com/kf/HTB1FVaNeL1H3KVjSZFBq6zSMXXae.jpg" alt="CD74HC4067" width="250" height="250">

- PCM5102 - an I2S audio interface
<img src="https://ae01.alicdn.com/kf/HTB1lS2hUMDqK1RjSZSyq6yxEVXaA.jpg" alt="PCM5102" width="250" height="250">

- WS2812 addressable RGB LEDs in two forms - either single LED or 8:
<img src="https://ae01.alicdn.com/kf/HTB11Oi7TxnaK1RjSZFtq6zC2VXaH.jpg?width=1000&height=1000&hash=2000" alt="WS2812 1x" width="250" height="250">
<img src="https://botland.com.pl/59565-large_default/listwa-led-rgb-ws2812-5050-x-8-diod-53mm.jpg" alt="WS2812 8x" width="250" height="250">

- assorted tactile buttons, potentiometers and rotary encoders as typical input devices
