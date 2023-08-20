/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  Buzzer_Interface.h
 *  Module:  HAL/Buzzer
 *  Description:  Buzzer Driver Interface File
*******************************************************************/
#ifndef _BUZZER_INTERFACE_H_
#define _BUZZER_INTERFACE_H_
/********************************************************************/
/*****************************************
----------   Include Files    ------------
*****************************************/
#include "GPIO_Interface.h"
/*****************************************
---------   Prebuild Configure   ---------
*****************************************/
#define Buzzer_Pin					(Pin_0)
#define Buzzer_Port					(Port_A)
/*****************************************
---  Application Programming Interface  --
*****************************************/
/*****************************************************************************************
* Syntax          : void HAL_Buzzer_Initialization(void)
* Description     : This function initializes the buzzer peripheral by configuring its 
*                   associated GPIO pin as an output. The buzzer will be ready to be 
*                   toggled on/off or produce sound sequences post initialization.
*                   The buzzer's port and pin configurations are pre-defined using macros.
*                   It's essential to call this function before trying to control the buzzer.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : None
* Parameters (out): None
* Return value    : Void
* Note            : The macros Buzzer_Port and Buzzer_Pin should be defined in the project 
*                   configurations or headers.
*****************************************************************************************/
void HAL_Buzzer_Initialization(void);
/*****************************************************************************************
* Syntax          : void HAL_Buzzer_Start(void)
* Description     : This function toggles the state of the buzzer (turns it on if it was 
*                   off and vice versa). Once the buzzer is activated, it remains on for 
*                   a delay of 500 milliseconds, then it's turned off.
*                   The buzzer's port and pin configurations are pre-defined using macros.
*                   Ensure the buzzer has been initialized using HAL_Buzzer_Initialization 
*                   before calling this function.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : None
* Parameters (out): None
* Return value    : Void
* Note            : - The macros Buzzer_Port and Buzzer_Pin should be defined in the project 
*                     configurations or headers.
*                   - The delay_ms() function should be properly defined and configured 
*                     in your project to generate a 500ms delay.
*****************************************************************************************/
void HAL_Buzzer_Start(void);
/********************************************************************
 *  END OF FILE:  Buzzer_Interface.h
********************************************************************/
#endif
