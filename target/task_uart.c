#include <stdio.h>
#include <string.h>

#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Event.h>

#include "board.h"
#include <ti/drivers/uart/UARTCC26XX.h>
#include "task_uart.h"
#include "hw_adc.h"
#include "hw_pwm.h"
/*********************************************************************
 * LOCAL PARAMETER
 */
// Task configuration
#define UART_TASK_PRIORITY                     2
#define UART_TASK_STACK_SIZE                   644
Task_Struct uartTask;
Char uartTaskStack[UART_TASK_STACK_SIZE];

// Uart configuration
#define UART_BUF_LEN  200


/*********************************************************************
 * LOCAL FUNCTIONS
 */
void TaskUART_taskInit(void);   
void TaskUART_taskFxn(UArg a0, UArg a1);


/*********************************************************************
 * @fn      TaskUART_createTask
 *
 * @brief   Task creation function for the uart.
 *
 * @param   None.
 *
 * @return  None.
 */
void TaskUART_createTask(void)
{
  Task_Params taskParams;

  // Configure task
  Task_Params_init(&taskParams);
  taskParams.stack = uartTaskStack;
  taskParams.stackSize = UART_TASK_STACK_SIZE;
  taskParams.priority = UART_TASK_PRIORITY;

  Task_construct(&uartTask, TaskUART_taskFxn, &taskParams, NULL);
}


/*********************************************************************
 * @fn      TaskUART_taskFxn
 *
 * @brief   串口任务处理
 *
 * @param   None
 *
 * @return  None.
 */
void TaskUART_taskFxn(UArg a0, UArg a1)
{ 
  Event_Params evParams;
  Event_Params_init(&evParams);

  
      HwADCInit();
  while(1)
  {
     uint32_t value = HwADCRead();
      value = 0xFFFFF*value;
      HwRGBControl(0, value);       //set now color pwm duty fraction

      uint8_t ii= Color_Switch_Index();  
      HwRGBSwitch(ii);               // start new color output
  }
}


