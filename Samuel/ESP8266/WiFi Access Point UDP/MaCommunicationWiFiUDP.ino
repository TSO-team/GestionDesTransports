#define DEBUG

//#include <ESP8266WiFi.h>
#include <WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266mDNS.h>
//#include <ESP8266WebServer.h>
#include <WiFiUdp.h>


#include "MaCommunicationWiFiUDP.h"

const char *ssid = "etudiant10";
const char *motDePasse = "12345678";
const int tempsMaximumSansConnexion = 1000;
const unsigned int portLocal = 8000;

const char messageDeTypeStandard = 0; //message par defaut: type=0 suivi de 5 donnees
const char messageDErreur = 1;        //message d'erreur: type=1 suivi de 5 lettres
const int longueurMaximumDesTransmissions = 128;
const int longueurMaximumDesReceptions = 128;
const int longueurStandardDesTransmissions= 8;
const int longueurStandardDesReceptions = 8;

long tempsDeLaDerniereConnexion;
WiFiUDP udp;
byte tamponDeTransmission[longueurMaximumDesTransmissions];
byte tamponDeReception[longueurMaximumDesReceptions];


void configureLeWiFiEnPointDAccesAvecUDP()
{
#ifdef DEBUG
 Serial.begin(115200);
#endif

  
  WiFi.mode(WIFI_AP);  
  WiFi.softAP(ssid, motDePasse);
  WiFi.begin (ssid, motDePasse);
  WiFi.config(IPAddress(192, 168, 0, 100),  IPAddress(192, 168, 0, 1), IPAddress(255, 255, 255, 0));
  udp.begin(portLocal);  
 
#ifdef DEBUG
  WiFi.printDiag(Serial); //pour avoir de l'information a  propos de l'acces point
#endif  
}

#if 0
xxx
  Serial.println("Configuring Wifi");
  WiFi.begin (config.ssid.c_str(), config.password.c_str());
  if (!config.dhcp)
  {
    WiFi.config(IPAddress(config.IP[0],config.IP[1],config.IP[2],config.IP[3] ),  IPAddress(config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3] ) , IPAddress(config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3] ));
  }

xxx
#endif



boolean detecteUnProblemeDeConnexion() {
  long tempsPresent = millis();
  if (tempsPresent - tempsDeLaDerniereConnexion > tempsMaximumSansConnexion)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void transmetUnMessageUDP(int longueurDuMessage)
{
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.write(tamponDeTransmission, longueurDuMessage);
    udp.endPacket();
#ifdef DEBUG
    Serial.printf("Message:");
    for (int i=0; i < longueurDuMessage; i++)
    {
      Serial.printf("\t %03d,", tamponDeTransmission[i]);
    }
    Serial.printf("\n");
#endif
}

int recoitUnMessageUDP()
{
  int nombreDOctetsRecus = udp.parsePacket();
  if (nombreDOctetsRecus > longueurMaximumDesReceptions)
  {
#ifdef DEBUG    
        Serial.printf("trop long %03d\n", nombreDOctetsRecus);    
#endif
    return 0; //ignore les paquets trop longs
  }
  else
  {
    if (nombreDOctetsRecus)
   {
      udp.read(tamponDeReception, nombreDOctetsRecus);
#ifdef DEBUG
      Serial.printf("Reception:");
      for (int i=0; i < nombreDOctetsRecus; i++)
      {
        Serial.printf("\t %03d,", tamponDeReception[i]);
      }
      Serial.printf("\n");
#endif      
      udp.flush();
    }
    return nombreDOctetsRecus;      
  }  
}

void repondAUnMessageStandard()
{
  for (byte i = 0; i < longueurStandardDesTransmissions; i++)
  {
    tamponDeTransmission[i] = tamponDeReception[i];
  }
  transmetUnMessageUDP(longueurStandardDesTransmissions);
}

void repondAUnMessageDeTypeInconnu()
{
  tamponDeTransmission[0] = messageDErreur;
  for (byte i = 1; i < longueurStandardDesTransmissions; i++)
  {
    tamponDeTransmission[i] = '?';
  }
}
