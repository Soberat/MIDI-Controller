#include <FastLED.h>
#include <Encoder.h>
#include <Control_Surface.h>
#include "TrackDataHandler.cpp"

// The data pin with the strip connected.
constexpr uint8_t ledpin = 0;
// Total number of leds connected to FastLED
constexpr uint8_t numleds = 44;
// How many CCs are sent to control LEDs
constexpr uint8_t ledCallbacks = 20;

TrackDataHandler deckA(0x02, 0xB0);
TrackDataHandler deckB(0x22, 0xB1);

CRGB colorOff = CRGB(0, 0, 0);
CRGB vuColors[8] = {CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Yellow, CRGB::Yellow, CRGB::Red};

//Track end warnings don't have to be synchronized between decks, so we need 2 separate timers
//This value is arbitarily chosen to match Traktor Pro's flashing interval
Timer<millis> timerEndA = 790;
Timer<millis> timerEndB = 790;

//Timer for serial debugging
Timer<millis> second = 1000;

//Variables containing information if Track End Warning is active for a deck
bool trackEndA = false;
bool trackEndB = false;

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


// Custom callback to handle incoming note events and control the LEDs
class NoteCCFastLEDCallbackRGB : public SimpleNoteCCValueCallback {
    public:
        NoteCCFastLEDCallbackRGB(CRGB *ledcolors) : ledcolors(ledcolors) {}
                        
        // Called once upon initialization.
        void begin(const INoteCCValue &input) override { updateAll(input); }

            
        /*
         * This function has the job of controlling WS2812 Neopixels
         * In this case we are using multiple Neopixels connected in series to reduce pin usage on the uC
         * They are connected as :
         * State A -> TrackEnd A -> Volume A-> Phase -> Volume B-> Volume Master -> State B-> TrackEnd B
         *  0    ->     1    ->       2       ->    3    ->     4      ->    5    ->      6     ->    7
         * Declaration of CustomNoteValueLED below defines a range of notes starting at a given note to be received and handled by the class.
         * Velocity of the Nth note is stored as index-1 in the input variable
         * Notes need to be one after another for this to work. 
         * 
         * It is crucial that the leds are not cleared with FastLED.clear(), as this introduces a lot of flickering
         * 
         * On Arduino Uno some notes may stay on even after a note signals to turn it off. No idea what's causing this, but the midi note is sent correctly.
         */
        void update(const INoteCCValue &input, uint8_t index) override {
            int value = input.getValue(index);
              switch (index) {
                  case 0:
                      if (value == 1) ledcolors[0] = CRGB::Green;
                      else ledcolors[0] = colorOff;
                      break;
                  case 1:
                      //Case 1 and 7 are responsible for alternating TrackEnd LEDs. Since NoteOn for the warning is received only once, this just tells an external function (trackEndLEDS()) to take care of it in the program loop
                      if (value == 1) {
                        trackEndA = true;
                        timerEndA.begin();
                      }
                      else trackEndA = false;
                      break;
                  case 2 :  //this strip is vertically inverted relative to others, so the code is a bit different
                      for (int i = 7; i >= 0; i--) if (value > 16*i) {
                          ledcolors[9-i] = vuColors[i];
                      } else {
                          ledcolors[9-i] = colorOff;
                      }
                      break;
                  case 3 :
                      //This is responsible for displaying the phase the same way Traktor does, as in center is no phase shift.
                      //Since midi values are 0-127 the code is quite ugly, but it works ;)                  
                      for (int i = 0; i <= 7; i++) ledcolors[i+10] = colorOff;
                      if (value == 63 || value == 0) break; //default value is 63, which means so phase shift. 0 is the default when the device starts without MIDI input, so we ignore it as well
                      else if (value >= 0  && value < 15) for (int i = 0; i <= 3; i++) ledcolors[i+10] = CRGB::Orange;
                      else if (value >= 15 && value < 31) for (int i = 1; i <= 3; i++) ledcolors[i+10] = CRGB::Orange;
                      else if (value >= 31 && value < 47) for (int i = 2; i <= 3; i++) ledcolors[i+10] = CRGB::Orange;
                      else if (value >= 47 && value < 63) ledcolors[13] = CRGB::Orange;
                      else if (value > 63 && value <= 79) ledcolors[14] = CRGB::Orange;
                      else if (value > 79 && value <= 95) for (int i = 4; i <= 5; i++) ledcolors[i+10] = CRGB::Orange;
                      else if (value > 95 && value <= 111) for (int i = 4; i <= 6; i++) ledcolors[i+10] = CRGB::Orange;
                      else if (value > 111) for (int i = 4; i <= 7; i++) ledcolors[i+10] = CRGB::Orange;
                      break;
                  case 4 :
                      for (int i = 0; i <= 7; i++) if (value > 16*i) {
                          ledcolors[18+i] = vuColors[i];
                      } else {
                          ledcolors[18+i] = colorOff;
                      }
                      break;
                  case 5 :
                      for (int i = 0; i <= 7; i++) if (value > 16*i) {
                          ledcolors[26+i] = vuColors[i];
                      } else {
                          ledcolors[26+i] = colorOff;
                      }
                      break;
                  case 6:
                      if (value == 1) ledcolors[34] = CRGB::Green;
                      else ledcolors[34] = colorOff;
                      break;
                  case 7:
                      if (value == 1) {
                        trackEndB = true;
                        timerEndB.begin();
                      }
                      else trackEndB = false;
                      break;
              }
        }        
    private:
        // Pointer to array of FastLED color values for the LEDs
        CRGB *ledcolors;
};

