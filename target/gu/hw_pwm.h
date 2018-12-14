#ifndef SERIAL_PWM_H
#define SERIAL_PWM_H

#ifdef __cplusplus
extern "C"
{
#endif

  
typedef enum CC2650_PWM_RGB {
    PWM_R = 0,
    PWM_G = 1,
    PWM_B = 2,
    PWM_Buzzer = 3,
    PWM_COUNT
} CC2650_PWM_RGBHandle;

/*****************************************************
 * PWM훨蛟놓迦뺏
*/  
void HwPWMInit(void);

/*****************************************************
 * 역폘뎠품PWM多신
*/ 
void HwPWMStart(uint8_t RGBHandle);

/*****************************************************
 * 董界뎠품PWM多신
*/ 
void HwPWMStop(uint8_t RGBHandle);

/*****************************************************
 * 밑균뎠품PWM多신
*/ 
void HwPWMClose(uint8_t RGBHandle);

void HwPWMCloseAll(void);

void HwRGBControl(uint8_t colour);

#ifdef __cplusplus
{
#endif // extern "C"

#endif // SERIAL_PWM_H