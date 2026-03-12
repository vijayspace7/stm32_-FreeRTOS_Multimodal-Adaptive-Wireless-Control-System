#ifndef CONTROL_H
#define CONTROL_H
#include "app_types.h"
void Control_Init(void);
void Apply_6DOF_Control(const ControlPacket_t *packet);
#endif
