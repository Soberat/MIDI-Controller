# MIDI Protocol

## MIDI Messages

A MIDI message consists of:
- a status byte, indicating the type of incoming message, frequently called a header,
- data byte containing the note - an identifier for a specific function of a device, ranging from 0 to 127, they all have a corresponding note on the [MIDI note chart](https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies)
- data byte containing the value - commonly called the velocity of the note.

The protocol was created with musical instruments in mind, mostly synthesizers, hence the names like note and velocity. However, the protocol evolved over the years so much that it is not standarized and the functionality we add to our own controller isn't bound to a specific note. 

## System Exclusive messages

System Exclusive messages are the reason why the protocol is still around and hasn't been phased out by a newer implementation. While it is [more complicated](https://www.midi.org/specifications-old/item/table-4-universal-system-exclusive-messages) than a basic MIDI message, it offers unlimited potential for integrating various functions in MIDI devices.

Unfortunately, we cannot create our own System Exclusive messages in Traktor Pro 3 - the implementation is a result of a controller manufacturer and Native Instruments working together. Thankfully for us, there is a proprietary protocol in Traktor Pro 3 that is available to any generic MIDI device connected.

In device configuration in Traktor Pro 3 we can choose one of available configurations - one of them is Numark Mixdeck Deck A/B. While it is designed to work with [the Numark Mixdeck](https://img.kytary.com/eshop_pl/stredni_v4/na/636706518208600000/4a20d137/63412186/numark-mixdeck.jpg) controller, there is nothing stopping us from choosing any other device as the receiving end - allowing us to receive messages with messages unavailable to any other device! While this protocol doesn't have any documentation as it is proprietary, we are happy to be the first to try and debug it.
![Imgur](https://i.imgur.com/DIh1Z6c.png)

//TODO: Add pictures with received messages
