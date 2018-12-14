#include "board.h"
#include "ti/drivers/PWM.h"

#include "hw_pwm.h"
/*********************************************************************
 * LOCAL PARAMETER
 */
PWM_Handle PWMHandle1R;
PWM_Handle PWMHandle1G;
PWM_Handle PWMHandle1B;
/* //LED2 for GPIO application test
PWM_Handle PWMHandle2R;
PWM_Handle PWMHandle2G;
PWM_Handle PWMHandle2B;
*/
//PWM_Handle PWMHandleBuzzer;

PWM_Params PWMparams;
/*********************************************************************
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
  PWMparams.dutyValue = PWM_DUTY_FRACTION_MAX/2;
  PWMHandle1R = PWM_open(Board_PWM1R, &PWMparams);
  //LED1 GREEN
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 600;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_DUTY_FRACTION_MAX/2;
  PWMHandle1G = PWM_open(Board_PWM1G, &PWMparams);
  //LED1 BLUE
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 600;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_DUTY_FRACTION_MAX/2;
  PWMHandle1B = PWM_open(Board_PWM1B, &PWMparams);
/* //LED2 for GPIO application test  
  //LED2 RED
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 100;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_DUTY_FRACTION_MAX/2;
//  PWMHandle2R = PWM_open(Board_PWM2R, &PWMparams);
  //LED2 GREEN
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 100;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_DUTY_FRACTION_MAX/2;
//  PWMHandle2G = PWM_open(Board_PWM2G, &PWMparams);
  //LED2 BLUE
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 100;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_DUTY_FRACTION_MAX/2;
//  PWMHandle2B = PWM_open(Board_PWM2B, &PWMparams);
*/
  //Buzzer
  PWMparams.idleLevel = PWM_IDLE_LOW;
  PWMparams.periodUnits = PWM_PERIOD_HZ;
  PWMparams.periodValue = 2700;
  PWMparams.dutyUnits = PWM_DUTY_FRACTION;
  PWMparams.dutyValue = PWM_DUTY_FRACTION_MAX/100;
 // PWMHandleBuzzer = PWM_open(Board_PWMBUZZER, &PWMparams);
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
/* //LED2 for GPIO application test      
    case 3:
      PWM_start(PWMHandle2R);
      break;
    case 4:
      PWM_start(PWMHandle2G);
      break;
    case 5:
      PWM_start(PWMHandle2B);
      break; 
*/      
    case 3:
//      PWM_start(PWMHandleBuzzer);
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
//      PWM_stop(PWMHandleBuzzer);
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
  /* //LED2 for GPIO application test
  HwPWMStop(PWM_2R);
  HwPWMStop(PWM_2G);
  HwPWMStop(PWM_2B);
  */
}
void HwPWMStartAll(void)
{
  PWM_start(PWMHandle1R);
  PWM_start(PWMHandle1G);
  PWM_start(PWMHandle1B);
/* //LED2 for GPIO application test  
  PWM_start(PWMHandle2R);
  PWM_start(PWMHandle2G);
  PWM_start(PWMHandle2B);
  */
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
/* //LED2 for GPIO application test      
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
*/      
    case 3:
//      PWM_stop(PWMHandleBuzzer);
//      PWM_close(PWMHandleBuzzer);
      break;
    default:
      break;
  }
}
void HwRGBControl(uint8_t colour)
{
  HwPWMStopAll();
  switch(colour)
  {
    case 0: //红
      PWM_start(PWMHandle1R);
      break;
    case 1: //绿
      PWM_start(PWMHandle1G);
      break;
    case 2: //蓝
      PWM_start(PWMHandle1B);
      break;
    case 3: //黄
      PWM_start(PWMHandle1R);
      PWM_start(PWMHandle1G);
      break;
    case 4: //紫
      PWM_start(PWMHandle1R);
      PWM_start(PWMHandle1B);
      break;
    case 5: //青
      PWM_start(PWMHandle1G);
      PWM_start(PWMHandle1B);
      break;
    case 6: //白
      PWM_start(PWMHandle1R);
      PWM_start(PWMHandle1G);
      PWM_start(PWMHandle1B);
      break;

    default:
      break;
  }
}
uint32_t PWM_DutyValue(uint8_t hz,uint32_t interval)
{
  static uint8_t count =0;
  static uint32_t value =0;
  if ( count <= hz )
  {
    value += interval;
    count ++;
  }
  else if ( count == hz )
    count ++;
  else
  {
    value -= interval;

    if(value < interval)
      count=0;
  }
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
    break;
  default:
    break;
  }
}