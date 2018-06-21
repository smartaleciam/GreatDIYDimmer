// allows or denys master user's and slave sub users, allow different permissions to functions, can block all access to functions, add/remove cards/acess level
// screen list of all users an there acess level  

///////////////////////////////////////// Main Loop ///////////////////////////////////
void RFID_LOOP() {
  //Serial.println("*****************RFID**********************************");  
 if (RFIDPASS==0){
  do {
//   checkClient();
     ScanRFID(); // (LCD_Graphix)
     showtimer(2); // (LCD_Graphix)
     
     successRead = getID();  // sets successRead to 1 when we get read from reader otherwise 0
     }
    while (!successRead);   // the program will not go further while you not get a successful read
  }
}

void RFID() {
 if (rfidaccess==0) RFID_LOOP();
 if (successRead==1 && RFIDPASS==0) {
    if (programMode) { 
      if (isMaster(readCard)) {   // If master card scanned again exit program mode
        rfidaccess=1;  rfid_access(rfidaccess);
        programMode = false;
        return;
      } else {
      if ( findID() ) { // If scanned card is known delete it
        myGLCD.setColor(0, 0, 0); myGLCD.setTextSize(2);   myGLCD.print("Device was Known... Now Deleted ", 50, 110);
        removeID();
        } else {            // If scanned card is not known add it
        myGLCD.setColor(0, 0, 0); myGLCD.setTextSize(2);   myGLCD.print("Device NOT Known... Now Added   ", 50, 110);
        writeID();
        }
      }
    } else {
    if (isMaster(readCard)) {   // If scanned card's ID matches Master Card's ID enter program mode
      programMode = true;
        rfidaccess=2; rfid_access(rfidaccess);
    } else {
      if (findID()) { // If not, check if we can find it
        rfidaccess=1; rfid_access(rfidaccess);
        RFIDPASS=1;
      } else {      // If not, show that the ID was not valid
        myGLCD.setColor(0, 255, 0); myGLCD.setTextSize(4);  myGLCD.print("RFID Denied", 100, clk);  delay(1000);// Prints the string on the screen
        rfidaccess=0; rfid_access(rfidaccess);   showtimer(2);  RFID();
      }
    }
  }
 }
}

void rfid_access(int l){
     if (l==0) { // Access Denied
        Serial1.println("RFID_FAIL");
        myGLCD.fillScreen(BLACK);  myGLCD.setBackColor(255,255,255);  // Sets the background color to black
        myGLCD.setColor(0, 255, 0);  myGLCD.fillCircle(15,15,10);
     } 
     if (l==1) { // Access Granted
        Serial1.println("RFID_PASS");
        myGLCD.fillScreen(BLACK);  myGLCD.setBackColor(255,255,255);  // Sets the background color to black
        myGLCD.setColor(0, 0, 255);  myGLCD.fillCircle(15,15,10);
     } 
     if (l==2) { // Master Mode
        Serial1.println("RFID_ADMIN");
        myGLCD.fillScreen(BLACK);  myGLCD.setBackColor(255,255,255);  // Sets the background color to black
        myGLCD.setColor(255, 0, 0);  myGLCD.fillCircle(15,15,10);
     } 
  }

void getFilename() {  // We will store UIDs as files on SD card
  sprintf(filename, "%s%02x%02x%02x%02x.%s", dir, readCard[0], readCard[1], // Convert readCard data to char and append extension
          readCard[2], readCard[3], extension);
}

boolean findID () {  // Check If we can find UID's specific file
  File fileopen = sd.open(filename);
  if (fileopen) {
    fileopen.close();  // Found it close
    return true;
  }
  else {    // If not, return false
  }
  return false;
}

void writeID () {
  File filewrite = sd.open(filename, FILE_WRITE);
  filewrite.close();
  if (sd.exists(filename)) {
    Serial.println(F("Succesfully added ID record"));
 //   greenBlink();
  }
  else {
    Serial.println(F("Failed to add record"));
//    redBlink();
  }
}

void removeID () {
  sd.remove(filename);
  if (sd.exists(filename)) {
    Serial.println(F("Failed to remove. Record still exists"));
//    redBlink();
  }
  else {
    Serial.println(F("Succesfully removed ID record"));
//    blueBlink();
  }
}

///////////////////////////////////////// Get PICC's UID ///////////////////////////////////
int getID() {
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    return 0;
  }
  // There are Mifare PICCs which have 4 byte or 7 byte UID care if you use 7 byte PICC
  // I think we should assume every PICC as they have 4 byte UID
  // Until we support 7 byte PICCs
//  Serial.print(F("Scanned PICC's UID:"));
  for (int i = 0; i < 4; i++) {  //
    readCard[i] = mfrc522.uid.uidByte[i];
     cardid=readCard[i]; 
//     Serial.print(readCard[i], HEX);
  }
//  Serial.println("");
  mfrc522.PICC_HaltA(); // Stop reading
  getFilename();    // Get data ready
  return 1;
}

void checkMaster() {
  if (sd.exists("SYS/master.dat")) {              // Check if we have master.dat on SD card
//    Serial.print(F("Master Card's UID: "));      // Since we have it print to serial
    File masterfile = sd.open("SYS/master.dat");  // Open file
    for (int i = 0; i < 4; i++) {             // Loop 4 times to get 4 bytes
      readCard[i] = masterfile.read();
//      Serial.print(readCard[i], HEX);         // Actual serial printing of each byte
      masterCard[i] = readCard[i];            // Prepare bytes for future comparing
     }
//    Serial.println("");
    masterfile.close();                       // Close file
  }
  else {
    Serial.println(F("No Master Card Defined"));
    Serial.println(F("Scan A PICC to Define as Master Card"));
    do {
      successRead = getID(); // sets successRead to 1 when we get read from reader otherwise 0
//      blueBlink(); // Visualize Master Card need to be defined
    }
    while (!successRead); //the program will not go further while you not get a successful read
    File masterfile = sd.open("SYS/master.dat", FILE_WRITE);
    if (masterfile) {
      Serial.println(F("Writing to master.dat..."));
      masterfile.write(readCard, 4);
      // close the file:
      masterfile.close();
      writeID();
      Serial.println(F("Master Card successfuly defined"));
    } else {
      // if the file didn't open, print an error:
      Serial.println(F("error creating master.dat"));
 //     redBlink();
    }
  }
}

///////////////////////////////////////// Check Bytes   ///////////////////////////////////
boolean checkTwo ( byte a[], byte b[] ) {
  if ( a[0] != NULL )       // Make sure there is something in the array first
    match = true;       // Assume they match at first
  for ( int k = 0; k < 4; k++ ) {   // Loop 4 times
    if ( a[k] != b[k] )     // IF a != b then set match = false, one fails, all fail
      match = false;
  }
  if ( match ) {      // Check to see if if match is still true
    return true;      // Return true
  }
  else  {
    return false;       // Return false
  }
}

////////////////////// Check readCard IF is masterCard   ///////////////////////////////////
// Check to see if the ID passed is the master programing card
boolean isMaster( byte test[] ) {
  if ( checkTwo( test, masterCard ) )
    return true;
  else
    return false;
}

