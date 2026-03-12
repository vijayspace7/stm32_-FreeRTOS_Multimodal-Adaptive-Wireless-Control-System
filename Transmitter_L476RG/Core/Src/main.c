#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "string.h"
#include "sensors.h"
#include "fusion.h"
#include "wireless.h"
#include "crc16.h"

static SensorFrame_t g_frame;
static AdaptiveWeights_t g_weights;
static ControlPacket_t g_packet;

void VoiceTask(void *argument);
void EMGTask(void *argument);
void IMUTask(void *argument);
void JoystickTask(void *argument);
void FusionTask(void *argument);
void WirelessTask(void *argument);
void SafetyTask(void *argument);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    Sensors_Init();
    Fusion_Init();
    Wireless_Init();

    xTaskCreate(VoiceTask, "VoiceTask", 256, NULL, 2, NULL);
    xTaskCreate(EMGTask, "EMGTask", 256, NULL, 2, NULL);
    xTaskCreate(IMUTask, "IMUTask", 256, NULL, 2, NULL);
    xTaskCreate(JoystickTask, "JoystickTask", 256, NULL, 2, NULL);
    xTaskCreate(FusionTask, "FusionTask", 384, NULL, 3, NULL);
    xTaskCreate(WirelessTask, "WirelessTask", 384, NULL, 3, NULL);
    xTaskCreate(SafetyTask, "SafetyTask", 256, NULL, 4, NULL);

    vTaskStartScheduler();
    while (1) {}
}

void VoiceTask(void *argument) { (void)argument; for (;;) { Voice_Read(&g_frame); vTaskDelay(pdMS_TO_TICKS(20)); } }
void EMGTask(void *argument) { (void)argument; for (;;) { EMG_Read(&g_frame); vTaskDelay(pdMS_TO_TICKS(10)); } }
void IMUTask(void *argument) { (void)argument; for (;;) { IMU_Read(&g_frame); vTaskDelay(pdMS_TO_TICKS(10)); } }
void JoystickTask(void *argument) { (void)argument; for (;;) { Joystick_Read(&g_frame); vTaskDelay(pdMS_TO_TICKS(10)); } }

void FusionTask(void *argument)
{
    (void)argument;
    for (;;) {
        Fusion_UpdateWeights(&g_frame, &g_weights);
        Fusion_BuildControl(&g_frame, &g_weights, &g_packet);
        g_packet.crc = CRC16_CCITT((const uint8_t *)&g_packet, sizeof(ControlPacket_t) - sizeof(uint16_t));
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void WirelessTask(void *argument)
{
    (void)argument;
    for (;;) {
        Wireless_Send((uint8_t *)&g_packet, sizeof(g_packet));
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void SafetyTask(void *argument)
{
    (void)argument;
    for (;;) {
        if (g_frame.semg_level > 0.95f) {
            memset(&g_packet, 0, sizeof(g_packet));
        }
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
