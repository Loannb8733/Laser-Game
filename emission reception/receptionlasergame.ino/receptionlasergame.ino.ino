
#include <SoftwareSerial.h> // Librairie nécessaire à la création d'une liaison série virtuelle

// Note: You must define a SoftwareSerial class object that the name must be mp3, 
//       but you can change the pin number according to the actual situation.
SoftwareSerial Xbee(2, 3); // Création d'une deuxième liaison série permettant la communication avec le lecteur mp3 
int tirs1 = 0 ;
int tirs2 = 0;
int touches1 = 0;
int touches2 = 0;
int recue ;

void setup()
{
    Xbee.begin(9600);      // Etablissement de la vitesse de communication entre la carte arduino et le lecteur mp3
    Serial.begin(9600);   // Etablissement de la vitesse de communication entre la carte arduino et le moniteur série
    delay(100);
}

void loop()
{
  // Play music by specified folder and file index.
  //Folder and files' names rules: 01/001***.mp3  
  
if (Xbee.available() != 0) // tant qu'il y a quelque chose à lire
{
  while(Xbee.available() == 0) ;
  recue = Xbee.read(); //on lie le caractère reçut
  while(Xbee.available() == 0) ;
  tirs1 = Xbee.read();
  while(Xbee.available() == 0) ;
  touches1 = Xbee.read();

      Serial.print("recue : ");
      Serial.println(recue);
      
      Serial.print("tirs1 : ");
      Serial.println(tirs1);
      Serial.print("touches1 : ");
      Serial.println(touches1);

}

Serial.println("et là Arduino fait ce qu'il veut ");
  
  Xbee.flush();
}
