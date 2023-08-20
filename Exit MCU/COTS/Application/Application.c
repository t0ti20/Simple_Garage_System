/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  Application.c
 *  Module:  ./Application
 *  Description:  Entrance Gate Control Unit ECU Main Application
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "Application.h"
/*****************************************
----------- Global Variables -------------
*****************************************/
/*--------- Flag To Scaned ID ----------*/
u8 ID_Scaned_Flag=False;
/*****************************************
----------- Main Application  ------------
*****************************************/
/*************************************************************************************************
* Function Name   : main
* Description     : The entry point of the program. This function initializes the entire system's modules,
*                   continuously checks for a scanned ID, and takes appropriate actions based on the ID 
*                   scanned.
* Sync-Async      : Synchronous
* Reentrancy      : Not Applicable (Entry point)
* Parameters (in) : None
* Parameters (out): Integer indicating program's exit status. Conventionally, an exit value of ZERO 
*                   indicates successful completion.
* Return value    : int - Exit status of the program.
* Notes           : - The function assumes that once the ID is scanned and found to be true, the gate 
*                     will open, wait for a motion sensor trigger (e.g., vehicle passing through the gate), 
*                     and then close again. This sequence is repeated indefinitely.
*                   - Ensure that all modules (`HAL_Gate_Open`, `HAL_Motion_Sensor_Get_State`, etc.) are 
*                     properly initialized before this function is called.
*                   - The function uses a "Busy Wait" approach which might not be efficient for power consumption.
*                     Consider using interrupts or other mechanisms if power consumption is a concern.
*                   - The program does not handle cases where an invalid ID is scanned. Error handling 
*                     mechanisms should be added for better robustness.
*                   - Always ensure that safety and security considerations are taken into account, 
*                     especially when dealing with gate control systems.
*************************************************************************************************/
int main(void)
{
     /*Initialize Whole System Modules*/
     Application_VidSystem_Initialization();
     while(True)
     {
          /*Close Exit Gate*/
          HAL_Gate_Close();
          /*Busy Wait For Scaned ID*/
          while(!ID_Scaned_Flag);
          /*If Flag Is True*/
          if(ID_Scaned_Flag=='1')
          {
               /*Open Exit Gate*/
               HAL_Gate_Open();
               /*Wait For Motion Sensor*/
               while (HAL_Motion_Sensor_Get_State());
               /* Reset the ID scanned flag for the next iteration */
               ID_Scaned_Flag=ZERO;
          }
     }
}
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
void Application_VidSystem_Initialization(void)
{
     /* Initialize Gate */
     HAL_Gate_Initialization();
     /* Initialize Motion Sensor */
     HAL_Motion_Sensor_Initialization();
     /* Initialize Communication Module */
     HAL_Communication_Initialization();
     /* Initialize RFID Module */
     UART_VidInitialization(Transmit_Recive,Rx_Enable,Tx_Disable);
     UART_VidReceive_Function(Application_VidUART_Receiving_ISR);
}
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
void Application_VidUART_Receiving_ISR(u8 *Received_Data)
{
     UART_VidSend_String((u8*)"ID Scaned = ");
     UART_VidSend_Receive(Send,Received_Data);
     ID_Scaned_Flag=HAL_Communication_ID_Check(*Received_Data);
     UART_VidSend_String((u8*)"\r------------------\r");
}
/********************************************************************
 *  END OF FILE:  Application.c
********************************************************************/
