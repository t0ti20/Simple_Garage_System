/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  USART_Interface.h
 *  Module:  MCAL/USART
 *  Description:  Universal Synchronous Asynchronous Receive Transmit Driver Interface File
*******************************************************************/
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "UART_Private.h"
#include "UART_Config.h"
#include "Macros.h"
/*****************************************
---  Application Programming Interface  --
*****************************************/
/********************************************************************
* Syntax          : UART_VidInitialization(u8 Copy_u8Mode, u8 Copy_u8Rx_Interrupt, u8 Copy_u8Tx_Interrupt)
* Description     : Initialize the UART module with specific configurations for mode, Rx interrupt, and Tx interrupt.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Mode (UART mode: Transmit, Receive or both),
*                   Copy_u8Rx_Interrupt (Enable or disable Rx interrupt),
*                   Copy_u8Tx_Interrupt (Enable or disable Tx interrupt)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void UART_VidInitialization (u8 Copy_u8Mode,u8 Copy_u8Rx_Interrupt,u8 Copy_u8Tx_Interrupt);

/********************************************************************
* Syntax          : void UART_VidReceive_Function(void(*UART_VidCallBack)(u8 *Received_Data))
* Description     : Sets the callback function that will be executed upon UART data reception via an interrupt.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : UART_VidCallBack (Pointer to callback function)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void UART_VidReceive_Function(void(*UART_VidCallBack)(u8 *Received_Data));

/********************************************************************
* Syntax          : UART_VidSend_Receive(u8 Copy_u8Mode, u8 *Copy_u8Data)
* Description     : Based on the provided mode, either sends data using UART or receives data through UART.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Mode (UART mode: Send or Receive),
*                   Copy_u8Data (Pointer to the data to send or to store received data)
* Parameters (out): None for Send mode. For Receive mode, data is stored in the address pointed by Copy_u8Data.
* Return value    : Void
********************************************************************/
void UART_VidSend_Receive (u8 Copy_u8Mode,u8 *Copy_u8Data);

/********************************************************************
* Syntax          : void UART_VidReceive_String(u8 *Copy_u8Data)
* Description     : Receives a string through UART until a termination character is encountered. 
				If the UART interrupt is enabled, the function uses interrupt-driven reception.
				Otherwise, it uses polling.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : None
* Parameters (out): Copy_u8Data (Pointer to store the received null-terminated string)
* Return value    : Void
********************************************************************/
void UART_VidReceive_String (u8 *Copy_u8Data);

/********************************************************************
* Syntax          : UART_VidSend_String(u8 *Copy_u8Data)
* Description     : Sends a null-terminated string using UART, followed by a carriage return.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Data (Pointer to the null-terminated string to be sent)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void UART_VidSend_String (u8 *Copy_u8Data);

#endif
/********************************************************************
 *  END OF FILE:  USART_Interface.h
********************************************************************/

