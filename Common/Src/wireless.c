#include "wireless.h"
void Wireless_Init(void) {}
uint8_t Wireless_Send(uint8_t *data, uint16_t len) { (void)data; (void)len; return 1; }
uint8_t Wireless_Available(void) { return 0; }
uint8_t Wireless_Read(uint8_t *data, uint16_t len) { (void)data; (void)len; return 0; }
