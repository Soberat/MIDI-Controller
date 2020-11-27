# MIDI-Controller
Cortex-M4 based Musical Instrument Digital Interface project

Authors:
Mirosław Wiącek - @Soberat

Łukasz Kowalczyk

![alt text](https://www.pjrc.com/teensy/teensy32_front_small.jpg "Teensy 3.2")

This project is based around a Teensy 3.2 - a Cortex-M4 equipped board in a very small form factor. It has multiple features, including:
- native USB MIDI support including up to 16 virtual cables (essentially 16 virtual devices),

- a hardware I2S interface for 2-channel USB audio

- 64K of RAM allowing us to drive 2 OLED I2C displays,

- a clock as fast as 120MHz.

All of those features and more allow us to create a high performance, low latency MIDI controller without compromises.

Other parts used in the project:

- 2 SSD1306 OLED displays:
![alt text](https://ae01.alicdn.com/kf/H0a2597f7134d42f89d20ad3b2fd67cafQ.jpg "SSD1306")

- TCA9548A I2C multiplexer (required due to displays using the same address):
![alt text](https://ae01.alicdn.com/kf/H84c3bcc2504e4c5182b54b8e419428852.jpg "TCA9548A")

- CD74HC4067 multiplexer due to large amount of inputs:
![alt text](https://ae01.alicdn.com/kf/HTB1FVaNeL1H3KVjSZFBq6zSMXXae.jpg "CD74HC4067")

- PCM5102 - an I2S audio interface
![alt text](https://ae01.alicdn.com/kf/HTB1lS2hUMDqK1RjSZSyq6yxEVXaA.jpg "PCM5102")

- WS2812 addressable RGB LEDs in two forms - either single LED or 8:
![alt text](https://ae01.alicdn.com/kf/HTB11Oi7TxnaK1RjSZFtq6zC2VXaH.jpg?width=1000&height=1000&hash=2000 "WS2812 1x")
![alt text](https://botland.com.pl/59565-large_default/listwa-led-rgb-ws2812-5050-x-8-diod-53mm.jpg "WS2812 8x")

- assorted tactile buttons, potentiometers and rotary encoders as typical input devices
