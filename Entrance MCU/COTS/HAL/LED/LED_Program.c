/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  LED_Program.c
 *  Module:  HAL/LED
 *  Description:  LED Driver Program File
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "LED_Interface.h"
/*****************************************
----------    GLOBAL DATA     ------------
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
void HAL_LED_Initialization(void)
{
     GPIO_VidSet_Pin_Direction(LED_Port,GREEN_LED,OUTPUT);
     GPIO_VidSet_Pin_Direction(LED_Port,RED_LED,OUTPUT);
}
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
*                               '1' - GREEN LED
*                               '0' - RED LED
* Parameters (out): None
* Return value   : Void
* Notes          : - The macros LED_Port, GREEN_LED, and RED_LED should be defined in the 
*                    project configurations or headers.
*                  - Before driving the LEDs, ensure they have been initialized using 
*                    HAL_LED_Initialization function.
*                  - The delay function (delay_ms) is assumed to be available in the project.
******************************************************************************************/
void HAL_LED_ID_State(u8 ID_State)
{
     GPIO_VidSet_Pin_Value(LED_Port,(ID_State?GREEN_LED:RED_LED),HI);
     delay_ms(1000);
     GPIO_VidSet_Pin_Value(LED_Port,(ID_State?GREEN_LED:RED_LED),LOW);
}
/********************************************************************
 *  END OF FILE:  LED_Program.c
********************************************************************/
