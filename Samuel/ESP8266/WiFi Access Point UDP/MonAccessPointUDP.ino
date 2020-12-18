#define DEBUG
// Le programme gère la réception des messages UDP par un Access Point. Si un message UDP est reçu et que
// la première valeur du message indique qu'il est de type standard, il y a gestion des accessoires
// du moteur, de la direction du véhicule, de la vitesse et du sens de rotation du moteur. Si le type
// de message n'est pas reconnu ou s'il y a perte de connexion, le véhicule s'arrête.
// La reconnaissance du type de message est faite pour réduire les risques que le véhicule réponde
// de façon aléatoire a des messages qui ne lui seraient pas destinés.
// Le format des messages est tel que:
// tamponDeReception[0] = type de message
// tamponDeReception[1] = bouton A
// tamponDeReception[2] = bouton B
// tamponDeReception[3] = bouton C


#include "MaCommunicationWiFiUDP.h"
#include "MaGestionDeAccessPoint.h"

unsigned char messageAbsent[] = "AP: Pas de message";

void setup() {
  initialiseLaGestionDeAccessPoint();
  configureLeWiFiEnPointDAccesAvecUDP();
}


void loop() {

  int nombreDOctetsRecus = recoitUnMessageUDP();
  if (nombreDOctetsRecus)
  {
    if (tamponDeReception[0] == messageDeTypeStandard)
    {
      repondAUnMessageStandard();
      afficheLeMessageRecu(tamponDeReception, 4);
    }
    else
    {
      repondAUnMessageDeTypeInconnu();
      afficheErreur();
    }
    tempsDeLaDerniereConnexion = millis();    
  }
  else
  {
    if (detecteUnProblemeDeConnexion())
    {
      afficheMessageAbsent();
    }    
  }
}
