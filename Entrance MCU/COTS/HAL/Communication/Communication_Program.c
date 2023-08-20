/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  Communication_Program.c
 *  Module:  HAL/Communication
 *  Description:  Communication Driver Program File
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "Communication_Interface.h"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
/*****************************************************************************************
* Syntax          : void HAL_Communication_Initialization(void)
* Description     : This function initializes the Communication peripheral by configuring its 
*                   associated GPIO pin as an output. The Communication will be ready to be 
*                   toggled on/off or produce sound sequences post initialization.
*                   The Communication's port and pin configurations are pre-defined using macros.
*                   It's essential to call this function before trying to control the Communication.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : None
* Parameters (out): None
* Return value    : Void
* Note            : The macros Communication_Port and Communication_Pin should be defined in the project 
*                   configurations or headers.
*****************************************************************************************/
void HAL_Communication_Initialization(void)
{
     /*Initialize SPI*/
     SPI_VidInitialization(SPI_Slave,SPI_Interrupt_Disable);
     /*Set Master Pin To Inform Master*/
     GPIO_VidSet_Pin_Direction(Master_Port,Master_Pin,OUTPUT);
}
/*****************************************************************************************
* Syntax          : void HAL_Communication_Start(void)
* Description     : This function toggles the state of the Communication (turns it on if it was 
*                   off and vice versa). Once the Communication is activated, it remains on for 
*                   a delay of 500 milliseconds, then it's turned off.
*                   The Communication's port and pin configurations are pre-defined using macros.
*                   Ensure the Communication has been initialized using HAL_Communication_Initialization 
*                   before calling this function.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : None
* Parameters (out): None
* Return value    : Void
* Note            : - The macros Communication_Port and Communication_Pin should be defined in the project 
*                     configurations or headers.
*                   - The delay_ms() function should be properly defined and configured 
*                     in your project to generate a 500ms delay.
*****************************************************************************************/
u8 HAL_Communication_ID_Check(u8 Data)
{
     /*Inform Master*/
     GPIO_VidSet_Pin_Value(Port_A,Pin_4,HI);
     /*Send Received Data*/
     SPI_VidSend_Receive(&Data);
     GPIO_VidSet_Pin_Value(Port_A,Pin_4,LOW);
     /*Get Id Status*/
     SPI_VidSend_Receive(&Data);
     return Data;
}
/********************************************************************
 *  END OF FILE:  Communication_Program.c
********************************************************************/
