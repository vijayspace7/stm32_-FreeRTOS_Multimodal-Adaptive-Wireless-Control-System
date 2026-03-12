#include "fusion.h"

static float clampf(float v, float minv, float maxv)
{
    if (v < minv) return minv;
    if (v > maxv) return maxv;
    return v;
}

void Fusion_Init(void) {}

void Fusion_UpdateWeights(const SensorFrame_t *in, AdaptiveWeights_t *w)
{
    w->voice_weight = (in->voice_cmd > 0.1f) ? 0.35f : 0.10f;
    w->semg_weight = clampf(in->semg_level, 0.10f, 0.50f);
    w->imu_weight = 0.25f;
    w->joystick_weight = 0.30f;
}

void Fusion_BuildControl(const SensorFrame_t *in, const AdaptiveWeights_t *w, ControlPacket_t *out)
{
    out->x = (w->joystick_weight * in->joy_x);
    out->y = (w->joystick_weight * in->joy_y);
    out->z = (w->semg_weight * in->semg_level);
    out->roll = w->imu_weight * in->imu_roll;
    out->pitch = w->imu_weight * in->imu_pitch;
    out->yaw = w->imu_weight * in->imu_yaw;

    if (in->voice_cmd == 1.0f) {
        out->z = 1.0f;
        out->mode = 1;
    } else if (in->voice_cmd == 2.0f) {
        out->z = 0.0f;
        out->mode = 2;
    } else {
        out->mode = 0;
    }

    out->confidence = 90;
    out->crc = 0;
}
