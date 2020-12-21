// serviceProtocoleCom.c

#include "serviceProtocoleCom.h"

#define SERVICEPROTOCOLECOM_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_TRANSMISSION (\
    FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
    / SERVICEPROTOCOLECOM_FREQUENCE_MAXIMALE_DES_TRANSMISSIONS_EN_HZ)
#define SERVICEPROTOCOLECOM_TRANSMISSION_PERMISE 1
#define SERVICEPROTOCOLECOM_TRANSMISSION_RETARDEE 0
#define SERVICEPROTOCOLECOM_RECEPTION_PERMISE 1
#define SERVICEPROTOCOLECOM_RECEPTION_RETARDEE 0
#define SERVICEPROTOCOLECOM_LECTURE_PAS_DISPONIBLE 0
#define SERVICEPROTOCOLECOM_LECTURE_DISPONIBLE 1
#define SERVICEPROTOCOLECOM_COMPTE_MAXIMAL_ENTRE_LES_RECEPTIONS ( \
    SERVICEPROTOCOLECOM_TEMPS_D_ATTENTE_MAXIMAL_EN_MS \
    * SERVICEPROTOCOLECOM_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ / 1000.0)
#define SERVICEPROTOCOLECOM_TEMPS_DEPASSE 1
#define SERVICEPROTOCOLECOM_TEMPS_PAS_DEPASSE 0
#define SERVICEPROTOCOLECOM_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_RECEPTION ( \
    FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
    / SERVICEPROTOCOLECOM_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ)

void serviceProtocoleCom_attendUneRequete(void);
void serviceProtocoleCom_transmetLaLongueur(void);
void serviceProtocoleCom_transmetUneDonnee(void);
void serviceProtocoleCom_transmetUnZero(void);
void serviceProtocoleCom_transmetUnChecksum(void);
unsigned char serviceProtocoleCom_gereLaSynchronisationDesTransmissions(void);
void serviceProtocoleCom_attendUnDebut(void);
void serviceProtocoleCom_attendLaLongueur(void);
void serviceProtocoleCom_attendUneDonnee(void);
void serviceProtocoleCom_attendUnZero(void);
void serviceProtocoleCom_attendUnChecksum(void);
unsigned char serviceProtocoleCom_gereLaSynchronisationDesReceptions(void);
unsigned char serviceProtocoleCom_gereLeTempsDAttente(void);
unsigned char serviceProtocoleCom_gereUneReception(void);

unsigned char serviceProtocoleCom_compteurDeSynchronisationDesTransmissions;
unsigned char serviceProtocoleCom_compteurDeSynchronisationDesReceptions;
unsigned char serviceProtocoleCom_compteurDeTransmissions;
unsigned char serviceProtocoleCom_compteurDeReceptions;
unsigned char serviceProtocoleCom_compteurDeTempsDAttente;
unsigned char serviceProtocoleCom_reception;
unsigned char serviceProtocoleCom_checksum;
unsigned char serviceProtocoleCom_checksumDeReception;
unsigned char serviceProtocoleCom_checksumDeTransmission;

void serviceProtocoleCom_attendUneRequete(void) {
  if (serviceProtocoleCom_gereLaSynchronisationDesTransmissions()
      == SERVICEPROTOCOLECOM_TRANSMISSION_RETARDEE) return;
  if (serviceProtocoleCom.requete == REQUETE_TRAITEE) return;
  piloteUSART2_transmet(SERVICEPROTOCOLECOM_DEBUT_DE_TRAME);
  serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_TRANSMISSION] =
      serviceProtocoleCom_transmetLaLongueur;
  return;
}

void serviceProtocoleCom_transmetLaLongueur(void) {
  if (serviceProtocoleCom_gereLaSynchronisationDesTransmissions()
      == SERVICEPROTOCOLECOM_TRANSMISSION_RETARDEE) return;
  piloteUSART2_transmet(serviceProtocoleCom.nombreATransmettre);
  serviceProtocoleCom_compteurDeTransmissions = 0;
  serviceProtocoleCom_checksumDeTransmission = 0;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_TRANSMISSION] =
      serviceProtocoleCom_transmetUneDonnee;
}

