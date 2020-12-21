#ifndef INTERFACECAN_H
#define INTERFACECAN_H

unsigned int Init_interfaceCAN(void);
unsigned int CAN_RX(void);
unsigned int CAN_TX(void);
unsigned char CAN_Read(unsigned char *Ptrdata,unsigned int *CallerID);
unsigned int CAN_Send(unsigned int CallerID, unsigned char *Ptrdata, unsigned char len);

#endif
