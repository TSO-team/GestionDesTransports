#ifndef MAIN_H
#define MAIN_H

//PROGRAMME: 247-637 S-0008
//DESCRIPTION: programme avec un service de base de temps et un service de
//  communication par lien série. Le programme execute plusieurs taches en
//  parallele. Un processus s'occupe de faire clignoter une DEL tandis qu'un
//  autre processus repond aux demandes que lui fait un module de developpement
//  stm32F4-Disco par lien serie.
//  Lorsqu'on appuie sur un bouton du STM32F4-Disco, celui-ci transmet un
//  message qui demande a l'ensemble Dallas de lui faire parvenir de
//  l'information a propos de l'etat de un de ses boutons de meme que d'autres
//  valeurs (on peut associer la demande a un remote request frame du protocole
//  CAN).
//  Le programme montre entre autres choses comment:
//  -integrer un protocole de communication dans un programme
//  -on convertit des valeurs entieres 16 bits en paires d'octets tout en
//   s'assurant que les premiers octets des paires representent les poids forts
//   des valeurs a transmettre alors que les deuxiemes octets representent les
//   poids faibles
//  -comment un message peut etre en partie construit par un module d'interface
//   sans l'intervention d'un processus quand c'est possible de le faire
//  -comment un processus peut inclure des donnees dans les messages a
//   transmettre
//  -comment on peut ajouter et gerer des informations de "debug" dans un code
//   a l'aide de definitions suggerees dans les .h des modules et definies ou
//   pas dans le fichier main.h
//  -comment proceder pour recuperer l'information recue par lien serie et la
//   valider avant de signaler que cette information est utilisable
//  -comment un module peut attendre qu'un autre module soit en fonction avant
//   de se mettre en fonction
//  -comment un module peut indiquer aux autres modules s'il est en fonction ou
//   pas

//HISTORIQUE:
// 2019-10-27, Yves Roy: création

//DEFINITIONS REQUISES PAR LE PROGRAMME:
#include <ioDS89C450.h>  //definitions pour acceder aux registres du DS89C450

//Dépendances matérielles:
#define MAIN_FREQUENCE_D_OSCILLATEUR_EN_KHZ  11059.2
#define PILOTEIOT1_SORTIE  P3_bit.P35_T1 
#define PILOTEIOB1_ENTREE  P3_bit.P32_INT0    
#define INTERFACEB1_VALEUR_LUE_SI_APPUYE  0   
#define INTERFACEB1_VALEUR_LUE_SI_RELACHE 1
#define INTERFACEB1_DELAI_ANTI_REBOND_EN_MS  15
#define INTERFACET1_VALEUR_POUR_ALLUMER  0   
#define INTERFACET1_VALEUR_POUR_ETEINDRE 1

//Dépendances logicielles:
#define FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ 2000.0
#define PILOTETIMER1MODE2_TAUX_DE_BITS 19200.0 //9600.0
#define PILOTETIMER1MODE2_UTILISE_LE_DOUBLEUR_DE_TAUX  1
#define INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ  100.0
#define INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10
#define PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS  500.0
#define PROCESSUSCLIGNOTANT_PERIODE_EN_MS 1000.0
#define SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_TRANSMISSIONS_EN_HZ 500.0
#define SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM  16
#define SERVICEPROTOCOLE637_DEBUT_DE_TRAME  '$'
#define SERVICEPROTOCOLE637_INSERTION 0x00
#define SERVICEPROTOCOLE637_TEMPS_D_ATTENTE_MAXIMAL_EN_MS 4
#define SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ 2000.0

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES  7
#define INTERFACEB1_PHASE 0
#define SERVICEPROTOCOLE637_PHASE_RECEPTION 1
#define INTERFACES0009_PHASE_RECEPTION 2
#define INTERFACES0009_PHASE_TRANSMISSION 5
#define SERVICEPROTOCOLE637_PHASE_TRANSMISSION 3
#define PROCESSUSBOUTONCONNECTE_PHASE 4
#define PROCESSUSCLIGNOTANT_PHASE 6

#define SERVICEPROTOCOLE637_DEBUG //activation de messages de debug

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define INFORMATION_DISPONIBLE  1
#define INFORMATION_TRAITEE  0
#define REQUETE_ACTIVE  1
#define REQUETE_TRAITEE 0
#define MODULE_EN_FONCTION 1
#define MODULE_PAS_EN_FONCTION 0

//Fonctions publiques:
void neFaitRien(void);

//Variables publiques:
//pas de variables publiques
#endif
