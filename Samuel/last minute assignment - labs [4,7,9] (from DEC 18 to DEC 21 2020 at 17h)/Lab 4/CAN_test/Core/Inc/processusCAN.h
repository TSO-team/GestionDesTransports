#ifndef PROCESSUSCAN_H
#define PROCESSUSCAN_H

//#define ADDRESS_1    (1<<5)
//#define ADDRESS_2    (2<<5)
//#define ADDRESS_3    (3<<5)
//#define ADDRESS_4    (4<<5)
//#define DELAI_CAN_RX 75     // Nombre d'interruptions.
//#define DELAI_CAN_TX 400    // Nombre d'interruptions.
//#define PHASE_RX_CAN 0
//#define PHASE_TX_CAN 1

void Init_processusCAN(void);

struct SPCAN {
    unsigned char dataOUT[8];
    unsigned int CallerIDOut;
    unsigned int CallerIDIn;
    unsigned char requete;
    unsigned char information;
};

extern struct SPCAN processusCAN;
#endif
