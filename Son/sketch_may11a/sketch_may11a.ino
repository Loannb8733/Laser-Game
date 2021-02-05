#include <SoftwareSerial.h> // Librairie nécessaire à la création d'une liaison série virtuelle
#include <MP3Player_KT403A.h> // librairie spécifique au lecteur mp3

SoftwareSerial mp3(2,3); // Création d'une 2eme liaison permettant la com avec le lecteur mp3

void setup() 
{
  mp3.begin(9600); //Etablissement de la vitesse de com entre la carte arduino et le lecteur mp3
  Serial.begin(9600): //Etablissement de la vitesse de com entre la carte arduino et le moniteur serie
    delay(100); // Attendre 100ms
    SelectPlayerDevice(0x02); //Selectionner carte SD en tant que lecteur
    SetVolume(0x16); // Definir le volume, plage comprise entre 0x00 et 0x1E
}

void loop() 
{
  //Lecture de la msq par dosiier spécifié et index de fichier
  //Règles des noms de dossiers et de fichiers: 01/001***.Mp3
      SpecifyfolderPlay(01,001);
      SpecifyfolderPlay(01,002);
  
  //Aucun nom de dossier ni nom de fichier spécifié
  //Peut stocker des fichiers MP3 n'importe où dans la carte microSD
      SpecifyMusicPlay(001);
      SpecifyMusicPlay(003);
      SpecifyMusicPlay(005);
}
