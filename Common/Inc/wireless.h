#ifndef WIRELESS_H
#define WIRELESS_H
#include <stdint.h>
void Wireless_Init(void);
uint8_t Wireless_Send(uint8_t *data, uint16_t len);
uint8_t Wireless_Available(void);
uint8_t Wireless_Read(uint8_t *data, uint16_t len);
#endif
