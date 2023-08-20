/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  GPIO_Interface.h
 *  Module:  MCAL/GPIO
 *  Description:  General Input Output Driver Interface File
*******************************************************************/
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_
/*****************************************
----------   Include Files    ------------
*****************************************/
#include "Macros.h"
#include "GPIO_Private.h"
/*****************************************
---  Application Programming Interface  --
*****************************************/
/********************************************************************
* Syntax          : GPIO_VidInternal_Pin_Bull_Up(u8 Copy_u8Port, u8 Copy_u8Pin)
* Description     : Set the internal pull-up for a specific GPIO pin.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Pin (Pin number)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidInternal_Pin_Bull_Up(u8 Copy_u8Port,u8 Copy_u8Pin);

/********************************************************************
* Syntax          : GPIO_VidSet_Pin_Direction(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
* Description     : Set the direction (input or output) for a specific GPIO pin.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier "Port_A, Port_B, Port_C, Port_D")
*                   Copy_u8Pin (Pin number)
*                   Copy_u8Direction (Direction "INPUT or OUTPUT")
* Parameters (out): None
* Return value    : Void
********************************************************************/	
void GPIO_VidSet_Pin_Direction(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Direction);

/********************************************************************
* Syntax          : GPIO_VidSet_Pin_Value(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
* Description     : Set the value (HIGH or LOW) for a specific GPIO pin.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Pin (Pin number), Copy_u8Value (Value to be set: HIGH/LOW)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidSet_Pin_Value(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value);

/********************************************************************
* Syntax          : GPIO_VidToggle_Pin_Value(u8 Copy_u8Port, u8 Copy_u8Pin)
* Description     : Toggle the value (HIGH to LOW or vice-versa) for a specific GPIO pin.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Pin (Pin number)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidToggle_Pin_Value(u8 Copy_u8Port,u8 Copy_u8Pin);

/********************************************************************
* Syntax          : GPIO_VidGet_Pin_Value(u8 Copy_u8Port, u8 Copy_u8Pin, u8 *Copy_Pu8Pin_Value)
* Description     : Retrieve the value (HIGH or LOW) of a specific GPIO pin.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Pin (Pin number)
* Parameters (out): Copy_Pu8Pin_Value (Pointer to store the retrieved pin value)
* Return value    : Void
********************************************************************/
void GPIO_VidGet_Pin_Value(u8 Copy_u8Port,u8 Copy_u8Pin,u8 *Copy_Pu8Pin_Value);

/********************************************************************
* Syntax          : GPIO_VidInternal_Port_Bull_Up(u8 Copy_u8Port)
* Description     : Activate the internal pull-up for an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidInternal_Port_Bull_Up(u8 Copy_u8Port);

/********************************************************************
* Syntax          : GPIO_VidSet_Whole_Port_Direction(u8 Copy_u8Port, u8 Copy_u8Direction)
* Description     : Set the direction (INPUT or OUTPUT) for an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Direction (Direction to be set: INPUT/OUTPUT)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidSet_Whole_Port_Direction(u8 Copy_u8Port,u8 Copy_u8Direction);

/********************************************************************
* Syntax          : GPIO_VidSet_Port_Direction(u8 Copy_u8Port, u8 Copy_u8Value)
* Description     : Set the direction value for an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Value (Value to be set for the direction of the entire port)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidSet_Port_Direction(u8 Copy_u8Port,u8 Copy_u8Direction);

/********************************************************************
* Syntax          : GPIO_VidSet_Port_Value(u8 Copy_u8Port, u8 Copy_u8Value)
* Description     : Set the value for an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Value (Value to be set for the entire port)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidSet_Port_Value(u8 Copy_u8Port,u8 Copy_u8Value);

/********************************************************************
* Syntax          : GPIO_VidToggle_Port_Value(u8 Copy_u8Port)
* Description     : Toggle the values of an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidToggle_Port_Value(u8 Copy_u8Port);

/********************************************************************
* Syntax          : GPIO_VidGet_Port_Value(u8 Copy_u8Port, u8 *Copy_u8Port_Value)
* Description     : Retrieve the value of an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier)
* Parameters (out): Copy_u8Port_Value (Pointer to store the retrieved port value)
* Return value    : Void
********************************************************************/
void GPIO_VidGet_Port_Value(u8 Copy_u8Port,u8 *Copy_Pu8Port_Value);

/********************************************************************
* Syntax          : GPIO_VidEdit_Port_Value(u8 Copy_u8Port, u8 Copy_u8Pins, u8 Copy_u8Value)
* Description     : Edit specific segments (HIGH or LOW nibble) of the port's value without altering the other segment.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), 
*                   Copy_u8Pins (Which segment to edit: HI/LOW nibble),
*                   Copy_u8Value (Value to be set for the selected segment)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidEdit_Port_Value(u8 Copy_u8Port,u8 Copy_u8Pins,u8 Copy_u8Value);

/********************************************************************
* Syntax          : GPIO_VidGlobal_Interrupt_Enable(void)
* Description     : Enable the global interrupts.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : None
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidGlobal_Interrupt_Enable(void);

#endif
/********************************************************************
 *  END OF FILE:  GPIO_Interface.h
********************************************************************/
