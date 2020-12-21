#include "main.h"
#include "interfaceCAN.h"

extern CAN_HandleTypeDef hcan1; // Défini par le hal dans main.

CAN_RxHeaderTypeDef infoRX;
CAN_TxHeaderTypeDef infoTX;
CAN_FilterTypeDef CANfilter;
unsigned int POBox;

unsigned int CAN_RX(void) {
  return HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_FILTER_FIFO0);
}

unsigned int CAN_TX(void) {
  return HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);
}

unsigned char CAN_Read(unsigned char *Ptrdata, unsigned int *CallerID) {
    if (HAL_CAN_GetRxMessage(&hcan1, CAN_FILTER_FIFO0, &infoRX, Ptrdata) != HAL_OK)
        return 0;
    *CallerID = infoRX.StdId;
    return 1;
}

unsigned int CAN_Send(unsigned int CallerID, unsigned char *Ptrdata, unsigned char len) {
    infoTX.StdId = CallerID;
    infoTX.DLC = len;
    if (HAL_CAN_AddTxMessage(&hcan1, &infoTX, Ptrdata, &POBox) != HAL_OK)
        return 1;
    return 0;
}

unsigned int Init_interfaceCAN(void) {
    infoTX.ExtId = 0;
    infoTX.IDE = CAN_ID_STD;
    infoTX.RTR = CAN_RTR_DATA;
    infoTX.TransmitGlobalTime = DISABLE;
    CANfilter.FilterIdHigh = 0x0;
    CANfilter.FilterIdLow = 0x0;
    CANfilter.FilterMaskIdHigh = 0;
    CANfilter.FilterMaskIdLow = 0;
    CANfilter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    CANfilter.FilterBank = 13;
    CANfilter.FilterMode = CAN_FILTERMODE_IDMASK;
    CANfilter.FilterScale = CAN_FILTERSCALE_32BIT;
    CANfilter.FilterActivation = ENABLE;

    if (HAL_CAN_ConfigFilter(&hcan1, &CANfilter) != HAL_OK)
        return 1;
    if (HAL_CAN_Start(&hcan1) != HAL_OK)
        return 1;
    return 0;
}
