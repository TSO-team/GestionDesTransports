// Define this in main.c:
//     struct service_CAN_buffer CAN_buffer;

#ifndef SERVICECANH
#define SERVICECANH
 
#define SERVICE_CAN_BUFFER_SIZE 16

struct service_CAN_buffer {
    unsigned char byte[SERVICE_CAN_BUFFER_SIZE];
};

extern struct service_CAN_buffer CAN_buffer;

#endif
