#include <SoftwareSerial.h>
#include "messagerieTB.h"

//pour debuguer le programme, mettre à true
#define DEBUG false

//définition des pinoches servant à la liaison série permettant de communiquer avec le robot
#define RX 10
#define TX 11

//définition des pinoches pour les boutons
#define bouton_jaune	8
#define bouton_vert	A1
#define bouton_bleu	9
#define bouton_rouge	12
//définition des pinoches pour le joystick
#define click_joystick	A0
#define gauche_droite_joystick	A3
#define avant_arriere_joystick	A2

SoftwareSerial liaisonSerie(RX, TX); //on informe le microcontrôleur que l'on utilise ses broches RX et TX pour une connexion série
String DonneesLues; //variable pour stocker les données lues sur la liaison série (normalement pas utile pour la télécommande)

void setup() 
{
  //console série pour le debugage sur PC
  if(DEBUG) Serial.begin(9600);
  
  //on ouvre la communication série de la télécommande
  liaisonSerie.begin(9600);

  //on informe le microcontrôleur des boutons qui seront utilisés 
	pinMode(bouton_bleu, INPUT);
	pinMode(bouton_rouge, INPUT);
	pinMode(bouton_jaune, INPUT);
	pinMode(bouton_vert, INPUT);
	pinMode(click_joystick  , INPUT);
	pinMode(avant_arriere_joystick   , INPUT);
	pinMode(gauche_droite_joystick, INPUT);
}

//boucle qui est répétée indéfiniment
void loop()
{
  //on lit l'état des boutons et du joystick
  int etat_bouton_bleu = digitalRead (bouton_bleu);
  int etat_bouton_rouge = digitalRead (bouton_rouge);
  int etat_bouton_jaune = digitalRead (bouton_jaune);
  int etat_bouton_vert = digitalRead (bouton_vert);
  int etat_click_joystick = digitalRead (click_joystick);
  int etat_avant_arriere_joystick = analogRead (avant_arriere_joystick);
  int etat_gauche_droite_joystick = analogRead (gauche_droite_joystick);
  
  //si l'état d'un des boutons change on envoit une donnée sur le port série
  if(etat_bouton_jaune==0)
  {
    if(DEBUG) Serial.println("HAUT (JAUNE)");
    liaisonSerie.write(MESSAGE_JAUNE);
    delay(200); //petit delai pour laisser le temps au doigt de se retirer du bouton
  }
  if(etat_bouton_vert==0)
  {
    if(DEBUG) Serial.println("BAS (VERT)");
    liaisonSerie.write(MESSAGE_VERT);
    delay(200); //petit delai pour laisser le temps au doigt de se retirer du bouton
  }
  if(etat_bouton_bleu==0)
  {
    if(DEBUG) Serial.println("GAUCHE (BLEU)");
    liaisonSerie.write(MESSAGE_BLEU);
    delay(200); //petit delai pour laisser le temps au doigt de se retirer du bouton
  }
  if(etat_bouton_rouge==0)
  {
    if(DEBUG) Serial.println("DROITE (ROUGE)");
    liaisonSerie.write(MESSAGE_ROUGE);
    delay(200); //petit delai pour laisser le temps au doigt de se retirer du bouton
  }
  if(etat_click_joystick==0)
  {
    if(DEBUG) Serial.println("JOYSTICK CLICK");
    liaisonSerie.write(MESSAGE_CLICK);
    delay(200); //petit delai pour laisser le temps au doigt de se retirer du bouton
  }

  //si l'état du joystick change on envoit une donnée sur le port série
  if(((etat_gauche_droite_joystick<=450)||(etat_gauche_droite_joystick>=550))||
        ((etat_avant_arriere_joystick<=450)||(etat_avant_arriere_joystick>=550)))
  {
    //etat_gauche_droite_joystick
    //gauche: entre 512 et 1023 (max=1023)
    //droite: entre 0 et 512 (max=0)
    if(etat_gauche_droite_joystick>=900)
    {
      if(DEBUG) Serial.println("GAUCHE");
      liaisonSerie.write(MESSAGE_GAUCHE_RAPIDE);
    }
    if((etat_gauche_droite_joystick>=550)&&(etat_gauche_droite_joystick<900))
    {
      liaisonSerie.write(MESSAGE_GAUCHE_LENT);
    }
    if((etat_gauche_droite_joystick>100)&&(etat_gauche_droite_joystick<=450))
    {
      liaisonSerie.write(MESSAGE_DROITE_LENT);
    }
    if(etat_gauche_droite_joystick<=100)
    {
      if(DEBUG) Serial.println("DROITE");
      liaisonSerie.write(MESSAGE_DROITE_RAPIDE);
    }
    
    //etat_avant_arriere_joystick
    //avant: entre 0 et 512 (max=0)
    //arriere: entre 512 et 1023 (max=1023)
    if(etat_avant_arriere_joystick>=900)
    {
      if(DEBUG) Serial.println("ARRIERE");
      liaisonSerie.write(MESSAGE_ARRIERE_RAPIDE);
    }
    if((etat_avant_arriere_joystick>=550)&&(etat_avant_arriere_joystick<900))
    {
      liaisonSerie.write(MESSAGE_ARRIERE_LENT);
    }
    if((etat_avant_arriere_joystick>100)&&(etat_avant_arriere_joystick<=450))
    {
      liaisonSerie.write(MESSAGE_AVANT_LENT);
    }
    if(etat_avant_arriere_joystick<=100)
    {
      if(DEBUG) Serial.println("AVANT");
      liaisonSerie.write(MESSAGE_AVANT_RAPIDE);
    }
  }
  if(((etat_gauche_droite_joystick>450)&&(etat_gauche_droite_joystick<550))&&
        ((etat_avant_arriere_joystick>450)&&(etat_avant_arriere_joystick<550)))
  {
    liaisonSerie.write(MESSAGE_STOP);
    delay(30); //pour ne pas surcharger la liaison série
    if(DEBUG)
    {
      Serial.println("STOP");
      delay(1000);
    }
  }


}
