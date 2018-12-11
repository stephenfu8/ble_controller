/******************************************************************************

 @file  board_key.c

 @brief This file contains the interface to the SRF06EB Key Service.

 Group: WCS, BTS
 Target Device: CC2650, CC2640, CC1350

 ******************************************************************************
 
 Copyright (c) 2014-2016, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 Release Name: ble_sdk_2_02_01_18
 Release Date: 2016-10-26 15:20:04
 *****************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include <ti/drivers/pin/PINCC26XX.h>
#include "util.h"
#include "cc2640_telectrl.h"
#include "hw_key.h"

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void Board_keyChangeHandler(UArg a0);
static void Board_keyCallback(PIN_Handle hPin, PIN_Id pinId);

/*******************************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * LOCAL VARIABLES
 */

// Value of keys Pressed
static uint8_t keysPressed;

// Key debounce clock
static Clock_Struct keyChangeClock;

// Pointer to application callback
keysPressedCB_t appKeyChangeHandler = NULL;

// Memory for the GPIO module to construct a Hwi
Hwi_Struct callbackHwiKeys;

// PIN configuration structure to set all KEY pins as inputs with pullups enabled
PIN_Config keyPinsCfg[] =
{
#ifdef TELE_LOCAL
    Board_KEY          | PIN_GPIO_OUTPUT_DIS  | PIN_INPUT_EN  |  PIN_PULLUP,
#endif
      
#ifdef TELE_REMOTE      
    Board_KEY1          | PIN_GPIO_OUTPUT_DIS  | PIN_INPUT_EN  |  PIN_PULLUP,
    Board_KEY2          | PIN_GPIO_OUTPUT_DIS  | PIN_INPUT_EN  |  PIN_PULLUP,
    Board_KEY3          | PIN_GPIO_OUTPUT_DIS  | PIN_INPUT_EN  |  PIN_PULLUP,
    Board_KEY4          | PIN_GPIO_OUTPUT_DIS  | PIN_INPUT_EN  |  PIN_PULLUP,
#endif
    PIN_TERMINATE
};

PIN_State  keyPins;
PIN_Handle hKeyPins;

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
/*********************************************************************
 * @fn      Board_initKeys
 *
 * @brief   Enable interrupts for keys on GPIOs.
 *
 * @param   appKeyCB - application key pressed callback
 *
 * @return  none
 */
void Board_initKeys(keysPressedCB_t appKeyCB)
{  
  // Initialize KEY pins. Enable int after callback registered
  hKeyPins = PIN_open(&keyPins, keyPinsCfg);
  PIN_registerIntCb(hKeyPins, Board_keyCallback);
  
#ifdef TELE_LOCAL
  PIN_setConfig(hKeyPins, PIN_BM_IRQ, Board_KEY        | PIN_IRQ_NEGEDGE);
#ifdef POWER_SAVING
  //Enable wakeup
  PIN_setConfig(hKeyPins, PINCC26XX_BM_WAKEUP, Board_KEY | PINCC26XX_WAKEUP_NEGEDGE);
#endif //POWER_SAVING
#endif
  
#ifdef TELE_REMOTE
  PIN_setConfig(hKeyPins, PIN_BM_IRQ, Board_KEY1        | PIN_IRQ_NEGEDGE);
  PIN_setConfig(hKeyPins, PIN_BM_IRQ, Board_KEY2        | PIN_IRQ_NEGEDGE);
  PIN_setConfig(hKeyPins, PIN_BM_IRQ, Board_KEY3        | PIN_IRQ_NEGEDGE);
  PIN_setConfig(hKeyPins, PIN_BM_IRQ, Board_KEY4        | PIN_IRQ_NEGEDGE);


#ifdef POWER_SAVING
  //Enable wakeup
  PIN_setConfig(hKeyPins, PINCC26XX_BM_WAKEUP, Board_KEY1 | PINCC26XX_WAKEUP_NEGEDGE);
  PIN_setConfig(hKeyPins, PINCC26XX_BM_WAKEUP, Board_KEY2 | PINCC26XX_WAKEUP_NEGEDGE);
#endif //POWER_SAVING
#endif  
  // Setup keycallback for keys
  Util_constructClock(&keyChangeClock, Board_keyChangeHandler,
                      KEY_DEBOUNCE_TIMEOUT, 0, false, 0);

  // Set the application callback
  appKeyChangeHandler = appKeyCB;
}

/*********************************************************************
 * @fn      Board_keyCallback
 *
 * @brief   Interrupt handler for Keys
 *
 * @param   none
 *
 * @return  none
 */
static void Board_keyCallback(PIN_Handle hPin, PIN_Id pinId)
{
  Util_startClock(&keyChangeClock);
}

/*********************************************************************
 * @fn      Board_keyChangeHandler
 *
 * @brief   Handler for key change
 *
 * @param   UArg a0 - ignored
 *
 * @return  none
 */
static void Board_keyChangeHandler(UArg a0)
{
  if (appKeyChangeHandler != NULL)
  {
    keysPressed = 0;
#ifdef TELE_LOCAL
    if ( PIN_getInputValue(Board_KEY) == 0 )
    {
      keysPressed |= KEY_BTN;
    }
#endif    
#ifdef TELE_REMOTE
    if ( PIN_getInputValue(Board_KEY1) == 0 )
    {
      keysPressed |= KEY_BTN1;
    }

    if ( PIN_getInputValue(Board_KEY2) == 0 )
    {
      keysPressed |= KEY_BTN2;
    }
    if ( PIN_getInputValue(Board_KEY3) == 0 )
    {
      keysPressed |= KEY_BTN3;
    }
    if ( PIN_getInputValue(Board_KEY4) == 0 )
    {
      keysPressed |= KEY_BTN4;
    }
#endif
    // Notify the application
    (*appKeyChangeHandler)(keysPressed);
  }
}
/*********************************************************************
*********************************************************************/
