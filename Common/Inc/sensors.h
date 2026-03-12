#ifndef SENSORS_H
#define SENSORS_H
#include "app_types.h"
void Sensors_Init(void);
void Voice_Read(SensorFrame_t *frame);
void EMG_Read(SensorFrame_t *frame);
void IMU_Read(SensorFrame_t *frame);
void Joystick_Read(SensorFrame_t *frame);
#endif
