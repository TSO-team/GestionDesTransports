#ifndef MA_COMMUNICATION_WIFI_UDP
 #define MA_COMMUNICATION_WIFI_UDP

//VARIABLES POUR LA COMMUNICATION
extern const char messageDeTypeStandard; //message par defaut: type=0 suivi de 5 donnees
extern const char messageDErreur;        //message d'erreur: type=1 suivi de 5 lettres
extern byte tamponDeTransmission[];
extern byte tamponDeReception[];
extern long tempsDeLaDerniereConnexion;

//CODE POUR LA COMMUNICATION
void initialiseLaFlash(void);
void configureLeWiFiEnPointDAccesAvecUDP();
boolean detecteUnProblemeDeConnexion();
void transmetUnMessageUDP(int longueurDuMessage);
int recoitUnMessageUDP();
void repondAUnMessageStandard();
void repondAUnMessageDeTypeInconnu();
#endif
