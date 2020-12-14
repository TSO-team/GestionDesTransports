//serviceProtocole637:
//Historique: 
// 2018-10-28, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteUART0.h"
#include "piloteUART2.h"
#include "serviceBaseDeTemps.h"
#include "serviceProtocole637.h"

//Definitions privees
#define SERVICEPROTOCOLE637_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_TRANSMISSION (\
    FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
    /SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_TRANSMISSIONS_EN_HZ )
#define SERVICEPROTOCOLE637_TRANSMISSION_PERMISE 1
#define SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE 0
#define SERVICEPROTOCOLE637_RECEPTION_PERMISE 1
#define SERVICEPROTOCOLE637_RECEPTION_RETARDEE 0
#define SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE 0
#define SERVICEPROTOCOLE637_LECTURE_DISPONIBLE 1
#define SERVICEPROTOCOLE637_COMPTE_MAXIMAL_ENTRE_LES_RECEPTIONS (\
    SERVICEPROTOCOLE637_TEMPS_D_ATTENTE_MAXIMAL_EN_MS \
    * SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ / 1000.0)
#define SERVICEPROTOCOLE637_TEMPS_DEPASSE 1
#define SERVICEPROTOCOLE637_TEMPS_PAS_DEPASSE 0
#define SERVICEPROTOCOLE637_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_RECEPTION (\
    FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
    /SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ)
//Declarations de fonctions privees:
void serviceProtocole637_attendUneRequete(void);
void serviceProtocole637_transmetLaLongueur(void);
void serviceProtocole637_transmetUneDonnee(void);
void serviceProtocole637_transmetUnZero(void);
void serviceProtocole637_transmetUnChecksum(void);
unsigned char serviceProtocole637_gereLaSynchronisationDesTransmissions(void);
void serviceProtocole637_attendUnDebut(void);
void serviceProtocole637_attendLaLongueur(void);
void serviceProtocole637_attendUneDonnee(void);
void serviceProtocole637_attendUnZero(void);
void serviceProtocole637_attendUnChecksum(void);
unsigned char serviceProtocole637_gereLaSynchronisationDesReceptions(void);
unsigned char serviceProtocole637_gereLeTempsDAttente(void);
unsigned char serviceProtocole637_gereUneReception(void);

//Definitions de variables privees:
unsigned char serviceProtocole637_compteurDeSynchronisationDesTransmissions;
unsigned char serviceProtocole637_compteurDeSynchronisationDesReceptions;
unsigned char serviceProtocole637_compteurDeTransmissions;
unsigned char serviceProtocole637_compteurDeReceptions;
unsigned char serviceProtocole637_compteurDeTempsDAttente;
unsigned char serviceProtocole637_reception;
unsigned char serviceProtocole637_checksum;
unsigned char serviceProtocole637_checksumDeReception;
unsigned char serviceProtocole637_checksumDeTransmission;
size_t i = 0;

//Definitions de fonctions privees:

// machine a etats serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION]

void serviceProtocole637_attendUneRequete(void)
{
    if (serviceProtocole637_gereLaSynchronisationDesTransmissions()
        == SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE)
    {
        return;
    }
    if (serviceProtocole637.requete == REQUETE_TRAITEE)
    {
        return;
    }
    piloteUART0_transmet(SERVICEPROTOCOLE637_DEBUT_DE_TRAME);
    piloteUART2_transmet(SERVICEPROTOCOLE637_DEBUT_DE_TRAME);
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] =
        serviceProtocole637_transmetLaLongueur;
    return;
}

void serviceProtocole637_transmetLaLongueur(void)
{
    if (serviceProtocole637_gereLaSynchronisationDesTransmissions()
        == SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE)
    {
        return;
    }
    serviceProtocole637.nombreATransmettre = INTERFACESTM_NOMBRE_D_OCTETS_A_TRANSMETTRE;
    piloteUART0_transmet('8');
    piloteUART2_transmet(serviceProtocole637.nombreATransmettre);
    serviceProtocole637_compteurDeTransmissions = 0;
    serviceProtocole637_checksumDeTransmission = '%';
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] =
        serviceProtocole637_transmetUneDonnee;
}

