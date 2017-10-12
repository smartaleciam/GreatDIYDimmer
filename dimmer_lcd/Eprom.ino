//
// EEPROM DB example
//
// This example creates a database, adds 10 records, and reads the 10 records
// displaying the results.  
//
/*
void eprom_startup()
{
#include "WProgram.h"
#include <EEPROM.h>
#include <DB.h>
#include <string.h>

DB db;

#define MY_TBL 1

struct MyRec {
  char date[11];
  char time[9];
  int temperature;
} 
myrec;

  Serial.println("EEPROM DB Library Demo");
  Serial.println();

  randomSeed(analogRead(0));

  Serial.print("Creating Table...");
  db.create(MY_TBL,sizeof(myrec));
  db.open(MY_TBL);
  Serial.println("DONE");

  Serial.print("Creating records...");
  for (int recno = 1; recno <= 5; recno++)
  {
    int m = random(1, 12);
    int d = random(1, 31);
    int h = random(1, 12);
    int i = random(59);
    int s = random(59);

    sprintf(myrec.date, "2009-%02d-%02d", m, d);
    sprintf(myrec.time, "%02d:%02d:%02d", h, i, s);
    myrec.temperature = random(-100, 100);
    Serial.print("CREATING RECNUM: "); Serial.println(recno);
    Serial.print("WRITING Date: "); Serial.println(myrec.date);
    Serial.print("WRITING Time: "); Serial.println(myrec.time);
    Serial.print("WRITING Temperature: "); Serial.println(myrec.temperature);
    db.append(DB_REC myrec);
    Serial.println("DONE");
  }
  Serial.println();
  Serial.println("Reading records from EEPROM...");
  Serial.println();
  selectAll();
}

void loop()
{
}

void selectAll()
{
  if (db.nRecs()) Serial.println("-----");
  for (int i = 1; i <= db.nRecs(); i++)
  {
    db.read(i, DB_REC myrec);
    Serial.print("Recnum: "); Serial.println(i); 
    Serial.print("Date: "); Serial.println(myrec.date); 
    Serial.print("Time: "); Serial.println(myrec.time);
    Serial.print("Temperature: "); Serial.println(myrec.temperature);
    Serial.println("-----");  
  } 
}
*/

