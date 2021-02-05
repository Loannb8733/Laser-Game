#include <SeeedOLED.h>

#include <Wire.h>
#include <SeeedOLED.h>
unsigned long debut;
unsigned long rebours;
unsigned long dureepartie;

int minute ;
int seconde ;
 
void setup()
{
  Wire.begin();
  SeeedOled.init();  //initialze SEEED OLED display

  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode
  SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
  SeeedOled.putString("BOUBOU"); //Print the String
  SeeedOled.setTextXY(1,0);
  SeeedOled.putString("BUBU");
  SeeedOled.setTextXY(3,0);
  SeeedOled.putString("compte a rebours");
    debut = millis ();
  
}

void loop()
{
 dureepartie = (millis() - debut)/1000;
 rebours = 600 - dureepartie ;
 minute = rebours / 60 ; // Calcul de minute
 seconde = rebours % 60 ; // Le nombre de seconde est le reste de la division %
  SeeedOled.setTextXY(5,0);
  SeeedOled.putNumber(minute);
   SeeedOled.putString(" : ");
   SeeedOled.putNumber(seconde);
   if (rebours = 0) dureepartie = 0;
}
   
    
  