void serviceProtocole637_transmetUneDonnee(void)
{
    unsigned char donnee;
    if (serviceProtocole637_gereLaSynchronisationDesTransmissions()
        == SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE)
    {
        return;
    }
    /* insérez votre code ici*/

    if (serviceProtocole637.octetsATransmettre[serviceProtocole637_compteurDeTransmissions] == SERVICEPROTOCOLE637_DEBUT_DE_TRAME)
    {
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] =
            serviceProtocole637_transmetUnZero;
    }
    if (serviceProtocole637_compteurDeTransmissions == serviceProtocole637.nombreATransmettre)
    {
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] =
           serviceProtocole637_transmetUnChecksum;
    }
    serviceProtocole637_compteurDeTransmissions++;
    //donnee = serviceProtocole637.octetsATransmettre[serviceProtocole637_compteurDeTransmissions];
    donnee = 0x05;
    i++;
    if (i < serviceProtocole637.nombreATransmettre)
    {
        piloteUART0_transmet(0x30 + donnee);
        piloteUART2_transmet(donnee);
    }
    if (i > serviceProtocole637.nombreATransmettre)
    {
        i = 0;
        //piloteUART0_transmet(Serial2.read());
        piloteUART2_transmet('%');
        
    }
}

void serviceProtocole637_transmetUnZero(void)
{
    if (serviceProtocole637_gereLaSynchronisationDesTransmissions()
        == SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE)
    {
        return;
    }
    /* insérez votre code ici*/
    if (serviceProtocole637_compteurDeTransmissions < serviceProtocole637.nombreATransmettre)
    {
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] =
            serviceProtocole637_transmetUneDonnee;
    }
    //piloteUART0_transmet('0');
    //piloteUART2_transmet(0x00);
}

void serviceProtocole637_transmetUnChecksum(void)
{
    if (serviceProtocole637_gereLaSynchronisationDesTransmissions()
        == SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE)
    {
        return;
    }
    /* insérez votre code ici */
    piloteUART0_transmet('%');
    piloteUART2_transmet('%');
    serviceProtocole637.requete = REQUETE_TRAITEE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] =
        serviceProtocole637_attendUneRequete;
}

unsigned char serviceProtocole637_gereLaSynchronisationDesTransmissions(void)
{
    serviceProtocole637_compteurDeSynchronisationDesTransmissions++;

    if (serviceProtocole637_compteurDeSynchronisationDesTransmissions <
        SERVICEPROTOCOLE637_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_TRANSMISSION)
    {
        //piloteUART0_transmet(0x31);
        return SERVICEPROTOCOLE637_TRANSMISSION_RETARDEE;
    }
    //digitalWrite(MAIN_DEL, 1);
    serviceProtocole637_compteurDeSynchronisationDesTransmissions = 0;
    return SERVICEPROTOCOLE637_TRANSMISSION_PERMISE;
}

// machine a etats serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION]

void serviceProtocole637_attendUnDebut(void)
{
    if (serviceProtocole637_gereUneReception() == SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE)
    {
        return;
    }
    if (serviceProtocole637_reception == SERVICEPROTOCOLE637_DEBUT_DE_TRAME)
    {
        serviceProtocole637_compteurDeTempsDAttente = 0;
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendLaLongueur;
        return;
    }
    serviceProtocole637.statut = SERVICEPROTOCOLE637_ERREUR_EN_ATTENTE;
    serviceProtocole637.information = INFORMATION_DISPONIBLE;
}

