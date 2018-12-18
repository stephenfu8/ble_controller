#include "board.h"
#include "ti/drivers/PWM.h"

#include "hw_pwm.h"
/*********************************************************************
 * LOCAL PARAMETER
 */
PWM_Handle PWMHandle1R;
PWM_Handle PWMHandle1G;
PWM_Handle PWMHandle1B;

PWM_Handle PWMHandle2R;
PWM_Handle PWMHandle2G;
PWM_Handle PWMHandle2B;

//PWM_Handle PWMHandleBuzzer;

PWM_Params PWMparams;


uint32_t PWM_Max_Duty_Fraction = PWM_DUTY_FRACTION_MID;
uint8_t color_index=0;
/*******************PWM_DUTY_FRACTION_MAX**************************************************
 * LOCAL FUNCTIONS
 */

/*********************************************************************
 * @fn      GY_PwmTask_Init
 *
 * @brief   PWM任务初始化及启动
 *
 * @param   pin -> Board_PWM0 - Board_PWM7
 *
 * @return  None.
 */
void HwPWMInit(void)
{
  PWM_init();
  PWM_Params_init(&PWMparams);
  //LED1 RED
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 600;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_Max_Duty_Fraction/2;
  PWMHandle1R = PWM_open(Board_PWM1R, &PWMparams);
  //LED1 GREEN
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 600;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_Max_Duty_Fraction/2;
  PWMHandle1G = PWM_open(Board_PWM1G, &PWMparams);
  //LED1 BLUE
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 600;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_Max_Duty_Fraction/2;
  PWMHandle1B = PWM_open(Board_PWM1B, &PWMparams);

  //LED2 RED
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 600;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_Max_Duty_Fraction/2;
  PWMHandle2R = PWM_open(Board_PWM2R, &PWMparams);
  //LED2 GREEN
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 600;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_Max_Duty_Fraction/2;
  PWMHandle2G = PWM_open(Board_PWM2G, &PWMparams);
  //LED2 BLUE
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 600;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_Max_Duty_Fraction/2;
  PWMHandle2B = PWM_open(Board_PWM2B, &PWMparams);
}

/*********************************************************************
 * @fn      GY_PWM_Start
 *
 * @brief   开启当前PWM引脚
 *
 * @param   None
 *
 * @return  None.
 */
void HwPWMStart(uint8_t RGBHandle)
{
  switch(RGBHandle)
  {
    case 0:
      PWM_start(PWMHandle1R);
      break;
    case 1:
      PWM_start(PWMHandle1G);
      break;
    case 2:
      PWM_start(PWMHandle1B);
      break;    
    case 3:
      PWM_start(PWMHandle2R);
      break;
    case 4:
      PWM_start(PWMHandle2G);
      break;
    case 5:
      PWM_start(PWMHandle2B);
      break; 
    default:
      break;
  }
}

/*********************************************************************
 * @fn      GY_PWM_Stop
 *
 * @brief   暂停当前PWM引脚
 *
 * @param   None
 *
 * @return  None.
 */
void HwPWMStop(uint8_t RGBHandle)
{
  switch(RGBHandle)
  {
    case 0:
      PWM_stop(PWMHandle1R);
      break;
    case 1:
      PWM_stop(PWMHandle1G);
      break;
    case 2:
      PWM_stop(PWMHandle1B);
      break;    
    case 3:
      PWM_stop(PWMHandle2R);
      break;
    case 4:
      PWM_stop(PWMHandle2G);
      break;
    case 5:
      PWM_stop(PWMHandle2B);
      break;  
    default:
      break;
  }
}
/*********************************************************************
 * @fn      PWM_StopAll
 *
 * @brief   停止所有PWM引脚输出
 *
 * @param   None
 *
 * @return  None.
 */
void HwPWMStopAll(void)
{
  HwPWMStop(PWM_1R);
  HwPWMStop(PWM_1G);
  HwPWMStop(PWM_1B);

  HwPWMStop(PWM_2R);
  HwPWMStop(PWM_2G);
  HwPWMStop(PWM_2B);

}
void HwPWMStartAll(void)
{
  PWM_start(PWMHandle1R);
  PWM_start(PWMHandle1G);
  PWM_start(PWMHandle1B);

  PWM_start(PWMHandle2R);
  PWM_start(PWMHandle2G);
  PWM_start(PWMHandle2B);

}
/*********************************************************************
 * @fn     PWM_Close
 *
 * @brief   关闭当前PWM引脚
 *
 * @param   None
 *
 * @return  None.
 */
