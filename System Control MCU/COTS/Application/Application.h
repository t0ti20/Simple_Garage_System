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
#include "Seven_Segment_Interface.h"
#include "Keypad_Interface.h"
#include "EXTI_Interface.h"
#include "GPIO_Interface.h"
#include "LCD_Interface.h"
#include "SPI_Interface.h"
/*****************************************
--------    Type  Definitions    ---------
*****************************************/
/*-------------- Database --------------*/
typedef struct DataBase_t
{
    u8 Valid_ID;
}DataBase_t;
/*****************************************
---------    Configure Macros    ---------
*****************************************/
/*------------ Application -------------*/
#define Max_ID                          (10)
#define Admin_Password                  "1234"
/*-------------- ECU Pins --------------*/
#define ECU_Port                        (GPIO_A)
#define Entrance_Pin                    (Pin_3)
#define Exit_Pin                        (Pin_2)
/*------------ ECU SS Pins -------------*/
#define SS_Port                         (GPIO_A)
#define Entrance_SS                     (Pin_0)
#define Exit_SS                         (Pin_1)
/*------------ ECU SS Pins -------------*/
#define Seven_Segment_Port              (GPIO_B)
#define Seven_Segment_Pins              {Pin_7,Pin_8,Pin_9,Pin_10,Pin_11,Pin_12,Pin_13,Pin_14}
#define Seven_Segment_Enable            (Pin_15)
/*****************************************
---  Application Programming Interface  --
*****************************************/
/****************************************************************************************************
* Function Name  : Application_VidSystem_Initialization
* Description    : This function initializes various components of the garage management system, ensuring 
*                  they are ready for use. It sets up the Keypad, LCD, SPI, External Interrupts for 
*                  entrance and exit gates, as well as the Seven Segment display.
* Sync-Async     : Synchronous
* Reentrancy     : Non-Reentrant
* Parameters (in): None
* Parameters (out): None
* Return value   : None
* Notes          : - Ensure that the required components (Keypad, LCD, SPI, EXTI, 7-Segment) are properly 
*                    connected and initialized.
*                  - The SS_Port for both Entrance and Exit is assumed to be the same. If this changes, 
*                    the function needs to be updated.
*                  - The A0 and A1 pins are used for initializing the Entrance and Exit Slave Selects 
*                    (SS) respectively.
*                  - All components' initialization functions should be defined properly.
*                  - After initializing the Slave Select (SS) pins for both Entrance and Exit, the 
*                    function sets them to a HIGH state. Ensure this is the correct state for your 
*                    application.
*                  - The SPI_Initialization function should be defined in a way to set up the SPI module 
*                    according to the requirements.
*                  - The EXTI_Entrance and EXTI_Exit represent the external interrupts for entrance and 
*                    exit. Their exact definition and behavior need to be defined elsewhere.
****************************************************************************************************/
void Application_VidSystem_Initialization(void);

/****************************************************************************************************
* Function Name  : Admin_Panel
* Description    : This function validates the admin's password using the Password_Check function. 
*                  If the password is correct, it prompts the admin to enter an ID which is then stored 
*                  in the DataBase. If the password is incorrect, it displays an error message on the LCD.
* Sync-Async     : Synchronous
* Reentrancy     : Non-Reentrant
* Parameters (in): u8 Input_Key - This is the key pressed by the admin which represents the password.
* Parameters (out): None
* Return value   : None
* Notes          : - Ensure that the required components (LCD, Keypad) are properly connected and initialized.
*                  - Ensure that the Password_Check function is implemented to validate the admin's password.
*                  - Ensure that the DataBase has enough capacity to store the new ID.
*                  - The DataBase should be an array or a structure that can store the valid IDs.
*                  - The DataBase_Index should be properly managed to prevent out-of-bounds access.
*                  - The function assumes that the admin enters a single-digit ID. If the ID has multiple 
*                    digits, the function needs to be modified.
****************************************************************************************************/
void Admin_Panel(u8 Input_Key);

/****************************************************************************************************
* Function Name  : EXTI_Entrance_ISR
* Description    : This interrupt service routine (ISR) is triggered by an external interrupt. It manages the 
*                  interaction with the SPI to read the ID of a client at the entrance. If the client ID 
*                  matches a valid ID in the database, it increments the number of garage clients. The result, 
*                  whether the ID is valid or not, is sent back via SPI.
* Sync-Async     : Asynchronous (It's an ISR)
* Reentrancy     : Non-Reentrant
* Parameters (in): None
* Parameters (out): None
* Return value   : None
* Notes          : - Ensure that the required components (LCD, SPI) are properly connected and initialized.
*                  - The function assumes that the DataBase array contains valid IDs.
*                  - DataBase_Index should be properly managed to prevent out-of-bounds access.
*                  - The function also assumes that the garage has a maximum capacity of 3 clients. 
*                    This can be adjusted if needed.
*                  - Proper debounce mechanisms should be implemented to avoid false triggers of the EXTI.
*                  - Ensure the SPI_Send_Receive_Data function correctly sends and receives data over SPI.
*                  - The function uses SS_Port and Entrance_SS to manage the slave select for the SPI communication.
****************************************************************************************************/
void EXTI_Entrance_ISR(void);

/****************************************************************************************************
* Function Name  : EXTI_Exit_ISR
* Description    : This interrupt service routine (ISR) is triggered by an external interrupt associated 
*                  with the exit gate. It handles the interaction with the SPI to read the ID of a client 
*                  attempting to exit. If the client ID matches a valid ID in the database and the garage 
*                  is not empty, it decrements the number of garage clients. The result (whether the ID 
*                  is valid, the garage is empty, or the ID is not found) is sent back via SPI.
* Sync-Async     : Asynchronous (It's an ISR)
* Reentrancy     : Non-Reentrant
* Parameters (in): None
* Parameters (out): None
* Return value   : None
* Notes          : - Ensure that the required components (LCD, SPI) are properly connected and initialized.
*                  - The function assumes that the DataBase array contains valid IDs.
*                  - DataBase_Index should be properly managed to prevent out-of-bounds access.
*                  - Proper debounce mechanisms should be implemented to avoid false triggers of the EXTI.
*                  - Ensure the SPI_Send_Receive_Data function correctly sends and receives data over SPI.
*                  - The function uses SS_Port and Exit_SS to manage the slave select for the SPI communication.
*                  - The function assumes that the garage has a maximum capacity of 3 clients. This can 
*                    be adjusted if needed.
*                  - Ensure error handling in cases where the garage is already empty.
****************************************************************************************************/
void EXTI_Exit_ISR(void);

/****************************************************************************************************
* Function Name  : Password_Check
* Description    : This function checks the admin's password by comparing each entered key against the 
*                  preset password stored in the Admin_Passowrd array. The password verification progress 
*                  is shown on the LCD screen by displaying asterisks (*).
* Sync-Async     : Synchronous
* Reentrancy     : Non-Reentrant
* Parameters (in): u8 First_Char - This is the first key pressed by the admin.
* Parameters (out): None
* Return value   : u8 - Returns TRUE if the password entered matches the stored password, otherwise returns FALSE.
* Notes          : - Ensure that the required components (LCD, Keypad) are properly connected and initialized.
*                  - The function assumes a 4-digit password. If the password length is different, 
*                    the function needs to be modified.
*                  - The Admin_Passowrd should be correctly initialized with the valid password.
****************************************************************************************************/
u8 Password_Check(u8 First_Char);

/********************************************************************
 *  END OF FILE:  Application.h
********************************************************************/
#endif
