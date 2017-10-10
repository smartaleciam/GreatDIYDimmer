#include <Wire.h>
#include <SPI.h>
#include <UsbFat.h>
#include <masstorage.h>
USB usb;
BulkOnly bulk(&usb);
UsbFat key(&bulk);
File file;

void save_file() {     // Test file.
     // How to write a file----Print a line to a test file.
  file.open("test file.txt", O_CREAT | O_RDWR);
  file.println("Hello USB");
  file.close();
 }

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
//  Wire.begin();    // join i2c bus ( as Master ) Arduino 2560 - Touch LCD
    Wire.begin(1);   // join i2c bus ( as Master )  Arduino Uno - USB Stick Recorder
//  Wire.begin(2);   // join i2c bus ( as Master ) Arduino 2560 - { 2x DMX, Pixel, Midi in/out } - Output Board
    Wire.onReceive(receiveI2C); // register event
  usb_scan();
 }

void receiveI2C(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

void usb_scan() {
  Serial.print(F("FreeRam "));  Serial.println(FreeRam());
  Serial.print(F("UsbFat version: "));  Serial.println(USB_FAT_VERSION); 
  //Serial.println(F("Type any character to begin"));  while (Serial.read() < 0) {};   // wait for any key to get pressed
  if (!initUSB(&usb)) {    Serial.println(F("USB Failed"));    return;      }  // Initialize the USB bus.
 
  if (!key.begin()) {    Serial.println(F("key.begin failed"));    return;  }  // Init the USB key or USB hard drive.

  Serial.print(F("\r\nVolume is FAT"));  Serial.println(int(key.vol()->fatType()));
  Serial.print(F("Volume Size: "));  Serial.print(0.000512*key.volumeBlockCount());  Serial.println(F(" MB"));
  Serial.println(F("Reading USB . .")); 
  uint32_t volFree = key.vol()->freeClusterCount(); 
  float fs = 0.000512*volFree*key.vol()->blocksPerCluster();
  Serial.print(F("Free Space:  "));  Serial.print(fs);  Serial.println(F(" MB"));
  Serial.println(F("---------------------------------------------------------------------"));
  key.ls(LS_A | LS_DATE | LS_SIZE);
  Serial.println(F("---------------------------------------------------------------------\r\n"));

  Serial.println(F("Volume initialized."));
  Serial.print(F("Volume Size: "));  Serial.print((key.volumeBlockCount()/1000)*512/1000);  Serial.println(F(" MB"));
  Serial.print(F("Volume is FAT"));  Serial.println(int(key.vol()->fatType()));
  Serial.print(F("blocksPerCluster: "));  Serial.println(int(key.vol()->blocksPerCluster()));
  Serial.print(F("clusterCount: "));  Serial.println(key.vol()->clusterCount());
  Serial.print(F("fatStartBlock: "));  Serial.println(key.vol()->fatStartBlock());
  Serial.print(F("fatCount: "));  Serial.println(int(key.vol()->fatCount()));
  Serial.print(F("blocksPerFat: "));  Serial.println(key.vol()->blocksPerFat());
  Serial.print(F("rootDirStart: "));  Serial.println(key.vol()->rootDirStart());
  Serial.print(F("dataStartBlock: "));  Serial.println(key.vol()->dataStartBlock());
  Serial.print(F("freeClusters: "));  Serial.println(volFree);
  Serial.print(F("freeSpace: "));  Serial.print(fs);  Serial.println(F(" MB"));

  }

void loop() {
  
  }