void serviceProtocoleCom_transmetUneDonnee(void) {
  unsigned char donnee;

  if (serviceProtocoleCom_gereLaSynchronisationDesTransmissions()
      == SERVICEPROTOCOLECOM_TRANSMISSION_RETARDEE) return;

  donnee = serviceProtocoleCom.octetsATransmettre[serviceProtocoleCom_compteurDeTransmissions];
  serviceProtocoleCom_checksumDeTransmission += donnee;
  serviceProtocoleCom_compteurDeTransmissions++;
  piloteUSART2_transmet(donnee);

  if (donnee == SERVICEPROTOCOLECOM_DEBUT_DE_TRAME) {
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_TRANSMISSION] =
        serviceProtocoleCom_transmetUnZero;
    return;
  }

  if (serviceProtocoleCom_compteurDeTransmissions == serviceProtocoleCom.nombreATransmettre) {
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_TRANSMISSION] =
        serviceProtocoleCom_transmetUnChecksum;
  }
}

void serviceProtocoleCom_transmetUnZero(void) {
  if (serviceProtocoleCom_gereLaSynchronisationDesTransmissions()
      == SERVICEPROTOCOLECOM_TRANSMISSION_RETARDEE) return;

  piloteUSART2_transmet(SERVICEPROTOCOLECOM_INSERTION);
  if(serviceProtocoleCom_compteurDeTransmissions == serviceProtocoleCom.nombreATransmettre) {
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_TRANSMISSION] =
        serviceProtocoleCom_transmetUnChecksum;
    return;
  }

  serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_TRANSMISSION] =
      serviceProtocoleCom_transmetUneDonnee;
}

void serviceProtocoleCom_transmetUnChecksum(void) {
  if (serviceProtocoleCom_gereLaSynchronisationDesTransmissions() 
      == SERVICEPROTOCOLECOM_TRANSMISSION_RETARDEE) return;

  piloteUSART2_transmet(serviceProtocoleCom_checksumDeTransmission);
  serviceProtocoleCom.requete = REQUETE_TRAITEE;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_TRANSMISSION] =
      serviceProtocoleCom_attendUneRequete;
}

unsigned char serviceProtocoleCom_gereLaSynchronisationDesTransmissions(void) {
  serviceProtocoleCom_compteurDeSynchronisationDesTransmissions++;
  if (serviceProtocoleCom_compteurDeSynchronisationDesTransmissions <
      SERVICEPROTOCOLECOM_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_TRANSMISSION)
    return SERVICEPROTOCOLECOM_TRANSMISSION_RETARDEE;
  serviceProtocoleCom_compteurDeSynchronisationDesTransmissions = 0;
  return SERVICEPROTOCOLECOM_TRANSMISSION_PERMISE;
}

void serviceProtocoleCom_attendUnDebut(void) {
  if (serviceProtocoleCom_gereUneReception() == SERVICEPROTOCOLECOM_LECTURE_PAS_DISPONIBLE)
    return;

  if (serviceProtocoleCom_reception == SERVICEPROTOCOLECOM_DEBUT_DE_TRAME) {
    serviceProtocoleCom_compteurDeTempsDAttente = 0;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendLaLongueur;
    return;
  }

  serviceProtocoleCom.statut = SERVICEPROTOCOLECOM_ERREUR_EN_ATTENTE;
  serviceProtocoleCom.information = INFORMATION_DISPONIBLE;
}

