#include <Wire.h>
//#include "FastLED.h"
// How many leds in your strip?
//#define NUM_LEDS 64
//#define DATA_PIN 3
//#define COLOR_ORDER GRB
//#define BRIGHTNESS 96
//#define FRAMES_PER_SECOND  120
// Define the array of leds
//CRGB leds[NUM_LEDS];

//uint8_t gHue = 0; // rotating "base color" used by many of the patterns

// --- setup of slider paramters
// >left <right <up >down
int aa=145, bb=115, cc=120, dd=146, i=0;  // set paramers for joystick center
int stick=1,j1hc=0,j1vc=0,j2hc=0,j2vc=0,j3hc=0,j3vc=0,j4hc=0,j4vc=0;

int16_t slid1=0, slidold1=-1, slid2=0, slidold2=-1, slid3=0, slidold3=-1, slid4=0, slidold4=-1, slid5=0, slidold5=-1, slid6=0, slidold6=-1, slid7=0, slidold7=-1, slid8=0, slidold8=-1;
int but1=0, butold1=-1, but2=0, butold2=-1, but3=0, butold3=-1, but4=0, butold4=-1,but5=0, butold5=-1, but6=0, butold6=-1, but7=0, butold7=-1, but8=0, butold8=-1, joyold1=0, joyold2=0, joyold3=0, joyold4=0, joyold5=0, joyold6=0, joyold7=0, joyold8=0; 
int16_t joy0, joy1, joy2, joy3, joy4, joy5, joy6, joy7, x=0;
String inputString = "",inputString1 = "",inputString2 = "",inputString3 = "", RFID="loading";
boolean stringComplete = false, stringComplete1 = false, stringComplete2 = false, stringComplete3 = false;

//config variables
#define NUM_BTN_COLUMNS (4)
#define NUM_BTN_ROWS (4)
#define MAX_DEBOUNCE (1)

// Global variables
static int32_t next_scan;
static const uint8_t btnselpins[4]  = {42,43,44,45}; // Gnd select pins
static const uint8_t btnreadpins[4] = {32,33,34,35};  // Switch select pins
static int8_t debounce_count[NUM_BTN_COLUMNS][NUM_BTN_ROWS];


//  FastLED.addLeds<WS2811, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  FastLED.setBrightness(BRIGHTNESS);


void setup() 
{ 
  Serial.begin(115200);  inputString.reserve(100);  //-- to Wifi esp board
  Serial1.begin(115200); inputString1.reserve(100);  //-- to pix joysticks pixels board
  Serial2.begin(115200); inputString2.reserve(100);  //-- to pix buttons pixels board
  Serial3.begin(115200); inputString3.reserve(100);  //-- to main lcd arduino
//  Serial3.begin(2000000); inputString3.reserve(100);  //-- to main lcd arduino
  Wire.begin();        // join i2c bus ( as Master ) Arduino 2560 - Touch LCD
//  Wire.begin(1);   // join i2c bus ( as Master ) Arduino Uno  - USB Stick Recorder
//  Wire.begin(2);   // join i2c bus ( as Master ) Arduino 2560 - { 2x DMX, Pixel, Midi in/out } - Output Board
  Wire.onReceive(receiveI2C); // register event
//rfid_fail();
slider_input();
setuppins();
}

