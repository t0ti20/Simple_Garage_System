/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  Motion_Sensor_Program.c
 *  Module:  HAL/Motion_Sensor
 *  Description:  Motion_Sensor Driver Program File
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "Motion_Sensor_Interface.h"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
/******************************************************************************************
* Function Name  : HAL_Motion_Sensor_Initialization
* Description    : This function initializes the motion sensor by setting its associated 
*                  pin as an INPUT. The motion sensor mechanism is assumed to be connected 
*                  to a GPIO pin represented by Motion_Sensor_Pin and on port Motion_Sensor_Port.
*                  The GPIO configuration details are abstracted within the 
*                  GPIO_VidSet_Pin_Direction function.
* Sync-Async     : Synchronous
* Reentrancy     : Non-Reentrant
* Parameters (in): None
* Parameters (out): None
* Return value   : Void
* Notes          : - Before using this function, ensure that the motion sensor is properly 
*                    connected and that the Motion_Sensor_Pin and Motion_Sensor_Port macros 
*                    are correctly defined in the project configurations or headers.
*                  - The GPIO_VidSet_Pin_Direction function should be properly defined and 
*                    implemented in the project.
******************************************************************************************/
void HAL_Motion_Sensor_Initialization(void)
{
     GPIO_VidSet_Pin_Direction(Motion_Sensor_Port,Motion_Sensor_Pin,INPUT);
}
/******************************************************************************************
* Function Name  : HAL_Motion_Sensor_Get_State
* Description    : This function retrieves the current state of the motion sensor. It 
*                  checks the state of the GPIO pin associated with the motion sensor and 
*                  returns its state.
*                  The GPIO reading details are abstracted within the 
*                  GPIO_VidGet_Pin_Value function.
* Sync-Async     : Synchronous
* Reentrancy     : Reentrant
* Parameters (in): None
* Parameters (out): None
* Return value   : u8 - The state of the motion sensor.
*                  Returns HI (1) if motion is detected, LOW (0) otherwise.
* Notes          : - Before using this function, ensure that the motion sensor is properly 
*                    connected and that the Motion_Sensor_Pin and Motion_Sensor_Port macros 
*                    are correctly defined in the project configurations or headers.
*                  - The GPIO_VidGet_Pin_Value function should be properly defined and 
*                    implemented in the project.
******************************************************************************************/
u8 HAL_Motion_Sensor_Get_State(void)
{  
     u8 State;  
     GPIO_VidGet_Pin_Value(Motion_Sensor_Port,Motion_Sensor_Pin,&State);
     return State;
}
/********************************************************************
 *  END OF FILE:  Motion_Sensor_Program.c
********************************************************************/
