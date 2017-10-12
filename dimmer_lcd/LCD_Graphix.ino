// all the fancy graphical Lcd pictures, referanced from other areas of code
// can load graphic's an stuff from SD Card
// should dmx modules be stored on the sd card?
// should USB data be able to be backed up to sd card

void introscreen()
{
  // Clear the screen and draw the frame
  myGLCD.setColor(255,255,255);
  myGLCD.fillRect(1,15,478,304);

// Draw some lines in a pattern
  myGLCD.setColor (255,0,0);
  for (int i=15; i<304; i+=5)  {    myGLCD.drawLine(1, i, (i*1.6)-10, 304);  }
  myGLCD.setColor (255,0,0);
  for (int i=304; i>15; i-=5)  {    myGLCD.drawLine(478, i, (i*1.6)-11, 15);  }
  myGLCD.setColor (0,255,255);
  for (int i=304; i>15; i-=5)  {    myGLCD.drawLine(1, i, 491-(i*1.6), 15);  }
  myGLCD.setColor (0,255,255);
  for (int i=15; i<304; i+=5)  {    myGLCD.drawLine(478, i, 490-(i*1.6), 304);  }
  delay (5000);  myGLCD.clrScr();
}

