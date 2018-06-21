
void TOUCHED(int currentPage) { 
  int y;
   if (currentPage == 1) {
// Serial.print("currentPage "); Serial.println(currentPage); 
     TSPoint p = ts.getPoint();
//   Serial.print("x line : ");   Serial.print(p.x);   Serial.print(" : y line : ");   Serial.print(p.y);   Serial.print(" | Pressure line : ");   Serial.println(p.z);
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
   x=p.x;
   y=p.y;
   Serial.print("x line : ");   Serial.print(p.x);   Serial.print(" : y line : ");   Serial.print(p.y);   Serial.print(" | Pressure line : ");   Serial.println(p.z);
   // If we press the RGB LED Control Button 
          if ((x>=35) && (x<=700) && (y>=500) && (y<=600)) {
            drawFrame(35, 140, 285, 180);
 //           currentPage = '2';
           // myGLCD.clrScr();
 //          myGLCD.fillScreen(BLACK); drawLedControl();
         }
    }
  }
      // RGB LED Control 
  if (currentPage == 2) {
//    setLedColor();
       TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        x=p.x;
        y=p.y;        
         //Back button
            if ((x>=10) && (x<=60) &&(y>=10) && (y<=36)) {
              drawFrame(10, 10, 60, 36);
              currentPage = '0';
              myGLCD.fillScreen(BLACK); refresh=1; introscreen();
           }
        }
   }
    //==== This section of the code, for the game example, is explained in my next tutorial
    TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        x=p.x;
        y=p.y;        
            if ((x>=10) && (x<=60) &&(y>=10) && (y<=36)) {
              drawFrame(10, 10, 60, 36);
              currentPage = '0';
              myGLCD.fillScreen(BLACK);  refresh=1; introscreen();
          }
      }
}

    
    // ====== Custom Funtions ======
     void drawFrame(int x1, int y1, int x2, int y2) {
      myGLCD.setColor(255, 0, 0);
      myGLCD.drawRoundRect (x1, y1, x2, y2);
     TSPoint p = ts.getPoint();
 //   while (p.z > MINPRESSURE && p.z < MAXPRESSURE)
        x=p.x;
        y=p.y;        
        myGLCD.setColor(255, 255, 255);
        myGLCD.drawRoundRect (x1, y1, x2, y2);
    }

