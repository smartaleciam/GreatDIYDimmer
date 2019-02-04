
void Joy_Event(){ if (Serial1.available() > 0) {  while (Serial1.available()) {  char inChar = (char)Serial1.read(); inputString += inChar;  
if (inChar == '\n') {  stringComplete1 = true;  inputString.trim();
  if (inputString=="RFID_PASS") { RFID="pass"; rfid_pass(); inputString = "";    stringComplete1 = false; }
  if (inputString=="RFID_FAIL") { RFID="fail"; rfid_fail(); inputString = "";    stringComplete1 = false; }
  if (inputString=="RFID_ADMIN") { RFID="admin"; rfid_admin();  inputString = "";    stringComplete1 = false; }
} 
} } }

void rfid_fail()
{
  // a colored dot sweeping back and forth, with fading trails
//  fadeToBlackBy( leds, NUM_LEDS, 20);
//  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
//  leds[pos] += CHSV( 0, 255, 192);
//  FastLED.show();  
//  EVERY_N_MILLISECONDS( 10 ) { gHue++;  /* Serial.println("."); */ } // slowly cycle the "base color" through the rainbow
}
void rfid_admin()
{
  // a colored dot sweeping back and forth, with fading trails
//  fadeToBlackBy( leds, NUM_LEDS, 20);
//  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
//  leds[pos] += CHSV( 160, 255, 128); //// CHSV( colour_wheel, rich, bright);
//  FastLED.show();  
}
void rfid_pass()
{
  // a colored dot sweeping back and forth, with fading trails
//  fadeToBlackBy( leds, NUM_LEDS, 20);
//  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
//  leds[pos] += CHSV( 96, 255, 128); //// CHSV( colour_wheel, rich, bright);
//  FastLED.show();  
}
