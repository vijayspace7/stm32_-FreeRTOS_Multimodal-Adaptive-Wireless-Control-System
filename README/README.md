# STM32 Multimodal Adaptive Wireless Control System

This is a full source scaffold for a multimodal adaptive wireless control system.

## Boards
- Transmitter: STM32L476RG
- Receiver: STM32F446RE

## Inputs
1. Voice recognition module (UART)
2. sEMG sensor (ADC)
3. IMU (I2C)
4. Joystick (ADC)

## Wireless
- nRF24L01 over SPI

## Output
- 6-DOF control vector: X, Y, Z, Roll, Pitch, Yaw

## Tasks
### Transmitter
- VoiceTask
- EMGTask
- IMUTask
- JoystickTask
- FusionTask
- WirelessTask
- SafetyTask

### Receiver
- WirelessRxTask
- ControlTask
- SafetyTask
