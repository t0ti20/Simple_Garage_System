/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  Gate_Interface.h
 *  Module:  HAL/Gate
 *  Description:  Gate Driver Interface File
*******************************************************************/
#ifndef _GATE_INTERFACE_H_
#define _GATE_INTERFACE_H_
/********************************************************************/
/*****************************************
----------   Include Files    ------------
*****************************************/
#include "Timer_Interface.h"
/*****************************************
---  Application Programming Interface  --
*****************************************/
/*****************************************************************************************
* Syntax          : void HAL_Gate_Initialization(void)
* Description     : This function initializes the Gate peripheral by configuring its 
*                   associated GPIO pin as an output. The Gate will be ready to be 
*                   toggled on/off or produce sound sequences post initialization.
*                   The Gate's port and pin configurations are pre-defined using macros.
*                   It's essential to call this function before trying to control the Gate.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : None
* Parameters (out): None
* Return value    : Void
* Note            : The macros Gate_Port and Gate_Pin should be defined in the project 
*                   configurations or headers.
*****************************************************************************************/
void HAL_Gate_Initialization(void);
/******************************************************************************************
* Function Name  : HAL_Gate_Open
* Description    : This function commands the gate to open using Pulse Width Modulation 
*                  (PWM). The gate control mechanism is assumed to be connected to a PWM 
*                  pin driven by Timer_0. The duty cycle set here is 98%, which corresponds 
*                  to the open command for the gate.
*                  The timer configuration and control details are abstracted within the 
*                  Timer_VidPwm_Duty_Cycle function.
* Sync-Async     : Synchronous
* Reentrancy     : Non-Reentrant
* Parameters (in): None
* Parameters (out): None
* Return value   : Void
******************************************************************************************/
void HAL_Gate_Open(void);
/******************************************************************************************
* Function Name  : HAL_Gate_Close
* Description    : This function commands the gate to close using Pulse Width Modulation 
*                  (PWM). The gate control mechanism is assumed to be connected to a PWM 
*                  pin driven by Timer_0. The duty cycle set here is 49%, which corresponds 
*                  to the close command for the gate.
*                  The timer configuration and control details are abstracted within the 
*                  Timer_VidPwm_Duty_Cycle function.
* Sync-Async     : Synchronous
* Reentrancy     : Non-Reentrant
* Parameters (in): None
* Parameters (out): None
* Return value   : Void
******************************************************************************************/
void HAL_Gate_Close(void);
/********************************************************************
 *  END OF FILE:  Gate_Interface.h
********************************************************************/
#endif
