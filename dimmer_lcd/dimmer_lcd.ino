
#include <SPI.h>        // RC522 Module uses SPI protocol
#include <Ethernet.h>   // Ethernet Library Wiznet
#include <MFRC522.h>  // Library for Mifare RC522 Devices
#include <SD.h>         // We are going to read and write PICC's UIDs from/to SD

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
UTFTGLUE myGLCD(0x9488,A2,A1,A3,A4,A0);
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>
/*
  We need to define MFRC522's pins and create instance
  Pin layout should be as follows (on Arduino Uno):
  MOSI: Pin 11 / ICSP-4
  MISO: Pin 12 / ICSP-1
  SCK : Pin 13 / ICSP-3
  SDA : (Configurable)
  RST : Not Needed
 */
#define SS_PIN 9
#define RST_PIN 8
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

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
   Serial.begin(115200);  // Initialize serial communications with PC
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
//rfid_startup();
introscreen();
}

void loop()
{
//loop1;

}