// Create a type alias for the MIDI Note Input Element that uses
// the custom callback defined above.
template <uint8_t RangeLen>
using CustomNoteValueLED = GenericNoteCCRange<MIDIInputElementCC, RangeLen, NoteCCFastLEDCallbackRGB>;
// Define the array of leds.
Array<CRGB, numleds> leds = {};

CustomNoteValueLED<ledCallbacks> midiled = {ledpin, leds.data};

USBMIDI_Interface midi;

void trackEndLEDS() {
    if (trackEndB && timerEndB) {
        if (leds[35] == colorOff) leds[35] = CRGB::Red;
        else leds[35] = colorOff;
    } else if (!trackEndB) {  //ensure switching off after NoteOff event
        leds[35] = colorOff;
    }

    if (trackEndA && timerEndA) {
        if (leds[1] == colorOff) leds[1] = CRGB::Red;
        else leds[1] = colorOff;
    } else if (!trackEndA) {
        leds[1] = colorOff;
    }
}


bool sysExMessageCallback(SysExMessage se) {
    //Making sure the data is coming from Traktor and that length corresponds to title data message length (6 ascii + 16 id)
    if (se.data[0] == 0xF0 && se.data[se.length-1] == 0xF7 && se.length == 22) {
        if (se.CN == 1) deckA.receive(se);  //We assign different virtual devices to both decks, so based on that we can tell which deck should recieve a message
        else if (se.CN == 2) deckB.receive(se);
    }
    return false;
}

bool channelMessageCallback(ChannelMessage cm) {
    if (cm.data1 >= 32 && cm.data1 <= 77) {
        if (cm.CN == 1) {
            deckA.receive(cm);
        } 
        else if (cm.CN == 2) {
            deckB.receive(cm);
        }
    }
    return false;
}

void setup() {
    //We set our custom callbacks to receive special messages
    Control_Surface.setMIDIInputCallbacks(channelMessageCallback, sysExMessageCallback, nullptr);
    Control_Surface.begin();

    FastLED.addLeds<NEOPIXEL, ledpin>(leds.data, numleds);
    FastLED.setCorrection(TypicalPixelString);
    FastLED.setBrightness(32);

    //Begin timer but not immediately
    //Note: this function may not be available in Control_Surface library and should be added from a newer version of Adruino Helpers
    second.beginNextPeriod();
}

void loop() {
    Control_Surface.loop();
    trackEndLEDS();
    
    //Print debug data to make it more readable in a serial monitor 
    if (second) {
        Serial << dec << "Deck A: Title: " << deckA.getTitle().replace("\n", " - ") << "  " << "BPM: " << deckA.getBPM() << "  " << "Time: " << (deckA.getTime().minutes < 10 ? "0" : "") << deckA.getTime().minutes << ":" << (deckA.getTime().seconds < 10 ? "0" : "") << deckA.getTime().seconds << "  " << "Tempo d: " << deckA.getTempo() << endl;
        Serial << dec << "Deck B: Title: " << deckB.getTitle().replace("\n", " - ") << "  " << "BPM: " << deckB.getBPM() << "  " << "Time: " << (deckB.getTime().minutes < 10 ? "0" : "") << deckB.getTime().minutes << ":" << (deckB.getTime().seconds < 10 ? "0" : "") << deckB.getTime().seconds << "  " << "Tempo d: " << deckB.getTempo() << endl << endl;
    }
    
    FastLED.show();
}
