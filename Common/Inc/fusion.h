#ifndef FUSION_H
#define FUSION_H
#include "app_types.h"
void Fusion_Init(void);
void Fusion_UpdateWeights(const SensorFrame_t *in, AdaptiveWeights_t *w);
void Fusion_BuildControl(const SensorFrame_t *in, const AdaptiveWeights_t *w, ControlPacket_t *out);
#endif
