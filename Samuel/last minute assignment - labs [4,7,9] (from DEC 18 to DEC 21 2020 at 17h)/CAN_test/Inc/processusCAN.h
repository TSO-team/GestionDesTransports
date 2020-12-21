#ifndef PROCESSUSCAN_H
#define PROCESSUSCAN_H

//#define ADRS_COM        (1<<5)
//#define ADRS_TRI        (2<<5)
//#define ADRS_TRUCK      (3<<5)
//#define ADRS_PESE       (4<<5)
//#define DELAI_CAN_RX    75                               // nombre d'interrupt
//#define DELAI_CAN_TX    400                              // nombre d'interrupt
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


