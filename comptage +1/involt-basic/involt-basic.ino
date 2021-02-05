#include <SeeedOLED.h>

int    involtPin[14] = {}; //equals involt.pin.P in app
String involtString[2] ={}; //equals involt.pin.S in app
char involt[16];

String fname;

#include <Wire.h>
unsigned long debut;
unsigned long rebours;
unsigned long dureepartie;
unsigned long dureepause = 0;
unsigned long debutpause =0;

int minut ;
int seconde ;

#define bp 7
int compte = 0;
bool appui = 0;
#define bp2 3
int compte2 = 0;
bool appui2 = 0;
int compte3 = 100;
bool appui3 = 0;
int compte4 = 100;
bool appui4 = 0;
bool depart = 0;
bool pause = 0;
bool reprendrepartie = 0;



// ------- Loann BST ------


void setup() 

{
 Serial.begin(57600);
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
  delay(1000);
   debut = millis ();
pinMode (5, OUTPUT);

}



void loop() {
      
 // ----- loann BDR ------
 
      involtReceive();
        
        depart = involtPin[5]; //la variable depart est égale au bouton P5 chez HTML
        if (depart == 0) // si depart est egal à 0
        {
      do //lancer le compte à rebours
      {
        involtReceive();
        depart = involtPin[5]; 
        debut = millis ();
        digitalWrite (5, LOW); // la led comprise sur la broche D5 est éteinte
        
      } while (depart != HIGH); // tant que depart ne soit pas ré appuyer alors laisser le compte à rebours 
        }
      digitalWrite (5, HIGH); // allumer la LED comprise sur la broche 5
   

   ///////////////////////////
  /// COMPTAGE DES POINTS ///
 ///////////////////////////
 
  if (digitalRead(bp) == HIGH && appui == 0)
    {
      compte ++;
      appui  = 1;
    }
   else if (digitalRead(bp) == LOW && appui == 1)
    {
      appui = 0;
    }
   Serial.println (compte);
   involtSend(0, compte);
      
  if (compte > 100)
    {
      compte = 0;
    }

   if (digitalRead(bp2) == HIGH && appui2 == 0)
    {
      compte2 ++;
      appui2  = 1;
    }
   else if (digitalRead(bp2) == LOW && appui2 == 1)
    {
      appui2 = 0;
    }
   Serial.println (compte2);
   involtSend(1, compte2);

   if (compte2 > 100)
    {
      compte2 = 0;
    }

   if (digitalRead(bp) == HIGH && appui3 == 0)
      {
        compte3 --;
        appui3 = 1;
      }

    else if (digitalRead(bp) == LOW && appui3 == 1)
      {
        appui3 = 0;
      }
    Serial.println (compte3);
    involtSend(2, compte3);
    
    if (compte3 < 0)
      {
        compte3 = 100;
      }

    if (digitalRead(bp2) == HIGH && appui4 == 0)
      {
        compte4 --;
        appui4 = 1;
      }

    else if (digitalRead(bp2) == LOW && appui4 == 1)
      {
        appui4 = 0;
      }
    Serial.println (compte4);
    involtSend(3, compte4);
    
    if (compte4 < 0)
      {
        compte4 = 100;
      }


        
     
// Début du chronomètre

 dureepartie = ( millis() - debut  )/1000; // la variable dureepartie prend la valeur (millis - debut)/1000
        
        involtReceive();
        pause = involtPin[9]; //la variable depart est égale au bouton P9 chez HTML
        
       if (pause == HIGH ) // Si pause est égale à 1
        {
         debutpause = millis(); // debutpause est égal à millis
        
         do //faire
        {
         involtReceive();
         pause = involtPin[9];
         dureepause = millis() - debutpause ; //dureepause est égale millis - debutpause
        }while (pause != LOW); // tant que pause est différent 0
        debut = debut + dureepause; // alors debut est egal à la variable debut + duree pause
        }
 
 rebours = 600 - dureepartie  ;

 
 if(rebours > 1000) // si rebours est superieur à 100
  {
    rebours = 0; // alors rebours = 0
  }

 minut = rebours / 60 ; // Calcul de minute
 seconde = rebours % 60 ; // Le nombre de seconde est le reste de la division %
  /*
  SeeedOled.setTextXY(5,0);
  SeeedOled.putNumber(minute);
   SeeedOled.putString(" : ");
   SeeedOled.putNumber(seconde);
   */
  /* if (rebours == 0) 
    {
      dureepartie = 0;
    }
    */      


          involtSend(4,minut);
          involtSend(5,seconde);
          involtSend(6,rebours);
 


  
  //Clear the function to trigger it only once.
  fname = "";

        


       //reprendrepartie = involtPin[4]; //la variable depart est égale au bouton P5 chez HTML
        //if (reprendrepartie == 1) // si depart est egale à 0
       
}



/*
  INVOLT FUNCTIONS
  ------------------------------------------------------

  involtReceive
  ------------------------------------------------------ 
  read the data from app and parse the values received 
  into proper array. The read until is used due to
  issues with missing chars when reading direct strings.
  
  involtSend, involtSendString
  ------------------------------------------------------
  send int or string to app. Multiple prints are to
  reduce the sketch size (compared to sprintf()).

  involtSendFunction
  ------------------------------------------------------
  send function name to trigger it in app.
*/

void involtReceive(){
  if(Serial.available()>0) {
    Serial.readBytesUntil('\n',involt,sizeof(involt));
    int pin;
    if (involt[0] == 'P'){
      int value;
      sscanf(involt, "P%dV%d", &pin, &value);
      involtPin[pin] = value;
    }
    else if (involt[0] == 'S'){
      char value[sizeof(involt)];
      sscanf(involt, "S%dV%s", &pin, &value);
      involtString[pin] = value;
    }
    else if (involt[0] == 'F'){
      char value[sizeof(involt)];
      sscanf(involt, "F%s", &value);
      fname = value;
    };
    memset(involt,0,sizeof(involt));
  };
};

void involtSend(int pinNumber, int sendValue){
  Serial.print('A'); 
  Serial.print(pinNumber); 
  Serial.print('V'); 
  Serial.print(sendValue); 
  Serial.println('E');
  Serial.flush();
};

void involtSendString(int pinNumber, String sendString){
  Serial.print('A'); 
  Serial.print(pinNumber); 
  Serial.print('V'); 
  Serial.print(sendString); 
  Serial.println('E'); 
  Serial.flush();

};

void involtSendFunction(String functionName){
  Serial.print('F'); 
  Serial.print(functionName); 
  Serial.println('E'); 
  Serial.flush();
};
