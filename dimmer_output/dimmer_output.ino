//#include <Conceptinetics.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

//DMX_Master        dmx_master ( 512, 45 );
//DMX_Master        dmx_master2 ( 512, 47 );

String inputString="", Dmx1Ch="", Dmx2Ch="", Dmx1Val="", Dmx2Val="", MidiCh="", MidiNot="", MidiLen="", Eunv="", Ech="" ,Eval="", PreSet="";
boolean stringComplete = false;
/*
void scene1 (void){
  // 10 seconds blue
  for (int i=0; i<10; i++){
    dmx_master.setChannelValue (1, 0);
    dmx_master.setChannelValue (2, 0);
    dmx_master.setChannelValue (3, 255);
    dmx_master.setChannelValue (4, 255);
    dmx_master.setChannelValue (5, 0);
    dmx_master.setChannelValue (6, 0);
    delay(1000);
  }
}

void scene2 (void){
  // 10 seconds blue
  for (int i=0; i<5; i++){
    dmx_master.setChannelValue (1, 255);
    dmx_master.setChannelValue (2, 255);
    dmx_master.setChannelValue (3, 255);
    dmx_master.setChannelValue (4, 255);
    dmx_master.setChannelValue (5, 0);
    dmx_master.setChannelValue (6, 0);
    delay(1000);
  }
}

void scene3 (void){
  // 10 seconds blue
  for (int i=0; i<5; i++){
    dmx_master.setChannelValue (1, 255);
    dmx_master.setChannelValue (2, 0);
    dmx_master.setChannelValue (3, 255);
    dmx_master.setChannelValue (4, 255);
    dmx_master.setChannelValue (5, 0);
    dmx_master.setChannelValue (6, 0);
    delay(1000);
  }
}

void scene4 (void){
  // 10 seconds blue
  for (int i=0; i<5; i++){
    dmx_master.setChannelValue (1, 0);
    dmx_master.setChannelValue (2, 0);
    dmx_master.setChannelValue (3, 255);
    dmx_master.setChannelValue (4, 255);
    dmx_master.setChannelValue (5, 255);
    dmx_master.setChannelValue (6, 0);
    delay(1000);
  }
}

void scene5 (void){
  // 10 seconds blue
  for (int i=0; i<5; i++){
    dmx_master.setChannelValue (1, 0);
    dmx_master.setChannelValue (2, 255);
    dmx_master.setChannelValue (3, 255);
    dmx_master.setChannelValue (4, 255);
    dmx_master.setChannelValue (5, 0);
    dmx_master.setChannelValue (6, 0);
    delay(1000);
  }
}
*/
void ReceiveI2C() {
  
}


// the setup routine runs once when you press reset:
void setup() {
   lcd.begin();
   lcd.backlight();   // Turn on the blacklight and print a message.
   Serial.begin(115200);  // Initialize serial communications with PC
   Serial1.begin(25000);    // Set DMX #1 baud rate:
   Serial2.begin(25000);    // Set DMX #2 baud rate:
   Serial3.begin(31250);    // Set MIDI baud rate:

//  Wire.begin();    // join i2c bus ( as Master ) Arduino 2560 - Touch LCD
//  Wire.begin(1);   // join i2c bus ( as Master )  Arduino Uno - USB Stick Recorder
    Wire.begin(2);   // join i2c bus ( as Master ) Arduino 2560 - { 2x DMX, Pixel, Midi in/out } - Output Board
    Wire.onReceive(ReceiveI2C); // register event

  // Enable DMX master interface and start transmitting
//  dmx_master.enable();
//  dmx_master2.enable ();

  // turn off all channels
//  dmx_master.setChannelValue (1, 0);
//  dmx_master.setChannelValue (2, 0);
//  dmx_master.setChannelValue (3, 0);
//  dmx_master.setChannelValue (4, 0);
//  dmx_master.setChannelValue (5, 0);
//  dmx_master.setChannelValue (6, 0);
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("DMX Dimmer Output");

}

// This function scans the serial port an logs all the data.
void serialEvent(){
    int next=1; inputString="";
    if (Serial.available() > 0) { 
    while (Serial.available()) { char inChar = (char)Serial.read(); 
      if (inputString == "DMX1=") { if (inChar==',') ++next; else if (next==1) Dmx1Ch += inChar; else if (next==2) Dmx1Val += inChar; } 
      if (inputString == "DMX2=") { if (inChar==',') ++next; else if (next==1) Dmx2Ch += inChar; else if (next==2) Dmx2Val += inChar; }
      if (inputString == "MIDI=") { if (inChar==',') ++next; else if (next==1) MidiCh += inChar; else if (next==2) MidiNot += inChar; else if (next==3) MidiLen += inChar; }
      if (inputString == "E132=") { if (inChar==',') ++next; else if (next==1) Eunv += inChar; else if (next==2) Ech += inChar; else if (next==3) Eval += inChar; }
      if (inputString == "PSET=") { PreSet += inChar; } // pixel Pattern
       inputString += inChar;
      if (inChar=='\n') {  stringComplete = true;  } 
    }
  }
}


// the loop routine runs over and over again forever:
void loop()
{
    serialEvent();
    if (stringComplete) {  inputString.trim();  
      if (inputString=="DMX1=") { /* dmx_master.setChannelValue ( Dmx1Ch, Dmx1Val); */ Serial.println(inputString); } else 
      if (inputString=="DMX2=") { /* dmx_master2.setChannelValue ( Dmx2Ch, Dmx2Val); */ Serial.println(inputString); } else 
      if (inputString=="MIDI=") {  } else 
      if (inputString=="E132=") {  } else 
      inputString = "";  stringComplete = false;
    }

}
