// ----- Version 1.1 -----
#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads0(0x48);     /* Dimming Module #1 x48 */
Adafruit_ADS1115 ads1(0x49);     /* Dimming Module #2 x49 */
Adafruit_ADS1115 ads2(0x4A);     /* Dimming Module #3 x4A */
Adafruit_ADS1115 ads3(0x4B);     /* Dimming Module #4 x4B */
int slid1=0, slidold1=0, slid2=0, slidold2=0, slid3=0, slidold3=0, slid4=0, slidold4=0, slid5=0, slidold5=0, slid6=0, slidold6=0, slid7=0, slidold7=0, slid8=0, slidold8=0;
int but1=0, butold1=0, but2=0, butold2=0, but3=0, butold3=0, but4=0, butold4=0,but5=0, butold5=0, but6=0, butold6=0, but7=0, butold7=0, but8=0, butold8=0, joyold1=0, joyold2=0, joyold3=0, joyold4=0, joyold5=0, joyold6=0, joyold7=0, joyold8=0; 
int32_t joy0, joy1, joy2, joy3, joy4, joy5, joy6, joy7, x=0;

void setup(void) 
{  int x=200; // delay in startup scroll of leds (fake loading - Delay)
  Serial.begin(115200);
  Serial.println();
  ads0.begin();  //ads0.setGain(GAIN_TWOTHIRDS);
  ads1.begin();  //ads1.setGain(GAIN_TWOTHIRDS);
  ads2.begin();  //ads2.setGain(GAIN_TWOTHIRDS);
  ads3.begin();  //ads3.setGain(GAIN_TWOTHIRDS);
  pinMode(10, INPUT);  pinMode(11, INPUT);  pinMode(12, INPUT);  pinMode(13, INPUT);  // joystick buttons
  pinMode(10, INPUT_PULLUP); pinMode(11, INPUT_PULLUP); pinMode(12, INPUT_PULLUP); pinMode(13, INPUT_PULLUP); 
  pinMode(3, OUTPUT);  pinMode(5, OUTPUT);  pinMode(6, OUTPUT);  pinMode(9, OUTPUT);  // Led Lights
  pinMode(2, INPUT);  pinMode(4, INPUT);  pinMode(7, INPUT);  pinMode(8, INPUT);  // panel led buttons
  digitalWrite(3, 1); delay(x); digitalWrite(5, 1); delay(x); digitalWrite(6, 1); delay(x); digitalWrite(9, 1); delay(x); digitalWrite(3, 0); delay(x); digitalWrite(5, 0); delay(x); digitalWrite(6, 0); delay(x); digitalWrite(9, 0); //startup led scroll flash
}
 
