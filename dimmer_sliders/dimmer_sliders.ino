// --- setup of slider paramters
// >left <right <up >down
int aa=145, bb=115, cc=120, dd=146, i=0;
int stick=1,j1hc=0,j1vc=0,j2hc=0,j2vc=0,j3hc=0,j3vc=0,j4hc=0,j4vc=0;
#include <Wire.h>
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
serial_output();
setuppins();
}

void receiveI2C(int howMany) {
  while (1 < Wire.available()) {  char c = Wire.read(); Serial.print(c);  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

void serial_output() 
{
  slid1 = map(analogRead(0), 0, 1001, 0, 255);  if (slid1!=slidold1) { slidold1=slid1; Serial3.print("SL_1:"); Serial3.println(slidold1);}
  slid2 = map(analogRead(1), 0, 1001, 0, 255);  if (slid2!=slidold2) { slidold2=slid2; Serial3.print("SL_2:"); Serial3.println(slidold2); }
  slid3 = map(analogRead(2), 0, 1001, 0, 255);  if (slid3!=slidold3) { slidold3=slid3; Serial3.print("SL_3:"); Serial3.println(slidold3); }
  slid4 = map(analogRead(3), 0, 1001, 0, 255);  if (slid4!=slidold4) { slidold4=slid4; Serial3.print("SL_4:"); Serial3.println(slidold4); }
  slid5 = map(analogRead(4), 0, 1001, 0, 255);  if (slid5!=slidold5) { slidold5=slid5; Serial3.print("SL_5:"); Serial3.println(slidold5); }
  slid6 = map(analogRead(5), 0, 1001, 0, 255);  if (slid6!=slidold6) { slidold6=slid6; Serial3.print("SL_6:"); Serial3.println(slidold6); }
  slid7 = map(analogRead(6), 0, 1001, 0, 255);  if (slid7!=slidold7) { slidold7=slid7; Serial3.print("SL_7:"); Serial3.println(slidold7); }
  slid8 = map(analogRead(7), 0, 1001, 0, 255);  if (slid8!=slidold8) { slidold8=slid8; Serial3.print("SL_8:"); Serial3.println(slidold8); }
  but1 = digitalRead(6);  if (but1!=butold1) { butold1=but1; Serial3.print("JB_1:"); Serial3.println(butold1); }
  but2 = digitalRead(7);  if (but2!=butold2) { butold2=but2; Serial3.print("JB_2:"); Serial3.println(butold2); }
  but3 = digitalRead(8);  if (but3!=butold3) { butold3=but3; Serial3.print("JB_3:"); Serial3.println(butold3); }
  but4 = digitalRead(9);  if (but4!=butold4) { butold4=but4; Serial3.print("JB_4:"); Serial3.println(butold4); }
  joy0 = map(analogRead(8), 0, 1023, 0, 255);  if (joy0!=joyold1) { joyold1=joy0;
    if (stick==1) {  if (joy0>=aa) { Serial3.println("JS_1:LL"); j1hc=0; } else if (joy0<=bb) { Serial3.println("JS_1:RR"); j1hc=0; }
    if ((joy0>=bb+2) && (joy0<=aa-2) && (j1hc==0)){ Serial3.println("JS_1:HC"); j1hc=1; }  }else{ Serial3.print("JH_1:");  Serial3.println(joy0);  }  }
  joy1 = map(analogRead(9), 0, 1023, 0, 255);  if (joy1!=joyold2) { joyold2=joy1;
    if (stick==1) {  if (joy1<=cc-1) { Serial3.println("JS_1:UU"); j1vc=0; } else if (joy1>=dd) { Serial3.println("JS_1:DD"); j1vc=0; }
    if ((joy1>=cc+2) && (joy1<=dd-2) && (j1vc==0)){ Serial3.println("JS_1:VC");  j1vc=1;}  }else{ Serial3.print("JV_1:");  Serial3.println(joy1);  }  }  
  joy2 = map(analogRead(10), 0, 1023, 0, 255);  if (joy2!=joyold3) { joyold3=joy2;
    if (stick==1) {  if (joy2>=aa) { Serial3.println("JS_2:LL"); j2hc=0; } else if (joy2<=bb) { Serial3.println("JS_2:RR"); j2hc=0; }
    if ((joy2>=bb+2) && (joy2<=aa-2) && (j2hc==0)){ Serial3.println("JS_2:HC"); j2hc=1; }  }else{ Serial3.print("JH_2:");  Serial3.println(joy2);  }  }
  joy3 = map(analogRead(11), 0, 1023, 0, 255);  if (joy3!=joyold4) { joyold4=joy3;
    if (stick==1) {  if (joy3<=cc-1) { Serial3.println("JS_2:UU"); j2vc=0; } else if (joy3>=dd) { Serial3.println("JS_2:DD"); j2vc=0; }
    if ((joy3>=cc+2) && (joy3<=dd-2) && (j2vc==0)){ Serial3.println("JS_2:VC"); j2vc=1; }  }else{ Serial3.print("JV_2:");  Serial3.println(joy3);  }  }  
  joy4 = map(analogRead(12), 0, 1023, 0, 255);  if (joy4!=joyold5) { joyold5=joy4;
    if (stick==1) {  if (joy4>=aa) { Serial3.println("JS_3:LL"); j3hc=0; } else if (joy4<=bb) { Serial3.println("JS_3:RR"); j3hc=0; }
    if ((joy4>=bb+2) && (joy4<=aa-2) && (j3hc==0)){ Serial3.println("JS_3:HC"); j3hc=1; }  }else{ Serial3.print("JH_3:");  Serial3.println(joy4);  }  }
  joy5 = map(analogRead(13), 0, 1023, 0, 255);  if (joy5!=joyold6) { joyold6=joy5;
    if (stick==1) {  if (joy5<=cc-1) { Serial3.println("JS_3:UU"); j3vc=0; } else if (joy5>=dd) { Serial3.println("JS_3:DD"); j3vc=0; }
    if ((joy5>=cc+2) && (joy5<=dd-2) && (j3vc==0)){ Serial3.println("JS_3:VC"); j3vc=1; }  }else{ Serial3.print("JV_3:");  Serial3.println(joy5);  }  }  
  joy6 = map(analogRead(14), 0, 1023, 0, 255);  if (joy6!=joyold7) { joyold7=joy6;
    if (stick==1) {  if (joy6>=aa) { Serial3.println("JS_4:LL"); j4hc=0; } else if (joy6<=bb) { Serial3.println("JS_4:RR"); j4hc=0; }
    if ((joy6>=bb+2) && (joy6<=aa-2) && (j4hc==0)){ Serial3.println("JS_4:HC"); j4hc=1; }  }else{ Serial3.print("JH_4:");  Serial3.println(joy6);  }  }
  joy7 = map(analogRead(15), 0, 1023, 0, 255);  if (joy7!=joyold8) { joyold8=joy7; 
    if (stick==1) {  if (joy7<=cc-1) { Serial3.println("JS_4:UU"); j4vc=0; } else if (joy7>=dd) { Serial3.println("JS_4:DD"); j4vc=0; } 
    if ((joy7>=cc+2) && (joy7<=dd-2) && (j4vc==0)){ Serial3.println("JS_4:VC"); j4vc=1; }  }else{ Serial3.print("JV_4:");  Serial3.println(joy7);  }  }  
}

void serialEvent(){ if (Serial.available() > 0) {  while (Serial.available()) {  char inChar = (char)Serial.read(); inputString += inChar;    if (inChar == '\n') {  stringComplete = true;  }  } } }
void serialEvent1(){ if (Serial1.available() > 0) {  while (Serial1.available()) {  char inChar1 = (char)Serial1.read(); inputString1 += inChar1;    if (inChar1 == '\n') {  stringComplete1 = true;  }  } } }
void serialEvent2(){ if (Serial2.available() > 0) {  while (Serial2.available()) {  char inChar2 = (char)Serial2.read(); inputString2 += inChar2;    if (inChar2 == '\n') {  stringComplete2 = true;  }  } } }
void serialEvent3(){ if (Serial3.available() > 0) {  while (Serial3.available()) {  char inChar3 = (char)Serial3.read(); inputString3 += inChar3;    if (inChar3 == '\n') {  stringComplete3 = true;  }  } } }

void loop() 
{
 serialEvent();
 serialEvent1();
 serialEvent2();
 serialEvent3();
 if (stringComplete) {  inputString.trim(); Serial.print("Wifi-");  Serial.println(inputString);   inputString = "";    stringComplete = false;  }
 if (stringComplete1) {  inputString1.trim(); Serial.print("B-Pixels-");  Serial.println(inputString1);   inputString1 = "";    stringComplete1 = false;  }
 if (stringComplete2) {  inputString2.trim(); Serial.print("S-Pixels-");  Serial.println(inputString2);   inputString2 = "";    stringComplete2 = false;  }
 if (stringComplete3) {  inputString3.trim(); Serial.println(inputString3);  //Serial.print("Lcd incomming-");
  if (inputString3=="RFID_PASS") { RFID="pass"; Serial1.println("C=1"); Serial2.println("C=1");  scan();  serial_output();  inputString3 = "";   stringComplete3 = false;}
  if (inputString3=="RFID_FAIL") { RFID="fail"; Serial1.println("C=0"); Serial2.println("C=0");  inputString3 = "";    stringComplete3 = false;}
  if (inputString3=="RFID_ADMIN") { RFID="admin"; Serial1.println("C=2"); Serial2.println("C=2"); inputString3 = "";    stringComplete3 = false;}
  if (inputString3=="Stick") { if (stick==1) stick=0; else if (stick==0) stick=1;  inputString3 = "";    stringComplete3 = false;  }
  }
// if (stringComplete3) {  inputString3.trim(); Serial.print("LCD-");  Serial.println(inputString3);   inputString3 = "";    stringComplete3 = false;  }
// if (RFID=="fail") rfid_fail();
// if (RFID=="pass") serial_output();
 scan();
 serial_output();

}

