// Define this in main.c:
//     struct CANInfo CAN_buffer;

#ifndef SERVICECANH
#define SERVICECANH
 
#define SERVICE_CAN_BUFFER_SIZE 16

struct CANInfo {
    unsigned char byte[SERVICE_CAN_BUFFER_SIZE];
};

extern struct CANInfo CAN_buffer;

#endif