void serviceProtocole637_attendLaLongueur(void)
{
    if (serviceProtocole637_gereLaSynchronisationDesReceptions()
        == SERVICEPROTOCOLE637_RECEPTION_RETARDEE)
    {
        return;
    }
    if (serviceProtocole637_gereLeTempsDAttente() == SERVICEPROTOCOLE637_TEMPS_DEPASSE)
    {
        serviceProtocole637.statut = SERVICEPROTOCOLE637_TEMPS_DEPASSE;
        serviceProtocole637.information = INFORMATION_DISPONIBLE;
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendUnDebut;
    }
    if (serviceProtocole637_gereUneReception() == SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE)
    {
        return;
    }
    serviceProtocole637_compteurDeTempsDAttente = 0;
    if (serviceProtocole637_reception == 0x00)
    {
        serviceProtocole637.statut = SERVICEPROTOCOLE637_ERREUR_LONGUEUR_NULLE;
        serviceProtocole637.information = INFORMATION_DISPONIBLE;
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendUnDebut;
    }
    if (serviceProtocole637_reception > SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM)
    {
        serviceProtocole637.statut = SERVICEPROTOCOLE637_ERREUR_LONGUEUR_TROP_GRANDE;
        serviceProtocole637.information = INFORMATION_DISPONIBLE;
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendUnDebut;
    }
    serviceProtocole637.nombreARecevoir = serviceProtocole637_reception;
    serviceProtocole637_compteurDeReceptions = 0;
    serviceProtocole637_checksum = 0;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendUneDonnee;
}

void serviceProtocole637_attendUneDonnee(void)
{
    if (serviceProtocole637_gereLaSynchronisationDesReceptions()
        == SERVICEPROTOCOLE637_RECEPTION_RETARDEE)
    {
        return;
    }
    if (serviceProtocole637_gereLeTempsDAttente()
        == SERVICEPROTOCOLE637_TEMPS_DEPASSE)
    {
        serviceProtocole637.statut = SERVICEPROTOCOLE637_TEMPS_DEPASSE;
        serviceProtocole637.information = INFORMATION_DISPONIBLE;
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendUnDebut;
        return;
    }
    if (serviceProtocole637_gereUneReception() == SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE)
    {
        return;
    }
    serviceProtocole637_compteurDeTempsDAttente = 0;
    serviceProtocole637.octetsRecus[serviceProtocole637_compteurDeReceptions]
        = serviceProtocole637_reception;
    serviceProtocole637_checksum += serviceProtocole637_reception;
    serviceProtocole637_compteurDeReceptions++;
    if (serviceProtocole637_reception == SERVICEPROTOCOLE637_DEBUT_DE_TRAME)
    {
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendUnZero;
        return;
    }
    if (serviceProtocole637_compteurDeReceptions == serviceProtocole637.nombreARecevoir)
    {
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendUnChecksum;
        return;
    }
}

void serviceProtocole637_attendUnZero(void)
{
    if (serviceProtocole637_gereLaSynchronisationDesReceptions()
        == SERVICEPROTOCOLE637_RECEPTION_RETARDEE)
    {
        return;
    }
    if (serviceProtocole637_gereLeTempsDAttente()
        == SERVICEPROTOCOLE637_TEMPS_DEPASSE)
    {
        serviceProtocole637.statut = SERVICEPROTOCOLE637_TEMPS_DEPASSE;
        serviceProtocole637.information = INFORMATION_DISPONIBLE;
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendUnDebut;
        return;
    }
    if (serviceProtocole637_gereUneReception() == SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE)
    {
        return;
    }
    serviceProtocole637_compteurDeTempsDAttente = 0;
    if (serviceProtocole637_reception > 0x00)
    {
        serviceProtocole637.statut = SERVICEPROTOCOLE637_ERREUR_INSERTION_NON_NULLE;
        serviceProtocole637.information = INFORMATION_DISPONIBLE;
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendUnDebut;
        return;
    }
    if (serviceProtocole637_compteurDeReceptions < serviceProtocole637.nombreARecevoir)
    {
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendUneDonnee;
        return;
    }
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendUnChecksum;
}