void serviceProtocoleCom_attendLaLongueur(void) {
  if (serviceProtocoleCom_gereLaSynchronisationDesReceptions()
      == SERVICEPROTOCOLECOM_RECEPTION_RETARDEE) return;

  if (serviceProtocoleCom_gereLeTempsDAttente() == SERVICEPROTOCOLECOM_TEMPS_DEPASSE) {
    serviceProtocoleCom.statut = SERVICEPROTOCOLECOM_TEMPS_DEPASSE;
    serviceProtocoleCom.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUnDebut;
  }

  if (serviceProtocoleCom_gereUneReception() == SERVICEPROTOCOLECOM_LECTURE_PAS_DISPONIBLE)
    return;

  serviceProtocoleCom_compteurDeTempsDAttente = 0;

  if (serviceProtocoleCom_reception == 0x00) {
    serviceProtocoleCom.statut = SERVICEPROTOCOLECOM_ERREUR_LONGUEUR_NULLE;
    serviceProtocoleCom.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUnDebut;
  }

  if (serviceProtocoleCom_reception > SERVICEPROTOCOLECOM_NOMBRE_DE_DONNEES_MAXIMUM) {
    serviceProtocoleCom.statut = SERVICEPROTOCOLECOM_ERREUR_LONGUEUR_TROP_GRANDE;
    serviceProtocoleCom.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUnDebut;
  }

  serviceProtocoleCom.nombreARecevoir = serviceProtocoleCom_reception;
  serviceProtocoleCom_compteurDeReceptions = 0;
  serviceProtocoleCom_checksum = 0;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
      serviceProtocoleCom_attendUneDonnee;
}

void serviceProtocoleCom_attendUneDonnee(void) {
  if (serviceProtocoleCom_gereLaSynchronisationDesReceptions()
      == SERVICEPROTOCOLECOM_RECEPTION_RETARDEE) return;

  if (serviceProtocoleCom_gereLeTempsDAttente()
      == SERVICEPROTOCOLECOM_TEMPS_DEPASSE) {
    serviceProtocoleCom.statut = SERVICEPROTOCOLECOM_TEMPS_DEPASSE;
    serviceProtocoleCom.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUnDebut;
    return;
  }

  if (serviceProtocoleCom_gereUneReception() == SERVICEPROTOCOLECOM_LECTURE_PAS_DISPONIBLE)
    return;

  serviceProtocoleCom_compteurDeTempsDAttente = 0;
  serviceProtocoleCom.octetsRecus[serviceProtocoleCom_compteurDeReceptions]
      = serviceProtocoleCom_reception;

  serviceProtocoleCom_checksum += serviceProtocoleCom_reception;
  serviceProtocoleCom_compteurDeReceptions++;

  if (serviceProtocoleCom_reception == SERVICEPROTOCOLECOM_DEBUT_DE_TRAME) {
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUnZero;
    return;
  }

  if (serviceProtocoleCom_compteurDeReceptions == serviceProtocoleCom.nombreARecevoir) {
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUnChecksum;
    return;
  }
}

void serviceProtocoleCom_attendUnZero(void) {
  if (serviceProtocoleCom_gereLaSynchronisationDesReceptions()
      == SERVICEPROTOCOLECOM_RECEPTION_RETARDEE) return;

  if (serviceProtocoleCom_gereLeTempsDAttente()
      == SERVICEPROTOCOLECOM_TEMPS_DEPASSE) {
    serviceProtocoleCom.statut = SERVICEPROTOCOLECOM_TEMPS_DEPASSE;
    serviceProtocoleCom.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUnDebut;
    return;
  }

  if (serviceProtocoleCom_gereUneReception() == SERVICEPROTOCOLECOM_LECTURE_PAS_DISPONIBLE)
    return;

  serviceProtocoleCom_compteurDeTempsDAttente = 0;

  if (serviceProtocoleCom_reception > 0x00) {
    serviceProtocoleCom.statut = SERVICEPROTOCOLECOM_ERREUR_INSERTION_NON_NULLE;
    serviceProtocoleCom.information = INFORMATION_DISPONIBLE; 
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUnDebut;
    return;
  }

  if (serviceProtocoleCom_compteurDeReceptions < serviceProtocoleCom.nombreARecevoir) {
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUneDonnee;
    return;
  }

  serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
      serviceProtocoleCom_attendUnChecksum;
}    

