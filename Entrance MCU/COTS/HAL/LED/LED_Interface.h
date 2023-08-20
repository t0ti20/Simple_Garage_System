/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  LED_Interface.h
 *  Module:  HAL/LED
 *  Description:  LED Alarm Interface File
*******************************************************************/
#ifndef _LED_INTERFACE_H_
#define _LED_INTERFACE_H_
/********************************************************************/
/*****************************************
----------   Include Files    ------------
*****************************************/
#include "GPIO_Interface.h"
/*****************************************
---------   Prebuild Configure   ---------
*****************************************/
#define RED_LED					(Pin_1)
#define GREEN_LED					(Pin_2)
#define LED_Port				     (Port_A)
/*****************************************
-------   Configuration Macros   ---------
*****************************************/
#define ID_Valid                        (1)
#define ID_Not_Valid                    (0)
/*****************************************
---  Application Programming Interface  --
*****************************************/
/*****************************************************************************************
* Syntax          : void HAL_LED_Initialization(void)
* Description     : This function initializes the specific pins for the green and red LEDs 
*                   as output. This ensures that these pins are ready to control the 
*                   corresponding LEDs.
*                   The LED port and pin configurations are pre-defined using macros.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : None
* Parameters (out): None
* Return value    : Void
* Note            : - The macros LED_Port, GREEN_LED, and RED_LED should be defined in the 
*                     project configurations or headers.
*                   - Before driving the LEDs (turning them ON/OFF), ensure they have been 
*                     initialized using HAL_LED_Initialization.
*****************************************************************************************/
void HAL_LED_Initialization(void);
/******************************************************************************************
* Function Name  : HAL_LED_ID_State
* Description    : This function controls the state of the LEDs based on the provided 
*                  ID state. If the ID state is '1' (true), the GREEN LED is turned on 
*                  for one second, otherwise, the RED LED is turned on for one second.
*                  After the duration, the LED is turned off.
*                  The LED port and pin configurations are assumed to be pre-defined using 
*                  macros in the project.
* Sync-Async     : Synchronous
* Reentrancy     : Non-Reentrant
* Parameters (in): ID_State - An unsigned 8-bit integer representing the LED state. 
*                  '1' - GREEN LED
*                  '0' - RED LED
* Parameters (out): None
* Return value   : Void
* Notes          : - The macros LED_Port, GREEN_LED, and RED_LED should be defined in the 
*                    project configurations or headers.
*                  - Before driving the LEDs, ensure they have been initialized using 
*                    HAL_LED_Initialization function.
*                  - The delay function (delay_ms) is assumed to be available in the project.
******************************************************************************************/
void HAL_LED_ID_State(u8 ID_State);
/********************************************************************
 *  END OF FILE:  LED_Interface.h
********************************************************************/
#endif