void loop(void) 
{
  slid1 = ads0.readADC_SingleEnded(0)/103.3;  if (slid1!=slidold1) { slidold1=slid1; Serial.print(" Slider 1 : "); Serial.println(slidold1); }
  slid2 = ads0.readADC_SingleEnded(1)/103.3;  if (slid2!=slidold2) { slidold2=slid2; Serial.print(" Slider 2 : "); Serial.println(slidold2); }
  slid3 = ads1.readADC_SingleEnded(0)/104;  if (slid3!=slidold3) { slidold3=slid3; Serial.print(" Slider 3 : "); Serial.println(slidold3); }
  slid4 = ads1.readADC_SingleEnded(1)/104;  if (slid4!=slidold4) { slidold4=slid4; Serial.print(" Slider 4 : "); Serial.println(slidold4); }
  slid5 = ads2.readADC_SingleEnded(0)/104;  if (slid5!=slidold5) { slidold5=slid5; Serial.print(" Slider 5 : "); Serial.println(slidold5); }
  slid6 = ads2.readADC_SingleEnded(1)/104;  if (slid6!=slidold6) { slidold6=slid6; Serial.print(" Slider 6 : "); Serial.println(slidold6); }
  slid7 = ads3.readADC_SingleEnded(0)/104;  if (slid7!=slidold7) { slidold7=slid7; Serial.print(" Slider 7 : "); Serial.println(slidold7); }
  slid8 = ads3.readADC_SingleEnded(1)/104;  if (slid8!=slidold8) { slidold8=slid8; Serial.print(" Slider 8 : "); Serial.println(slidold8); }
  but1 = digitalRead(10);  if (but1!=butold1) { digitalWrite(3, butold1); butold1=but1; Serial.print(" Joy Button 1 : "); Serial.println(butold1); }
  but2 = digitalRead(11);  if (but2!=butold2) { digitalWrite(5, butold2); butold2=but2; Serial.print(" Joy Button 2 : "); Serial.println(butold2); }
  but3 = digitalRead(12);  if (but3!=butold3) { digitalWrite(6, butold3); butold3=but3; Serial.print(" Joy Button 3 : "); Serial.println(butold3); }
  but4 = digitalRead(13);  if (but4!=butold4) { digitalWrite(9, butold4); butold4=but4; Serial.print(" Jpy Button 4 : "); Serial.println(butold4); }
  joy0 = ads0.readADC_SingleEnded(2)/103;  if (joy0!=joyold1) { joyold1=joy0;  if (joy0<127) { Serial.print(joy0); Serial.println(" Joystick 1: Left"); } else if (joy0>130) { Serial.print(joy0); Serial.println(" Joystick 1: Right"); } }
  joy1 = ads0.readADC_SingleEnded(3)/300;  if (joy1!=joyold2) { joyold2=joy1;  if (joy1<47) { Serial.print(joy1); Serial.println(" Joystick 1: Up"); } else if (joy1>49) { Serial.print(joy1); Serial.println(" Joystick 1: Down"); } } 
  joy2 = ads1.readADC_SingleEnded(2)/103;  if (joy2!=joyold3) { joyold3=joy2;  Serial.print("Joystick 2: ");  if (joy2<127) Serial.print("Left | "); else if (joy2>130) Serial.print("Right | "); }
  joy3 = ads1.readADC_SingleEnded(3)/300;  if (joy3!=joyold4) { joyold4=joy3;  Serial.print("Joystick 2: ");  if (joy3<47) Serial.println("Up"); else if (joy3>48) Serial.println("Down"); }
  joy4 = ads2.readADC_SingleEnded(2)/103;  if (joy4!=joyold5) { joyold5=joy4;  Serial.print("Joystick 3: ");  if (joy4<127) Serial.print("Left | "); else if (joy4>130) Serial.print("Right | "); }
  joy5 = ads2.readADC_SingleEnded(3)/300;  if (joy5!=joyold6) { joyold6=joy5;  Serial.print("Joystick 3: ");  if (joy5<47) Serial.println("Up"); else if (joy5>48) Serial.println("Down"); }
  joy6 = ads3.readADC_SingleEnded(2)/103;  if (joy6!=joyold7) { joyold7=joy6;  Serial.print("Joystick 4: ");  if (joy6<127) Serial.print("Left | "); else if (joy6>130) Serial.print("Right | "); }
  joy7 = ads3.readADC_SingleEnded(3)/300;  if (joy7!=joyold8) { joyold8=joy7;  Serial.print("Joystick 4: ");  if (joy7<47) Serial.println("Up"); else if (joy7>48) Serial.println("Down"); }
  but5 = digitalRead(2);  if (but5!=butold5) { butold5=but5; Serial.print(" LCD Button 1 : "); Serial.println(butold5); }
  but6 = digitalRead(4);  if (but6!=butold6) { butold6=but6; Serial.print(" LCD Button 2 : "); Serial.println(butold6); }
  but7 = digitalRead(7);  if (but7!=butold7) { butold7=but7; Serial.print(" LCD Button 3 : "); Serial.println(butold7); }
  but8 = digitalRead(8);  if (but8!=butold8) { butold8=but8; Serial.print(" LCD Button 4 : "); Serial.println(butold8); }

}
