#include "sensors.h"
void Sensors_Init(void) {}
void Voice_Read(SensorFrame_t *frame) { frame->voice_cmd = 0.0f; }
void EMG_Read(SensorFrame_t *frame) { frame->semg_level = 0.4f; }
void IMU_Read(SensorFrame_t *frame) { frame->imu_roll = 0.05f; frame->imu_pitch = -0.02f; frame->imu_yaw = 0.01f; }
void Joystick_Read(SensorFrame_t *frame) { frame->joy_x = 0.2f; frame->joy_y = -0.1f; }
