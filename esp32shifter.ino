// Animated GIF with Round Display
//
// ESP32 40MHz SPI single frame rendering performance

#include <SPI.h>
#include <TFT_eSPI.h>     // Install this library with the Arduino IDE Library Manager
                          // Don't forget to configure the driver for the display!
                          
#include <AnimatedGIF.h>  // Install this library with the Arduino IDE Library Manager
AnimatedGIF gif;



#include "images/kia.h"


#define GIF_IMAGE kia

#include "NotoSansBold15.h"
#include "NotoSansBold36.h"

// The font names are arrays references, thus must NOT be in quotes ""
#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_LARGE NotoSansBold36
int rectX=45;
int rectY=120;
int delayTime = 20;
int gear1StartX=rectX+35;

int lineW=8;
int lineH=45;
int gearGap=45;
int topGearstarty=rectY-lineH;
int botGearstarty=rectY+lineW;
int lastGear=0;

TFT_eSPI tft = TFT_eSPI();
void fillRectSlow(int x, int y, int w, int h, int d){
  // d Direction 1,2,3,4, Up, Down, Left Right
  if(d==1){

    for(int i=0;i<h; i=i+2){
      tft.fillRect(x,y+h-i,w,i,TFT_WHITE);
      // Serial.print(i,DEC);

      delay(delayTime);
    }
  }
  if(d==2){
    for(int i=0;i<h; i=i+2){
      tft.fillRect(x,y+i,w,2,TFT_WHITE);
      // Serial.print(i,DEC);

      delay(delayTime);
    }
  }
  if(d==3){
    for(int i=0;i<w; i=i+2){
      tft.fillRect(x+w-i,y,i,h,TFT_WHITE);
      // Serial.print(i,DEC);

      delay(delayTime);
    }
  }
  if(d==4){
    for(int i=0;i<w; i=i+2){
      tft.fillRect(x+i,y,i,h,TFT_WHITE);
      // Serial.print(i,DEC);

      delay(delayTime);
    }
    }
}
void printgearnumber(int g){

switch(g){

  case 1:
      tft.drawString("1", gear1StartX, topGearstarty-30);
      break;

  case 2:
        tft.drawString("2", gear1StartX, botGearstarty+lineH+30);
        break;

  case 3:      
      tft.drawString("3", gear1StartX+gearGap, topGearstarty-30);
      break;

  case 4:
      tft.drawString("4", gear1StartX+gearGap, botGearstarty+lineH+30);
      break;

  case 5:
      tft.drawString("5", gear1StartX+gearGap+gearGap, topGearstarty-30);
      break;

  case 6:
      tft.drawString("6", gear1StartX+gearGap+gearGap, botGearstarty+lineH+30);
      break;

  case 7:
      tft.drawString("R", rectX, topGearstarty-30);
      break;




}
}
void setGear(int gear){
if (lastGear==gear){return;}
if (lastGear==0){
      tft.setTextColor(TFT_RED, TFT_BLACK); // Set the text color to white with black background
       printgearnumber(gear);
       lastGear=gear;
}else{
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
 printgearnumber(lastGear);
       tft.setTextColor(TFT_RED, TFT_BLACK); // Set the text color to white with black background
       printgearnumber(gear);
       lastGear=gear;
}


}

void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(2);     // Adjust Rotation of your screen (0-3)
  tft.fillScreen(TFT_BLACK);
  
  gif.begin(BIG_ENDIAN_PIXELS);

    if (gif.open((uint8_t *)GIF_IMAGE, sizeof(GIF_IMAGE), GIFDraw))
  {
    Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
    tft.startWrite();
    while (gif.playFrame(true, NULL))
    {
      yield();
    }
    gif.close();
    tft.endWrite(); 
  }
  
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set the text color to white with black background
 // tft.loadFont(AA_FONT_SMALL); // Load a small anti-aliased font
  tft.loadFont(AA_FONT_LARGE); // Load a small anti-aliased font

// Draw numbers and lines

tft.fillRect(rectX,rectY,gear1StartX+gearGap+gearGap+lineW-rectX,lineW,TFT_WHITE); //midle line
fillRectSlow(gear1StartX,topGearstarty,lineW,lineH,1);//1
 printgearnumber(1);
fillRectSlow(gear1StartX,botGearstarty,lineW,lineH,2);//2
 printgearnumber(2);
fillRectSlow(gear1StartX+gearGap,topGearstarty,lineW,lineH,1);//3
 printgearnumber(3);
fillRectSlow(gear1StartX+gearGap,botGearstarty,lineW,lineH,2);//4
 printgearnumber(4);
fillRectSlow(gear1StartX+gearGap+gearGap,topGearstarty,lineW,lineH,1);//5
 printgearnumber(5);
fillRectSlow(gear1StartX+gearGap+gearGap,botGearstarty,lineW,lineH,2);//6
 printgearnumber(6);
fillRectSlow(rectX,topGearstarty,lineW,lineH,1);//R
 printgearnumber(7);
pinMode(19, INPUT_PULLUP);
}


void loop()
{
/*

            setGear(1);
                  delay(1000);
            setGear(2);
                  delay(1000);
            setGear(3);
                  delay(1000);
            setGear(4);
                  delay(1000);
            setGear(5);
                  delay(1000);
            setGear(6);
                  delay(1000);
            setGear(7);
                  delay(1000);

                  */




int sensorValue = digitalRead(19);
if (sensorValue == LOW){
  setGear(1);

}else{
  setGear(6);
}
delay(100);



}