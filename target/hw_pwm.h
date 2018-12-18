#ifndef SERIAL_PWM_H
#define SERIAL_PWM_H

#ifdef __cplusplus
extern "C"
{
#endif

 
#define PWM_DUTY_FRACTION_LOW  (PWM_DUTY_FRACTION_MAX/8)
#define PWM_DUTY_FRACTION_MID  (PWM_DUTY_FRACTION_MAX/3)

typedef enum CC2640_PWM_RGB {
    PWM_1R = 0,
    PWM_1G = 1,
    PWM_1B = 2,
    PWM_2R = 3,
    PWM_2G = 4,
    PWM_2B = 5,
    PWM_COUNT
} CC2640_PWM_RGBHandle;

extern uint32_t PWM_Max_Duty_Fraction;
extern uint8_t color_index;

void HwPWMInit(void);


void HwPWMStart(uint8_t RGBHandle);

void HwPWMStartAll(void);

void HwPWMStop(uint8_t RGBHandle);

void HwPWMStopAll(void);

void HwPWMClose(uint8_t RGBHandle);

void HwPWMCloseAll(void);

void HwRGBSwitch(uint8_t colour);

void HwRGBControl(uint8_t colour,uint32_t Duty_Fraction_value);

uint8_t Color_Switch_Index(void);

void PWM_Set_Duty(uint8_t RGBHandle,uint32_t value);

uint32_t PWM_DutyValue(uint8_t hz,uint32_t interval);

#ifdef __cplusplus
{
#endif // extern "C"

#endif // SERIAL_PWM_H