void serviceProtocole637_attendUnChecksum(void)
{
    if (serviceProtocole637_gereLaSynchronisationDesReceptions()
        == SERVICEPROTOCOLE637_RECEPTION_RETARDEE)
    {
        return;
    }
    if (serviceProtocole637_gereLeTempsDAttente()
        == SERVICEPROTOCOLE637_TEMPS_DEPASSE)
    {
        serviceProtocole637.statut = SERVICEPROTOCOLE637_TEMPS_DEPASSE;
        serviceProtocole637.information = INFORMATION_DISPONIBLE;
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendUnDebut;
        return;
    }
    if (serviceProtocole637_gereUneReception() == SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE)
    {
        return;
    }
    serviceProtocole637_compteurDeTempsDAttente = 0;
    if (serviceProtocole637_reception == serviceProtocole637_checksum)
    {
        serviceProtocole637.statut = SERVICEPROTOCOLE637_PAS_D_ERREURS;
        serviceProtocole637.information = INFORMATION_DISPONIBLE;
        serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
            serviceProtocole637_attendUnDebut;
        return;
    }
    serviceProtocole637.statut = SERVICEPROTOCOLE637_ERREUR_MAUVAIS_CHECKSUM;
    serviceProtocole637.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendUnDebut;
}

unsigned char serviceProtocole637_gereLaSynchronisationDesReceptions(void)
{
    serviceProtocole637_compteurDeSynchronisationDesReceptions++;
    if (serviceProtocole637_compteurDeSynchronisationDesReceptions <
        SERVICEPROTOCOLE637_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_RECEPTION)
    {
        return SERVICEPROTOCOLE637_RECEPTION_RETARDEE;
    }
    serviceProtocole637_compteurDeSynchronisationDesReceptions = 0;
    return SERVICEPROTOCOLE637_RECEPTION_PERMISE;
}

unsigned char serviceProtocole637_gereLeTempsDAttente(void)
{
    serviceProtocole637_compteurDeTempsDAttente++;
    if (serviceProtocole637_compteurDeTempsDAttente <
        SERVICEPROTOCOLE637_COMPTE_MAXIMAL_ENTRE_LES_RECEPTIONS)
    {
        return SERVICEPROTOCOLE637_TEMPS_PAS_DEPASSE;
    }
    return SERVICEPROTOCOLE637_TEMPS_DEPASSE;
}

unsigned char serviceProtocole637_gereUneReception(void)
{
    if (piloteUART0_octetDisponible() == PILOTEUART0_PAS_DISPONIBLE)
    {
        return SERVICEPROTOCOLE637_LECTURE_PAS_DISPONIBLE;
    }
    serviceProtocole637_reception = piloteUART0_litUnOctetRecu();
    piloteUART0_confirmeLaReception();
    return SERVICEPROTOCOLE637_LECTURE_DISPONIBLE;
}

//Definitions de variables publiques:
SERVICEPROTOCOLE637 serviceProtocole637;

//Definitions de fonctions publiques:
void serviceProtocole637_initialise(void)
{
    serviceProtocole637.etatDuModuleDeReception = MODULE_EN_FONCTION;
    serviceProtocole637.information = INFORMATION_DISPONIBLE;
    serviceProtocole637.requete = REQUETE_TRAITEE;
    serviceProtocole637_compteurDeSynchronisationDesTransmissions = 0;

    serviceProtocole637_compteurDeSynchronisationDesReceptions = 0;
    serviceProtocole637.information = INFORMATION_TRAITEE;
    serviceProtocole637.statut = SERVICEPROTOCOLE637_PAS_D_ERREURS;

    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_TRANSMISSION] =
        serviceProtocole637_attendUneRequete;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLE637_PHASE_RECEPTION] =
        serviceProtocole637_attendUnDebut;

   
}
