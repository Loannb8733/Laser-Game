#include <SoftwareSerial.h>     //Librairie nécessaire à la création d'une liaison série virtuelle
SoftwareSerial Xbee(2, 3);      //Création d'une deuxième liaison série permettant 
                                //la communication avec le lecteur mp3

#include <SeeedOLED.h>        //Librairie nécessaire pour l'affichage sur l'ecran lcd

int involtPin[14] = {};    //equals involt.pin.P in app
String involtString[2] ={};   //equals involt.pin.S in app
char involt[16];

String fname;


#include <Wire.h>               //Permet de communiquer avec les composants utilisant l'I2C
unsigned long debut;            //La variable debut est une variable non signée très grande qui ne stocke pas de nombre négatifs et codé sur 32 bits
unsigned long rebours;          //La variable rebours est une variable non signée très grande qui ne stocke pas de nombre négatifs et codé sur 32 bits
unsigned long dureepartie;      //La variable dureepartie est une variable non signée très grande qui ne stocke pas de nombre négatifs et codé sur 32 bits
unsigned long dureepause = 0;   //La variable dureepause prend la valeur 0 et est une variable non signée très grande qui ne stocke pas de nombre négatifs et codé sur 32 bits
unsigned long debutpause = 0;   //La variable debutpause prend la valeur 0 et est une variable non signée très grande qui ne stocke pas de nombre négatifs et codé sur 32 bits

int minut ;                   //Déclaration de la variable de type int appelé minut. Cette variable stocke une valeur sur 2 octets, des valeurs negatives comme positives
int seconde ;                 //Déclaration de la variable de type int appelé seconde. Cette variable stocke une valeur sur 2 octets, des valeurs negatives comme positives
bool depart = 0;              //La variable de type bool appelé depart peut prendre que 2 valeurs 0 ou 1 où HIGH ou LOW
bool pause = 0;               //La variable de type bool appelé pause peut prendre que 2 valeurs 0 ou 1 où HIGH ou LOW
bool reprendrepartie = 0;     //La variable de type bool appelé dureepartie peut prendre que 2 valeurs 0 ou 1 où HIGH ou LOW

int touches;             //Déclaration de la variable de type int appelé touches. Cette variable stocke une valeur sur 2 octets, des valeurs negatives comme positives
int tirs;                //Déclaration de la variable de type int appelé tirs. Cette variable stocke une valeur sur 2 octets, des valeurs negatives comme positives
int tirs1 = 0;           //Déclaration de la variable de type int appelé tirs1 et prend la valeur 0. Cette variable stocke une valeur sur 2 octets, des valeurs negatives comme positives
int tirs2 = 0;          //Déclaration de la variable de type int appelé tirs2 et prend la valeur 0. Cette variable stocke une valeur sur 2 octets, des valeurs negatives comme positives
int touches1 = 100;      //Déclaration de la variable de type int appelé touches1 et prend la valeur 100. Cette variable stocke une valeur sur 2 octets, des valeurs negatives comme positives
int touches2 = 100;       //Déclaration de la variable de type int appelé touches2 et prend la valeur 100. Cette variable stocke une valeur sur 2 octets, des valeurs negatives comme positives
int recue ;              //Déclaration de la variable de type int appelé recue. Cette variable stocke une valeur sur 2 octets, des valeurs negatives comme positives


void setup() 

{
 
 Serial.begin(57600);     //Vitesse de transmission de données en série en bits par seconde
 Wire.begin();            //Configure la carte Arduino pour utiliser les fonctions I2C
   debut = millis ();     //Recoie le nombre de ms écoulées depuis que la carte A commencé à exécuter le programme
  pinMode (5, OUTPUT);    //Configure la broche 5 en sortie

    Xbee.begin(9600);      //Etablissement de la vitesse de communication entre la carte arduino et le lecteur mp3
    Serial.begin(57600);   //Etablissement de la vitesse de communication entre la carte arduino et le moniteur série
    delay(100);            //Attendre 100ms

}



void loop() {
 
      involtReceive();
        
        depart = involtPin[5];  
          //la variable depart est égale au bouton P5 chez HTML
        
        if (depart == 0)//si depart est egal à 0
        {
      do  //lancer le compte à rebours
      {
        involtReceive();
        depart = involtPin[5]; 
        debut = millis ();
        digitalWrite (5, LOW); 
          // la led comprise sur la broche D5 est éteinte
        
      } while (depart != HIGH); 
        // tant que depart ne soit pas ré appuyer alors 
        // laisser le compte à rebours 
        }
      
   

if (Xbee.available() != 0) // tant qu'il y a quelque chose à lire
{
  while(Xbee.available() == 0) ; //Renvoie le nombre d'octet qu'il reste à lire
  recue = Xbee.read();          //on lit le caractère reçu
  
  while(Xbee.available() == 0) ;
  tirs = Xbee.read();
  
  while(Xbee.available() == 0) ;
  touches = Xbee.read();
  
    if (recue == 1) 
      {
        tirs1 = tirs;
        touches1 = touches ;
      }
      if (recue == 2) 
      {
        tirs2 = tirs;
        touches2 = touches ;
      }
    
    //tirs1 = tirs;       //tirs1 prend la valeur de tirs
    //touches1 = touches; //touches1 prends la valeur de touches 
  
  //tirs2 = tirs;       //tirs2 prend la valeur de tirs
  //touches2 = touches; //touches2 prends la valeur de touches
 }

Xbee.flush(); // Attend que la transmission des données séries sortantes s'achève
    
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
        }while (pause != LOW);                //tant que pause est différent 0
        debut = debut + dureepause;           //alors debut est egal à la variable debut + duree pause
        }
 
 dureepartie = ( millis() - debut  )/1000; 
 // la variable dureepartie prend la valeur (millis - debut)/1000
 rebours = 600 - dureepartie  ;
 if(rebours > 1000) // si rebours est superieur à 100
  {
    rebours = 0; // alors rebours = 0
  }
 minut = rebours / 60 ; // Calcul de minute
 seconde = rebours % 60 ; // Le nombre de seconde est le reste de la division %

          involtSend(4,minut);    //minut correspond à la pin 4 et envoie la valeut chez HTML
          involtSend(5,seconde);  //seconde correspond à la pin 5 et envoie la valeut chez HTML
          involtSend(6,rebours);  //rebours correspond à la pin 6 et envoie la valeut chez HTML

          involtSend(1,tirs1);    //tirs1 correspond à la pin 1 et envoie la valeut chez HTML
          involtSend(2,tirs2);    //tirs2 correspond à la pin 2 et envoie la valeut chez HTML
          involtSend(3,touches1); //touches1 correspond à la pin 3 et envoie la valeut chez HTML
          involtSend(7,touches2); //touches2 correspond à la pin 7 et envoie la valeut chez HTML
          
 


  
  //Clear the function to trigger it only once.
  fname = "";

        
       
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
