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
#include "Motion_Sensor_Interface.h"
#include "Communication_Interface.h"
#include "Buzzer_Interface.h"
#include "UART_Interface.h"
#include "Gate_Interface.h"
#include "LCD_Interface.h"
#include "SPI_Interface.h"
#include "LED_Interface.h"
/*****************************************
---  Application Programming Interface  --
*****************************************/
/**********************************************************************************************
* Function Name   : Application_VidSystem_Initialization
* Description     : This function initializes all the peripherals and modules required for the 
*                   application to function properly. It sets up the LCD for display, LED for 
*                   indication, Buzzer for alerts, Gate controls, Motion Sensor for detection, 
*                   communication module for data transfers and the RFID module for ID scanning.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - It is critical to call this function once at the start of the application 
*                     (e.g., in the main function) to ensure that all peripherals and modules 
*                     are correctly initialized before their use.
*                   - The initialization sequence can be important in some cases. Ensure dependencies 
*                     between peripherals are managed correctly. 
*                   - Make sure the connected peripherals (LCD, LED, Buzzer, etc.) are powered on 
*                     and correctly wired to the corresponding microcontroller pins.
*                   - Ensure appropriate configurations (like baud rate, communication protocols, 
*                     etc.) are set for each module based on the application's requirements.
***********************************************************************************************/
void Application_VidSystem_Initialization(void);

/*************************************************************************************************
* Function Name   : Scanned_ID_True
* Description     : This function is called when a valid ID is scanned. It displays a gate opening 
*                   message on the LCD, turns on the green LED, opens the garage gate, and then waits 
*                   for the motion sensor to trigger (indicating that a vehicle has passed).
* Sync-Async      : Synchronous (waits for motion sensor to trigger)
* Reentrancy      : Non-Reentrant
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - Ensure the LCD, LED, Gate, and Motion Sensor modules are properly initialized.
*                   - The function waits indefinitely for the motion sensor to trigger, which could 
*                     lead to a system hang if the sensor doesn't work correctly. Ensure the sensor 
*                     is reliable or consider adding a timeout.
*                   - This function assumes that the motion sensor returns a "true" value when triggered. 
*                     Ensure that the `HAL_Motion_Sensor_Get_State` function is set up to return 
*                     appropriate values.
*                   - The green LED (`HAL_LED_ID_State(ONE)`) is used to indicate a valid ID. Ensure 
*                     that there's no confusion with other system indications.
*************************************************************************************************/
void Scanned_ID_True(void);

/*************************************************************************************************
* Function Name   : Scanned_ID_False
* Description     : This function is invoked when an invalid ID is scanned. It displays an error message 
*                   on the LCD, activates the red LED to indicate the invalid ID, and sounds the buzzer 
*                   to alert the user about the invalid ID attempt.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           :
*                   - Ensure the LCD, LED, and Buzzer modules are properly initialized.
*                   - This function will briefly activate the buzzer. Ensure that the buzzer's duration 
*                     and volume are appropriate for the use case.
*                   - The red LED (`HAL_LED_ID_State(ZERO)`) is used to indicate an invalid ID. Ensure 
*                     that there's no confusion with other system indications.
*                   - Consider the environment and the users. A loud buzzer might not be suitable 
*                     for all scenarios. The volume and duration of the buzzer should be adjusted 
*                     accordingly.
*************************************************************************************************/
void Scanned_ID_False(void);

/*************************************************************************************************
* Function Name   : Application_VidUART_Receiving_ISR
* Description     : This function acts as an interrupt service routine (ISR) that gets triggered 
*                   when data is received through the UART module. It retrieves the scanned card ID 
*                   using UART, sends this ID to the UART terminal for monitoring, and then checks 
*                   the scanned ID with a master list using SPI communication.
* Sync-Async      : Asynchronous (being an ISR)
* Reentrancy      : Non-Reentrant (generally, ISRs should not be reentrant)
* Parameters (in) : u8 *Received_Data - A pointer to the data received through UART.
* Parameters (out): None
* Return value    : None
* Notes           : - It's vital to ensure that the UART module is correctly initialized and has 
*                     its interrupts enabled to use this ISR.
*                   - Given the nature of ISRs, it's generally advisable to keep them as short and 
*                     quick as possible to avoid missing other system events.
*                   - Ensure the SPI module (HAL_Communication_ID_Check function in particular) 
*                     and UART module are appropriately initialized and set up for this ISR to function.
*                   - Given that this is an ISR, avoid using it to execute prolonged tasks. If required, 
*                     set flags or use other mechanisms to offload extended tasks to the main loop or other 
*                     non-interrupt contexts.
*************************************************************************************************/
void Application_VidUART_Receiving_ISR(u8 *Received_Data);

/********************************************************************
 *  END OF FILE:  Application.h
********************************************************************/
#endif
