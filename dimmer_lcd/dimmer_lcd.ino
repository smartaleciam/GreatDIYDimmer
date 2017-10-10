// Screen resolution of 480x320 pixels.
// This program requires the UTFT library.
//
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
UTFTGLUE myGLCD(0x9488,A2,A1,A3,A4,A0);
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

// Declare which fonts we will be using
#if !defined(SmallFont)
extern uint8_t SmallFont[];    //.kbv GLUE defines as GFXFont ref
#endif
TouchScreen ts = TouchScreen(7, A2, A1, 6, 300);
//TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 20
#define MAXPRESSURE 1000

#define SWAP(a, b) {uint16_t tmp = a; a = b; b = tmp;}

int16_t BOXSIZE;
int16_t PENRADIUS = 3;
uint16_t identifier, oldcolor, currentcolor;
uint8_t Orientation = 1;    //PORTRAIT
byte x = 0;

void setup()
{
  randomSeed(analogRead(5));   //.kbv Due does not like A0
    pinMode(A0, OUTPUT);       //.kbv mcufriend have RD on A0
    digitalWrite(A0, HIGH);
  
  Wire.begin();   // join i2c bus ( as Master )    Arduino 2560 - Touch LCD
//  Wire.begin(1);   // join i2c bus ( as Master )  Arduino Uno - USB Stick Recorder
//  Wire.begin(2);   // join i2c bus ( as Master ) Arduino 2560 - { 2x DMX, Pixel, Midi in/out } - Output Board

// Setup the LCD
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  myGLCD.clrScr();
introscreen();
}

void introscreen()
{
  // Clear the screen and draw the frame
  myGLCD.setColor(255,255,255);
  myGLCD.fillRect(1,15,478,304);

// Draw some lines in a pattern
  myGLCD.setColor (255,0,0);
  for (int i=15; i<304; i+=5)  {    myGLCD.drawLine(1, i, (i*1.6)-10, 304);  }
  myGLCD.setColor (255,0,0);
  for (int i=304; i>15; i-=5)  {    myGLCD.drawLine(478, i, (i*1.6)-11, 15);  }
  myGLCD.setColor (0,255,255);
  for (int i=304; i>15; i-=5)  {    myGLCD.drawLine(1, i, 491-(i*1.6), 15);  }
  myGLCD.setColor (0,255,255);
  for (int i=15; i<304; i+=5)  {    myGLCD.drawLine(478, i, 490-(i*1.6), 304);  }
  delay (5000);  myGLCD.clrScr();
  }

void loop()
{


}

