#include <Encoder.h>
#include <Control_Surface.h>

USBMIDI_Interface midi;

//Declare all output elements
CD74HC4067 mux = {A6, {7, 6, 5, 4}};

CCPotentiometer potVolumeA = {mux.pin(13), {56, CHANNEL_1}}; 
CCPotentiometer potGainA   = {A2, {57, CHANNEL_1}};

CCButton buttonPlayA = {mux.pin(15),{62, CHANNEL_1}};
CCButton buttonCueA = {mux.pin(14),{63, CHANNEL_1}};
CCButton buttonLoadA = {mux.pin(11),{64, CHANNEL_1}};

CCPotentiometer potVolumeB = {mux.pin(2), {67, CHANNEL_1}};
CCPotentiometer potGainB   = {A0, {68, CHANNEL_1}};

CCButton buttonPlayB = {mux.pin(1),{73, CHANNEL_1}};
CCButton buttonCueB  = {mux.pin(0),{74, CHANNEL_1}};
CCButton buttonLoadB = {mux.pin(4),{75, CHANNEL_1}};

CCPotentiometer potXfader  = {mux.pin(3), {78, CHANNEL_1}};
CCPotentiometer potVolumeMaster  = {A1, {79, CHANNEL_1}};

CCButton buttonModifier1 = {1, {66, CHANNEL_1}}; 
CCButton buttonModifier5 = {mux.pin(12), {81, CHANNEL_1}}; //browser encoder pushbutton, used only for browser navigation.
CCRotaryEncoder encoderBrowser = {{2, 3}, {83, CHANNEL_1}};

void setup() {
    Control_Surface.begin();
}

void loop() {
    Control_Surface.loop();
}
