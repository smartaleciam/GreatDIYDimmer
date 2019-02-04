#include <Wire.h>
#include "FastLED.h"
// How many leds in your strip?
//#define NUM_LEDS 64
#define NUM_LEDS 16
#define DATA_PIN 3
#define COLOR_ORDER RGB
#define BRIGHTNESS 96
#define FRAMES_PER_SECOND  120
// Define the array of leds
CRGB leds[NUM_LEDS];

String inputString = "", RFID="loading";
boolean stringComplete = false;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void setup() 
{      uint8_t i;  int x=200; // delay in startup scroll of leds (fake loading - Delay)
  Serial.begin(115200);
  //Serial.begin(2000000);
  inputString.reserve(200);
  FastLED.addLeds<WS2811, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  FastLED.setBrightness(BRIGHTNESS); FastLED.clear();   FastLED.show();  
}

void button_light(String a,int b)
{
int coler;
//Red (0)
//Orange (32)
//Yellow (64)
//Green (96)
//Aqua (128)
//Blue (160)
//Purple (192)

Serial.println( a );
Serial.println( b );
if (a=="R") coler=0;
if (a=="O") coler=32;
if (a=="Y") coler=64;
if (a=="G") coler=96;
if (a=="A") coler=128;
if (a=="B") coler=160;
if (a=="P") coler=213;
leds[b-1] = CRGB::Black;
//      FastLED.show();
  leds[b-1] += CHSV( coler, 255, 192);
  FastLED.show();  

}

void loop() 
{
 serialEvent();
 if (stringComplete) {  Serial.println(inputString);  inputString.trim();
  if (inputString=="RP") { RFID="pass"; rfid_pass(); }
  if (inputString=="RF") { RFID="fail"; rfid_fail(); }
  if (inputString=="RA") { RFID="admin"; rfid_admin(); }

button_light(inputString.substring(0,1),inputString.substring(1).toInt());
  inputString = "";    stringComplete = false; 
 }
 if (RFID=="fail") rfid_fail();
 if (RFID=="pass") rfid_pass();
 if (RFID=="admin") rfid_admin();
 }

void serialEvent(){ if (Serial.available() > 0) {  while (Serial.available()) {
  char inChar = (char)Serial.read();
  inputString += inChar;
  if (inChar == '\n') {  stringComplete = true;  }
  } } }

void rfid_fail()
{ 
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
  FastLED.show();  
  Serial.println(gHue);
  EVERY_N_MILLISECONDS( 10 ) { gHue++;  /* Serial.println("."); */ } // slowly cycle the "base color" through the rainbow
}
void rfid_admin()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( 160, 255, 128); //// CHSV( colour_wheel, rich, bright);
  FastLED.show();  
}
void rfid_pass()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( 96, 255, 128); //// CHSV( colour_wheel, rich, bright);
  FastLED.show();  
}
