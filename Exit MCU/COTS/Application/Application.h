/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  Application.h
 *  Module:  ./Application
 *  Description:  Application Headder File
*******************************************************************/
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
/********************************************************************/
/*****************************************
----------   Include Files    ------------
*****************************************/
#include "Communication_Interface.h"
#include "Motion_Sensor_Interface.h"
#include "UART_Interface.h"
#include "Gate_Interface.h"
#include "SPI_Interface.h"
/*****************************************
---  Application Programming Interface  --
*****************************************/
/*****************************************************************************************
* Function Name   : Application_VidSystem_Initialization
* Description     : This function is responsible for initializing various system components 
*                   required for the main application. These include the gate mechanism, 
*                   the motion sensor, communication module, and RFID module.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - It's crucial to call this function before invoking any operations 
*                     related to the initialized modules.
*                   - The function initializes the RFID module in the mode to both transmit 
*                     and receive, enabling the reception and setting the callback function 
*                     to `Application_VidUART_Receiving_ISR`.
*                   - Make sure the required hardware components are properly connected 
*                     and powered up before initializing.
*                   - If any of the initialization functions have return status or error codes, 
*                     consider adding error-checking mechanisms to handle initialization failures.
*                   - Initialization order matters; ensure dependencies between components 
*                     are addressed in the sequence of initialization.
*****************************************************************************************/
void Application_VidSystem_Initialization(void);

/*****************************************************************************************
* Function Name   : Application_VidUART_Receiving_ISR
* Description     : This function acts as an Interrupt Service Routine (ISR) triggered by 
*                   UART reception events. Upon the reception of data, it sends the received 
*                   ID to the UART and subsequently checks the received ID via SPI communication.
* Sync-Async      : Asynchronous (due to its ISR nature)
* Reentrancy      : Non-Reentrant (typical for ISRs, but verify based on actual application behavior)
* Parameters (in) : u8 *Received_Data - A pointer to the data received through UART.
* Parameters (out): None
* Return value    : None
* Notes           : - The function first sends the "ID Scaned = " string to indicate the 
*                     beginning of the ID scanning process.
*                   - It then sends the actual received ID.
*                   - The `HAL_Communication_ID_Check` function is used to verify the 
*                     received ID, and based on the verification, the `ID_Scaned_Flag` 
*                     is set appropriately.
*                   - The ISR concludes by sending a line separator to UART for clarity.
*                   - Ensure that the UART communication is appropriately set up, and that 
*                     buffer overflows or other errors are managed correctly in the main 
*                     application or lower-level driver functions.
*                   - Avoid performing long operations inside the ISR; the function should 
*                     return control as soon as possible to not block other processes.
*                   - If other components depend on the state of `ID_Scaned_Flag`, make sure 
*                     they account for its asynchronous nature.
*****************************************************************************************/
void Application_VidUART_Receiving_ISR(u8 *Received_Data);

/********************************************************************
 *  END OF FILE:  Application.h
********************************************************************/
#endif
