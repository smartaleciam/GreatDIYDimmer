/*
  MIDI note player

  This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
  If this circuit is connected to a MIDI synth, it will play the notes
  F#-0 (0x1E) to F#-5 (0x5A) in sequence.

  The circuit:
  - digital in 1 connected to MIDI jack pin 5
  - MIDI jack pin 2 connected to ground
  - MIDI jack pin 4 connected to +5V through 220 ohm resistor
  - Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

  created 13 Jun 2006
  modified 13 Aug 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Midi
*/

//void loop1() {
//  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
//  for (int note = 0x1E; note < 0x5A; note ++) {
//    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
//    noteOn(0x90, note, 0x45);
//    delay(100);
//    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
//    noteOn(0x90, note, 0x00);
//    delay(100);
//  }
//}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
//void noteOn(int cmd, int pitch, int velocity) {
//  Serial3.write(cmd);
//  Serial3.write(pitch);
//  Serial3.write(velocity);
//}



//******** Teensy MIDI Color Ring ********
// Uses 16 LED Neopixel Ring from Adafruit as written - change NUM_LEDS and divisor of note/8 to adapt
// Hacked together by Dave Pentecost - to use palettes, MIDI input, velocity change of color, notes on different LEDs
//
/*
#include "FastLED.h" //We are using the FastLED library instead of the Adafruit Neopixel library, to work better with Teensy

#define LED_PIN     5
#define NUM_LEDS    16
#define BRIGHTNESS  100
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

//Palette setup
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 RainbowColors;
extern const TProgmemPalette16 RainbowColors_p PROGMEM;

//Set variables for velocity (color) and note (LED position on ring)
uint8_t NewVelocity;
uint8_t NewNote;


void setup()
{
  //MIDI handles to set up actions on note on and note off
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
  
  //Setting up LED info for the FastLED library
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  currentPalette = RainbowColors_p;
  currentBlending = BLEND;
  
  //Turn on one red LED to show sketch has started
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);
  
  //Print OK for start
  Serial.begin(115200);
  Serial.print("Okay Okay Okay");
}


//***** Running program loop *****
void loop()
{
  //This is all we need, since we have actions set when MIDI is read
  usbMIDI.read();
}

//******************************************
//Functions defined below


//What to do if MIDI note on is read
void OnNoteOn(byte channel, byte note, byte velocity)
{
  NewNote = note/8;
  //this reduces notes to 16 LEDs - change to suit different setup
  NewVelocity = 128 - velocity; // do this so palette goes from blue to red with higher velocity
  
  VelocityColorFromPalette( NewVelocity); //Go do the routine we have defined below, to set up color depending on velocity
  
  FastLED.show(); //Turn on that LED when you get back from the color routine
 
  //Uncomment lines below to print values to Serial Monitor if needed 
  //Serial.print("Note On, ch=");
  //Serial.print(channel, DEC);
  //Serial.print(", note=");
  //Serial.print(note, DEC);
  //Serial.print(", velocity=");
  //Serial.print(velocity, DEC);
  //Serial.println();
}

//What to do if MIDI note off is read
void OnNoteOff(byte channel, byte note, byte velocity)
{
  leds[note/8] = CRGB::Black; //Set color to black instead of going to the color from velocity routine
  FastLED.show(); //turn off that LED by making it black
}

void VelocityColorFromPalette( uint8_t colorIndex)
{
  uint8_t brightness = BRIGHTNESS; //This takes the brightness from the BRIGHTNESS variable we set at the top
  
  colorIndex = NewVelocity; //This makes the colorIndex in the FastLED ColorFromPalette command follow our velocity
  
  leds[NewNote] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending); //Set those colors and brightness
    
}
*/

