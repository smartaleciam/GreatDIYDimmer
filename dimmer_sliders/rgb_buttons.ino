
void Button_Event(){ if (Serial2.available() > 0) {  while (Serial2.available()) {  char inChar2 = (char)Serial2.read(); inputString2 += inChar2;    if (inChar2 == '\n') {  stringComplete2 = true; 
 inputString2.trim(); Serial.print("S-Pixels-");  Serial.println(inputString2);   inputString2 = "";    stringComplete2 = false; }  } } }


// read the 4 buttons an control the red leds as needed, for screen control buttons etc

static void setuppins()
{
    uint8_t i;
    for(i = 0; i < NUM_BTN_COLUMNS; i++)  {  pinMode(btnselpins[i], OUTPUT);  digitalWrite(btnselpins[i], HIGH);  }
    // key return lines
    for(i = 0; i < 4; i++)
    {  pinMode(btnreadpins[i], INPUT_PULLUP);  }
    for(uint8_t i = 0; i < NUM_BTN_COLUMNS; i++)  {  for(uint8_t j = 0; j < NUM_BTN_ROWS; j++)  {  debounce_count[i][j] = 0;  }   }
}

static void scan()
{
  static uint8_t current = 0;
  uint8_t val;
  uint8_t i, j;
  digitalWrite(btnselpins[current], LOW);
  for( j = 0; j < NUM_BTN_ROWS; j++)
  {
    val = digitalRead(btnreadpins[j]);
    if(val == LOW)
    {
      // active low: val is low when btn is pressed
      if( debounce_count[current][j] < MAX_DEBOUNCE)
      {
        debounce_count[current][j]++;
        if( debounce_count[current][j] == MAX_DEBOUNCE )
        {
          Serial.print("Key_Down_");
          Serial.println((current * NUM_BTN_ROWS) + j);
 // leds[(current * NUM_BTN_ROWS) + j] = CRGB::Blue;
//  FastLED.show();
        }
      }
    }
    else
    {
      // otherwise, button is released
      if( debounce_count[current][j] > 0)
      {
        debounce_count[current][j]--;
        if( debounce_count[current][j] == 0 )
        {
          Serial.print("Key_Up_");
          Serial.println((current * NUM_BTN_ROWS) + j);
 // leds[(current * NUM_BTN_ROWS) + j] = CRGB::Black;
//  FastLED.show();
        }
      }
    }
  }
  digitalWrite(btnselpins[current], HIGH);
  current++;
  if (current >= NUM_BTN_COLUMNS)  {   current = 0;   }
}