void HwPWMClose(uint8_t RGBHandle)
{
  switch(RGBHandle)
  {
    case 0:
      PWM_stop(PWMHandle1R);
      PWM_close(PWMHandle1R);
      break;
    case 1:
      PWM_stop(PWMHandle1G);
      PWM_close(PWMHandle1G);
      break;
    case 2:
      PWM_stop(PWMHandle1B);
      PWM_close(PWMHandle1B);
      break;
    
    case 3:
      PWM_stop(PWMHandle2R);
      PWM_close(PWMHandle2R);
      break;
    case 4:
      PWM_stop(PWMHandle2G);
      PWM_close(PWMHandle2G);
      break;
    case 5:
      PWM_stop(PWMHandle2B);
      PWM_close(PWMHandle2B);
      break;
    default:
      break;
  }
}
void HwPWMCloseAll(void)
{
  HwPWMStop(PWM_1R);
  HwPWMStop(PWM_1G);
  HwPWMStop(PWM_1B);
  PWM_close(PWMHandle1R);
  PWM_close(PWMHandle1G);
  PWM_close(PWMHandle1B);
  
  HwPWMStop(PWM_2R);
  HwPWMStop(PWM_2G);
  HwPWMStop(PWM_2B);
  PWM_close(PWMHandle2R);
  PWM_close(PWMHandle2G);
  PWM_close(PWMHandle2B);

}
void HwRGBSwitch(uint8_t colour)
{
  HwPWMStopAll();
  switch(colour)
  {
    case 1: //红
      PWM_start(PWMHandle1R);
      break;
    case 2: //橙
      PWM_start(PWMHandle1R);
      PWM_start(PWMHandle1G);
      break;   
    case 3: //黄
      PWM_start(PWMHandle1R);
      PWM_start(PWMHandle1G);
      break;
    case 4: //绿
      PWM_start(PWMHandle1G);
      break;
    case 5: //青
      PWM_start(PWMHandle1G);
      PWM_start(PWMHandle1B);
      break;    
    case 6: //蓝
      PWM_start(PWMHandle1B);
      break;
    case 7: //紫
      PWM_start(PWMHandle1R);
      PWM_start(PWMHandle1B);
      break;
    default:
      break;
  }
}
void HwRGBControl(uint8_t colour,uint32_t Duty_Fraction_value)
{
  switch(colour)
  {
    case 1: //红
      PWM_Set_Duty(PWM_1R,Duty_Fraction_value);
      break;
    case 2: //橙
      PWM_Set_Duty(PWM_1R,Duty_Fraction_value);
      PWM_Set_Duty(PWM_1G,Duty_Fraction_value/2);
      break;   
    case 3: //黄
      PWM_Set_Duty(PWM_1R,Duty_Fraction_value);
      PWM_Set_Duty(PWM_1G,Duty_Fraction_value);
      break;
    case 4: //绿
      PWM_Set_Duty(PWM_1G,Duty_Fraction_value);
      break;
    case 5: //青
      PWM_Set_Duty(PWM_1G,Duty_Fraction_value);
      PWM_Set_Duty(PWM_1B,Duty_Fraction_value);
      break;    
    case 6: //蓝
      PWM_Set_Duty(PWM_1B,Duty_Fraction_value);
      break;
    case 7: //紫
      PWM_Set_Duty(PWM_1R,Duty_Fraction_value);
      PWM_Set_Duty(PWM_1B,Duty_Fraction_value);
      break;
    default:
      break;
  }
}
uint8_t Color_Switch_Index(void)
{
  color_index = color_index == 7 ? 0 : color_index;
  color_index++;
  return color_index;
}
/*
* calculate value of the duty fraction base on the PWM_Max_Duty_Fraction
* hz： The times to change
* interval： change interval time
*/
uint32_t PWM_DutyValue(uint8_t hz,uint32_t interval)
{
  static uint8_t count =0;
  static uint32_t value =0;
  uint8_t buff;
  count ++;
  if (count >(hz+hz))
    count = 0;
  if (count <= hz)
    buff = count;
  else if (count > hz)
    buff = hz +hz -count;
  value = buff *interval;
  return value;
}
void PWM_Set_Duty(uint8_t RGBHandle,uint32_t value)
{
  switch (RGBHandle)
  {
  case 0:
      PWMHandle1R->fxnTablePtr->setDutyFxn(PWMHandle1R,value);
    break;
  case 1:
      PWMHandle1G->fxnTablePtr->setDutyFxn(PWMHandle1G,value);
    break;
  case 2:
      PWMHandle1B->fxnTablePtr->setDutyFxn(PWMHandle1B,value);
    break;
  case 3:
      PWMHandle1R->fxnTablePtr->setDutyFxn(PWMHandle2R,value);
    break;
  case 4:
      PWMHandle1G->fxnTablePtr->setDutyFxn(PWMHandle2G,value);
    break;
  case 5:
      PWMHandle1B->fxnTablePtr->setDutyFxn(PWMHandle2B,value);  
  default:
    break;
  }
}