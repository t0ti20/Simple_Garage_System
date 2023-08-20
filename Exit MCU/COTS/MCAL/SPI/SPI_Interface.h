/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  SPI_Interface.h
 *  Module:  MCAL/SPI
 *  Description:  Serial Peripheral Interface Interface File
*******************************************************************/
#ifndef _SPI_INTERFACE_H_
#define _SPI_INTERFACE_H_
/********************************************************************/
/*****************************************
----------   Include Files    ------------
*****************************************/
#include "GPIO_Interface.h"
#include "UART_Interface.h"
#include "SPI_Private.h"
#include "SPI_Config.h"
/*****************************************
---  Application Programming Interface  --
*****************************************/
/********************************************************************
* Syntax          : void SPI_VidInitialization(u8 Copy_u8Master_Slave,u8 Copy_u8Interrupt)
* Description     : Initializes the SPI (Serial Peripheral Interface) module.
				This function allows the user to set the device as a master or slave
				Enable or disable interrupts, and configure the other necessary SPI settings.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : Copy_u8Master_Slave (Master or Slave mode selector), 
*                   Copy_u8Interrupt (Interrupt enable or disable flag)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void SPI_VidInitialization (u8 Copy_u8Master_Slave,u8 Copy_u8Interrupt);

/********************************************************************
* Syntax          : void SPI_VidSend_Receive(u8 Copy_u8Mode,u8 *Copy_u8Data)
* Description     : Sends or receives data using the SPI (Serial Peripheral Interface) module.
				The function allows for sending data, receiving data, or flushing the SPI buffer.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : Copy_u8Mode (Mode selector, either to send or receive), 
*                   Copy_u8Data (Pointer to the data byte to send or store received data)
* Parameters (out): Copy_u8Data (Pointer updates with received data if in Receive mode)
* Return value    : Void
********************************************************************/
void SPI_VidSend_Receive(u8 *Copy_u8Reading);

/********************************************************************
* Syntax          : void SPI_VidInturrept(void(*Copy_VidInturrept)(void))
* Description     : Sets the callback function for the SPI interrupt. 
*                   The provided function will be executed when the SPI interrupt occurs.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant (due to shared resources)
* Parameters (in) : Copy_VidInturrept (Pointer to the callback function to be set for the SPI interrupt)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void SPI_VidInturrept(void(*Copy_VidInturrept)(void));

/********************************************************************
 *  END OF FILE:  SPI_Interface.h
 ********************************************************************/
#endif

