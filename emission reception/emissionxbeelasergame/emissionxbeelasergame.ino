#include <SoftwareSerial.h> 
int i; // et du compteur
int tableau[3] = {1,0,0}; //déclaration du tableau
bool appui2 = LOW ;
bool appui3 = LOW ;
int tirs1 = 0 ;
int tirs2 = 0 ;
int touches1 = 0 ;
int touches2 = 0 ;

void setup()
{
Serial.begin(9600);
pinMode(4, INPUT);
pinMode(3, INPUT);
}
void loop()
{
  bool button4 = digitalRead(4);
  delay(10);
  bool button3 = digitalRead(3);
delay(10);

  if ((button4 == HIGH) && (appui2 == LOW))
    {
      appui2 = HIGH ;
      tirs1 = tirs1 + 1;
      touches2 = touches2 +1 ;
      Serial.write(1);
      Serial.write(tirs1);
      Serial.write(touches1);
//Serial.flush();
    }
  if ((button4 == LOW) && (appui2 == HIGH))
    {
      appui2 = LOW ;
    }

if ((button3 == HIGH) && (appui3 == LOW))
    {
      appui3 = HIGH ;
      tirs2 = tirs2 + 1;
      touches1 = touches1 +1 ;
      Serial.write(2);
      Serial.write(tirs2);
      Serial.write(touches2);
    //Serial.flush();
    }
  if ((button3 == LOW) && (appui3 == HIGH))
    {
      appui3 = LOW ;
    }
        


}
