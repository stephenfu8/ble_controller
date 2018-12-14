#ifndef SERIAL_PWM_H
#define SERIAL_PWM_H

#ifdef __cplusplus
extern "C"
{
#endif

  
typedef enum CC2640_PWM_RGB {
    PWM_1R = 0,
    PWM_1G = 1,
    PWM_1B = 2,
    PWM_2R = 3,
    PWM_2G = 4,
    PWM_2B = 5,
    PWM_Buzzer = 6,
    PWM_COUNT
} CC2640_PWM_RGBHandle;


void HwPWMInit(void);


void HwPWMStart(uint8_t RGBHandle);


void HwPWMStop(uint8_t RGBHandle);

void HwPWMStopAll(void);

void HwPWMClose(uint8_t RGBHandle);

void HwPWMCloseAll(void);

void HwRGBControl(uint8_t colour);

void PWM_Set_Duty(uint8_t RGBHandle,uint32_t value);

uint32_t PWM_DutyValue(uint8_t hz,uint32_t interval);
#ifdef __cplusplus
{
#endif // extern "C"

#endif // SERIAL_PWM_H