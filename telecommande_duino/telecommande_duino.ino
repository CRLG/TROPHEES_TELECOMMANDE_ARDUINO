#include <SoftwareSerial.h>
#include "messagerieTB.h"

#define RX 10
#define TX 11

#define up_button	8
#define down_button	A1
#define left_button	9
#define right_button	12

#define stick_button	A0
#define level_stick	A2
#define vertical_stick	A3

SoftwareSerial liaisonSerie(RX, TX); //on informe le microcontrôleur que l'on utilise ses broches RX et TX pour une connexion série
String DonneesLues; //variable pour stocker les données lues sur la liaison série (normalement pas utile pour la télécommande)

void setup() 
{
  //console série pour le debugage sur PC
  Serial.begin(9600);
  
  //on ouvre la communication série de la télécommande
  liaisonSerie.begin(9600);

  //on informe le microcontrôleur des boutons qui seront utilisés 
	pinMode(left_button, INPUT);
	pinMode(right_button, INPUT);
	pinMode(up_button, INPUT);
	pinMode(down_button, INPUT);

	pinMode(stick_button  , INPUT);
	pinMode(level_stick   , INPUT);
	pinMode(vertical_stick, INPUT);
}

//boucle qui est répétée indéfiniment
void loop()
{
  //on lit l'état des boutons
  int left_state = digitalRead (left_button);
  int right_state = digitalRead (right_button);
  int up_state = digitalRead (up_button);
  int down_state = digitalRead (down_button);
  int stick_state = digitalRead (stick_button);
  int level_value = analogRead (level_stick);
  int vertical_value = analogRead (vertical_stick);

  //si l'état d'un des boutons change on envoit une donnée sur le port série
  if(up_state==0)
  {
    Serial.println("HAUT (JAUNE)");
    liaisonSerie.write(MESSAGE_JAUNE);
  }
    
  if(down_state==0)
  {
    Serial.println("BAS (VERT)");
    liaisonSerie.write(MESSAGE_VERT);
  }
  if(left_state==0)
  {
  Serial.println("GAUCHE (BLEU)");
      liaisonSerie.write(MESSAGE_BLEU);
  }
  if(right_state==0)
  {
  Serial.println("DROITE (ROUGE)");
      liaisonSerie.write(MESSAGE_ROUGE);
  }
  
  if((vertical_value!=502)||(level_value!=513))
  {
    Serial.print("JOYSTICK V: ");
    Serial.print(vertical_value);
    Serial.print("\tH: ");
    Serial.println(level_value);
  }
  if(stick_state==0)
  Serial.println("JOYSTICK CLICK");
  
  delay (500);
}
