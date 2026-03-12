#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#include "wireless.h"
#include "control.h"
#include "crc16.h"

static ControlPacket_t g_rxPacket;
static ControlPacket_t g_safePacket;

void WirelessRxTask(void *argument);
void ControlTask(void *argument);
void SafetyTask(void *argument);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    Wireless_Init();
    Control_Init();
    memset(&g_safePacket, 0, sizeof(g_safePacket));

    xTaskCreate(WirelessRxTask, "WirelessRxTask", 384, NULL, 3, NULL);
    xTaskCreate(ControlTask, "ControlTask", 384, NULL, 3, NULL);
    xTaskCreate(SafetyTask, "SafetyTask", 256, NULL, 4, NULL);

    vTaskStartScheduler();
    while (1) {}
}

void WirelessRxTask(void *argument)
{
    (void)argument;
    for (;;) {
        if (Wireless_Available()) {
            Wireless_Read((uint8_t *)&g_rxPacket, sizeof(g_rxPacket));
        }
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void ControlTask(void *argument)
{
    uint16_t expected_crc;
    (void)argument;
    for (;;) {
        expected_crc = CRC16_CCITT((const uint8_t *)&g_rxPacket, sizeof(ControlPacket_t) - sizeof(uint16_t));
        if (expected_crc == g_rxPacket.crc) Apply_6DOF_Control(&g_rxPacket);
        else Apply_6DOF_Control(&g_safePacket);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void SafetyTask(void *argument)
{
    (void)argument;
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
