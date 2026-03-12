#include "control.h"
static float motor1, motor2, motor3, motor4;
void Control_Init(void) { motor1 = motor2 = motor3 = motor4 = 0.0f; }
void Apply_6DOF_Control(const ControlPacket_t *packet)
{
    motor1 = packet->z + packet->pitch + packet->roll - packet->yaw;
    motor2 = packet->z + packet->pitch - packet->roll + packet->yaw;
    motor3 = packet->z - packet->pitch + packet->roll + packet->yaw;
    motor4 = packet->z - packet->pitch - packet->roll - packet->yaw;
    (void)motor1; (void)motor2; (void)motor3; (void)motor4;
}
