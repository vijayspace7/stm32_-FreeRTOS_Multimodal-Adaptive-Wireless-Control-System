#ifndef APP_TYPES_H
#define APP_TYPES_H
#include <stdint.h>

typedef struct {
    float voice_cmd;
    float semg_level;
    float imu_roll;
    float imu_pitch;
    float imu_yaw;
    float joy_x;
    float joy_y;
    uint32_t timestamp_ms;
} SensorFrame_t;

typedef struct {
    float x;
    float y;
    float z;
    float roll;
    float pitch;
    float yaw;
    uint8_t mode;
    uint8_t confidence;
    uint16_t crc;
} ControlPacket_t;

typedef struct {
    float voice_weight;
    float semg_weight;
    float imu_weight;
    float joystick_weight;
} AdaptiveWeights_t;

#endif