void serviceProtocoleCom_attendUnChecksum(void) {
  if (serviceProtocoleCom_gereLaSynchronisationDesReceptions()
      == SERVICEPROTOCOLECOM_RECEPTION_RETARDEE) return;

  if (serviceProtocoleCom_gereLeTempsDAttente()
      == SERVICEPROTOCOLECOM_TEMPS_DEPASSE) {
    serviceProtocoleCom.statut = SERVICEPROTOCOLECOM_TEMPS_DEPASSE;
    serviceProtocoleCom.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUnDebut;
    return;
  }

  if (serviceProtocoleCom_gereUneReception() == SERVICEPROTOCOLECOM_LECTURE_PAS_DISPONIBLE)
    return;

  serviceProtocoleCom_compteurDeTempsDAttente = 0;

  if (serviceProtocoleCom_reception == serviceProtocoleCom_checksum) {
    serviceProtocoleCom.statut = SERVICEPROTOCOLECOM_PAS_D_ERREURS;
    serviceProtocoleCom.information = INFORMATION_DISPONIBLE;
    serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUnDebut;      
    return;
  }

  serviceProtocoleCom.statut = SERVICEPROTOCOLECOM_ERREUR_MAUVAIS_CHECKSUM;
  serviceProtocoleCom.information = INFORMATION_DISPONIBLE;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
        serviceProtocoleCom_attendUnDebut;      
}

unsigned char serviceProtocoleCom_gereLaSynchronisationDesReceptions(void) {
  serviceProtocoleCom_compteurDeSynchronisationDesReceptions++;
  if (serviceProtocoleCom_compteurDeSynchronisationDesReceptions <
      SERVICEPROTOCOLECOM_COMPTE_MAXIMAL_DE_SYNCHRONISATION_EN_RECEPTION)
    return SERVICEPROTOCOLECOM_RECEPTION_RETARDEE;

  serviceProtocoleCom_compteurDeSynchronisationDesReceptions = 0;
  return SERVICEPROTOCOLECOM_RECEPTION_PERMISE;
}

unsigned char serviceProtocoleCom_gereLeTempsDAttente(void) {
  serviceProtocoleCom_compteurDeTempsDAttente++;
  if (serviceProtocoleCom_compteurDeTempsDAttente <
      SERVICEPROTOCOLECOM_COMPTE_MAXIMAL_ENTRE_LES_RECEPTIONS)
    return SERVICEPROTOCOLECOM_TEMPS_PAS_DEPASSE;
  return SERVICEPROTOCOLECOM_TEMPS_DEPASSE;
}

unsigned char serviceProtocoleCom_gereUneReception(void) {
  if (piloteUSART2_octetDisponible() == PILOTEUSART2_PAS_DISPONIBLE)
    return SERVICEPROTOCOLECOM_LECTURE_PAS_DISPONIBLE;

  serviceProtocoleCom_reception = piloteUSART2_litUnOctetRecu();
  piloteUSART2_confirmeLaReception();
  return SERVICEPROTOCOLECOM_LECTURE_DISPONIBLE;
}

SERVICEPROTOCOLECOM serviceProtocoleCom;

void serviceProtocoleCom_initialise(void) {
  serviceProtocoleCom.etatDuModuleDeReception = MODULE_PAS_EN_FONCTION;
  serviceProtocoleCom.information = INFORMATION_TRAITEE;
  serviceProtocoleCom_compteurDeSynchronisationDesTransmissions = 0;
  serviceProtocoleCom.requete = REQUETE_TRAITEE;
  serviceProtocoleCom_compteurDeSynchronisationDesReceptions = 0;
  serviceProtocoleCom.information = INFORMATION_TRAITEE;
  serviceProtocoleCom.statut = SERVICEPROTOCOLECOM_PAS_D_ERREURS;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_TRANSMISSION] =
      serviceProtocoleCom_attendUneRequete;
  serviceBaseDeTemps_execute[SERVICEPROTOCOLECOM_PHASE_RECEPTION] =
      serviceProtocoleCom_attendUnDebut;
}