void receiveI2C(int howMany) {
  while (1 < Wire.available()) {  char c = Wire.read(); Serial.print(c);  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
void serial_lcd_send(String s_com, int s_value)
{
  Serial.println(s_com+":"+s_value);
  }
void slider_input() 
{
  slid1 = map(analogRead(0), 0, 1001, 0, 255);  if (slid1!=slidold1) { slidold1=slid1; serial_lcd_send("SL_1", slidold1); }
  slid2 = map(analogRead(1), 0, 1001, 0, 255);  if (slid2!=slidold2) { slidold2=slid2; serial_lcd_send("SL_2", slidold2); }
  slid3 = map(analogRead(2), 0, 1001, 0, 255);  if (slid3!=slidold3) { slidold3=slid3; serial_lcd_send("SL_3", slidold3); }
  slid4 = map(analogRead(3), 0, 1001, 0, 255);  if (slid4!=slidold4) { slidold4=slid4; serial_lcd_send("SL_4", slidold4); }
  slid5 = map(analogRead(4), 0, 1001, 0, 255);  if (slid5!=slidold5) { slidold5=slid5; serial_lcd_send("SL_5", slidold5); }
  slid6 = map(analogRead(5), 0, 1001, 0, 255);  if (slid6!=slidold6) { slidold6=slid6; serial_lcd_send("SL_6", slidold6); }
  slid7 = map(analogRead(6), 0, 1001, 0, 255);  if (slid7!=slidold7) { slidold7=slid7; serial_lcd_send("SL_7", slidold7); }
  slid8 = map(analogRead(7), 0, 1001, 0, 255);  if (slid8!=slidold8) { slidold8=slid8; serial_lcd_send("SL_8", slidold8); }
  but1 = digitalRead(6);  if (but1!=butold1) { butold1=but1; serial_lcd_send("JB_1", butold1); }
  but2 = digitalRead(7);  if (but2!=butold2) { butold2=but2; serial_lcd_send("JB_2", butold2); }
  but3 = digitalRead(8);  if (but3!=butold3) { butold3=but3; serial_lcd_send("JB_3", butold3); }
  but4 = digitalRead(9);  if (but4!=butold4) { butold4=but4; serial_lcd_send("JB_4", butold4); }
  joy0 = map(analogRead(8), 0, 1023, 0, 255);  if (joy0!=joyold1) { joyold1=joy0;
    if (stick==1) {  if (joy0>=aa) { serial_lcd_send("JS_1:LL",joy0); j1hc=0; } else if (joy0<=bb) { serial_lcd_send("JS_1:RR",joy0); j1hc=0; }
    if ((joy0>=bb+2) && (joy0<=aa-2) && (j1hc==0)){ serial_lcd_send("JS_1:HC",joy0); j1hc=1; }  }else{ serial_lcd_send("JH_1:",joy0);  }  }
  joy1 = map(analogRead(9), 0, 1023, 0, 255);  if (joy1!=joyold2) { joyold2=joy1;
    if (stick==1) {  if (joy1<=cc-1) { serial_lcd_send("JS_1:UU",joy1); j1vc=0; } else if (joy1>=dd) { serial_lcd_send("JS_1:DD",joy1); j1vc=0; }
    if ((joy1>=cc+2) && (joy1<=dd-2) && (j1vc==0)){ serial_lcd_send("JS_1:VC",joy1);  j1vc=1;}  }else{ serial_lcd_send("JV_1:",joy1);  }  }  
  joy2 = map(analogRead(10), 0, 1023, 0, 255);  if (joy2!=joyold3) { joyold3=joy2;
    if (stick==1) {  if (joy2>=aa) { serial_lcd_send("JS_2:LL",joy2); j2hc=0; } else if (joy2<=bb) { serial_lcd_send("JS_2:RR",joy2); j2hc=0; }
    if ((joy2>=bb+2) && (joy2<=aa-2) && (j2hc==0)){ serial_lcd_send("JS_2:HC",joy2); j2hc=1; }  }else{ serial_lcd_send("JH_2:",joy2);  }  }
  joy3 = map(analogRead(11), 0, 1023, 0, 255);  if (joy3!=joyold4) { joyold4=joy3;
    if (stick==1) {  if (joy3<=cc-1) { serial_lcd_send("JS_2:UU",joy3); j2vc=0; } else if (joy3>=dd) { serial_lcd_send("JS_2:DD",joy3); j2vc=0; }
    if ((joy3>=cc+2) && (joy3<=dd-2) && (j2vc==0)){ serial_lcd_send("JS_2:VC",joy3); j2vc=1; }  }else{ serial_lcd_send("JV_2:",joy3);  }  }  
  joy4 = map(analogRead(12), 0, 1023, 0, 255);  if (joy4!=joyold5) { joyold5=joy4;
    if (stick==1) {  if (joy4>=aa) { serial_lcd_send("JS_3:LL",joy4); j3hc=0; } else if (joy4<=bb) { serial_lcd_send("JS_3:RR",joy4); j3hc=0; }
    if ((joy4>=bb+2) && (joy4<=aa-2) && (j3hc==0)){ serial_lcd_send("JS_3:HC",joy4); j3hc=1; }  }else{ serial_lcd_send("JH_3:",joy4);  }  }
  joy5 = map(analogRead(13), 0, 1023, 0, 255);  if (joy5!=joyold6) { joyold6=joy5;
    if (stick==1) {  if (joy5<=cc-1) { serial_lcd_send("JS_3:UU",joy5); j3vc=0; } else if (joy5>=dd) { serial_lcd_send("JS_3:DD",joy5); j3vc=0; }
    if ((joy5>=cc+2) && (joy5<=dd-2) && (j3vc==0)){ serial_lcd_send("JS_3:VC",joy5); j3vc=1; }  }else{ serial_lcd_send("JV_3:",joy5);  }  }  
  joy6 = map(analogRead(14), 0, 1023, 0, 255);  if (joy6!=joyold7) { joyold7=joy6;
    if (stick==1) {  if (joy6>=aa) { serial_lcd_send("JS_4:LL",joy6); j4hc=0; } else if (joy6<=bb) { serial_lcd_send("JS_4:RR",joy6); j4hc=0; }
    if ((joy6>=bb+2) && (joy6<=aa-2) && (j4hc==0)){ serial_lcd_send("JS_4:HC",joy6); j4hc=1; }  }else{ serial_lcd_send("JH_4:",joy6);  }  }
  joy7 = map(analogRead(15), 0, 1023, 0, 255);  if (joy7!=joyold8) { joyold8=joy7; 
    if (stick==1) {  if (joy7<=cc-1) { serial_lcd_send("JS_4:UU",joy7); j4vc=0; } else if (joy7>=dd) { serial_lcd_send("JS_4:DD",joy7); j4vc=0; } 
    if ((joy7>=cc+2) && (joy7<=dd-2) && (j4vc==0)){ serial_lcd_send("JS_4:VC",joy7); j4vc=1; }  }else{ serial_lcd_send("JV_4:",joy7);  }  }  
}

//void serialEvent(){ if (Serial.available() > 0) {  while (Serial.available()) {  char inChar = (char)Serial.read(); inputString += inChar;    if (inChar == '\n') {  stringComplete = true;  }  } } }
void serialEvent3(){ if (Serial3.available() > 0) {  while (Serial3.available()) {  char inChar3 = (char)Serial3.read(); inputString3 += inChar3;    if (inChar3 == '\n') {  stringComplete3 = true;  }  } } }

void loop() 
{
// serialEvent();
// Joy_Event();      // serialEvent1();
// Button_Event();   // serialEvent2();
 serialEvent3();
 if (stringComplete) {  inputString.trim(); Serial.print("Wifi-");  Serial.println(inputString);   inputString = "";    stringComplete = false;  }
 if (stringComplete3) {  inputString3.trim(); Serial.println(inputString3);  //Serial.print("Lcd incomming-");
//  if (inputString3=="RFID_PASS") { RFID="pass"; Serial1.println("C=1"); Serial2.println("C=1");  scan();  slider_input();  inputString3 = "";   stringComplete3 = false;}
//  if (inputString3=="RFID_FAIL") { RFID="fail"; Serial1.println("C=0"); Serial2.println("C=0");  inputString3 = "";    stringComplete3 = false;}
//  if (inputString3=="RFID_ADMIN") { RFID="admin"; Serial1.println("C=2"); Serial2.println("C=2"); inputString3 = "";    stringComplete3 = false;}
//  if (inputString3=="Stick") { if (stick==1) stick=0; else if (stick==0) stick=1;  inputString3 = "";    stringComplete3 = false;  }
//  }
// if (stringComplete3) {  inputString3.trim(); Serial.print("LCD-");  Serial.println(inputString3);  
inputString3 = "";    stringComplete3 = false;  }
// if (RFID=="fail") rfid_fail();
// if (RFID=="pass") serial_output();
scan();
slider_input();

}
