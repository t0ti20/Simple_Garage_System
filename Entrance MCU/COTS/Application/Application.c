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
/*---------- Flag To Scan ID -----------*/
u8 ID_Scaned_Flag=False;
/*****************************************
----------- Main Application  ------------
*****************************************/
/*************************************************************************************************
* Function Name   : main
* Description     : This is the main function of the system. It initializes the various components,
*                   then enters an infinite loop where it waits for the user to scan their ID. 
*                   Based on the scanned ID, it takes appropriate actions, either opening the gate 
*                   or indicating an invalid ID.
* Sync-Async      : Synchronous (as it's the primary flow of the application)
* Reentrancy      : Non-Reentrant (as the main function)
* Parameters (in) : None
* Parameters (out): None
* Return value    : int - Standard for the main function. Generally returns 0.
* Notes           : - Ensure that all the modules and components like the LCD, Gate, etc., are 
*                     properly initialized before entering the main loop.
*                   - The two functions `Scanned_ID_True` and `Scanned_ID_False` are responsible 
*                     for taking actions when a valid or invalid ID is scanned respectively.
*                   - After each ID scan and action, the ID_Scaned_Flag is reset to be ready for 
*                     the next scan.
*                   - It's crucial to ensure that no two processes modify the `ID_Scaned_Flag` 
*                     simultaneously to prevent race conditions.
*                   - If the system grows in complexity, consider using a state machine or task 
*                     scheduler for more structured and scalable management.
*************************************************************************************************/
int main(void)
{
     /* Initialize the system components */
     Application_VidSystem_Initialization();
     while(True)
     {
          /* Close the garage gate */
          HAL_Gate_Close();
          /* Display a welcome message on the LCD */
          LCD_VidClear();
          LCD_VidSet_Position(ONE,THREE);
          LCD_VidSend_String((u8 const *)"- WELCOME -");
          LCD_VidSet_Position(TWO,THREE);
          LCD_VidSend_String((u8 const *)"-----------");
          LCD_VidSet_Position(THREE,ZERO);
          /* Prompt the user to scan their ID */
          LCD_VidSend_String((u8 const *)"Please Scan ID :");
          /* Wait until an ID is scanned */
          while(!ID_Scaned_Flag);
          /* Determine the next action based on the scanned ID */
          if(ID_Scaned_Flag=='1')Scanned_ID_True();
          else Scanned_ID_False();
          /* Reset the ID scanned flag for the next iteration */
          ID_Scaned_Flag=ZERO;
     }
     return ONE;
}
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
void Scanned_ID_True(void)
{
     /* Clear the LCD and display the gate opening message */
     LCD_VidClear();
     LCD_VidSet_Position(ONE,TWO);
     /* Turn on the green LED to indicate a valid ID */
     HAL_LED_ID_State(ONE);
     /* Open the garage gate */
     LCD_VidSend_String((u8 const *)"Gate  Opened");
     HAL_Gate_Open();
     /* Wait until the motion sensor is triggered */
     while (HAL_Motion_Sensor_Get_State());
}
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
void Scanned_ID_False(void)
{
     /* Clear the LCD and display an error message */
     LCD_VidClear();
     LCD_VidSet_Position(ONE,TWO);
     /* Turn on the red LED to indicate an invalid ID */
     HAL_LED_ID_State(ZERO);
     /* Display an invalid ID error message */
     LCD_VidSend_String((u8 const *)"Invalid ID !");
     /* Sound the buzzer to alert about the invalid ID */
     HAL_Buzzer_Start();
}
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
void Application_VidSystem_Initialization(void)
{
     /* Initialize LCD */
     LCD_VidInitialization();
     /* Initialize LED */
     HAL_LED_Initialization();
     /* Initialize Buzzer */
     HAL_Buzzer_Initialization();
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
void Application_VidUART_Receiving_ISR(u8 *Received_Data)
{
     /*Get Card ID Using UART*/
     UART_VidSend_String((u8*)"ID Scaned = ");
     /*Print Scaned ID On UART*/
     UART_VidSend_Receive(Send,Received_Data);
     /*Check Scaned ID From Master Using SPI*/
     ID_Scaned_Flag=HAL_Communication_ID_Check(*Received_Data);
     UART_VidSend_String((u8*)"\r------------------\r");
}
/********************************************************************
 *  END OF FILE:  Application.c
********************************************************************/
