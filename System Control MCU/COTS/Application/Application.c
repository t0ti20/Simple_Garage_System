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
/*----------- Saved DataBase -----------*/
DataBase_t DataBase[Max_ID]=
{
    {'1'},
    {'2'},
    {'3'},
    {'4'}
}; 
/*---------- Global Variables ----------*/
u8 Garage_Clients=ZERO,DataBase_Index=FOUR,Admin_Passowrd[5]=Admin_Password;
/*----------- Entrance EXTI ------------*/
EXTI_Config_t EXTI_Entrance=
{
    ECU_Port,
    Entrance_Pin,
    Rising_Edge,
    ENABLE,
    Disable,
    EXTI_Entrance_ISR
};
/*------------- Exit EXTI --------------*/
EXTI_Config_t EXTI_Exit=
{
    ECU_Port,
    Exit_Pin,
    Rising_Edge,
    ENABLE,
    Disable,
    EXTI_Exit_ISR
};
/*---------- SPI Configuration ---------*/
SPI_Config_t SPI=
{
    NULL,
    SPI_1,
    SPI_Master,
    SPI_Tx_Rx_Two_Line,
    SPI_MSBF,
    SPI_8_Bit,
    SPI_Idle_Hi_Second_Edge,
    SPI_Prescalar_8,
    SPI_Disable_Interrupt,
    SPI_Software_Disable
};
/*------------- Entrance SS ------------*/
GPIO_Pin_Config_t A1=
{
    Pin_1,
    Output_Push_Pull,
    Output_10
};
/*--------------- Exit SS --------------*/
GPIO_Pin_Config_t A0=
{
    Pin_0,
    Output_Push_Pull,
    Output_10
};
/*------------ Seven Segment -----------*/
Seven_Segment_t Segment=
{
    Seven_Segment_Port,
    Common_Cathode,
    Seven_Segment_Pins,
    Seven_Segment_Enable
};
/*****************************************
----------- Main Application  ------------
*****************************************/
/******************************************************************************************
* Function Name  : main
* Description    : This is the entry point of the program. It initializes the system using 
*                  Application_VidSystem_Initialization function and then enters an infinite
*                  loop where it checks for keypad input and updates the seven segment display.
*                  If a key is pressed on the keypad, it calls the Admin_Panel function 
*                  with the pressed key as an argument.
* Sync-Async     : Synchronous
* Reentrancy     : Non-Reentrant
* Parameters (in): None
* Parameters (out): None
* Return value   : int - The termination status of the program. 
*                  As per C standard for hosted environments, a return of 0 indicates success 
*                  and any other value indicates failure. Since this is embedded software 
*                  with an infinite loop, it typically never returns.
* Notes          : - Ensure that the required components (LCD, Keypad, Seven Segment display, 
*                    etc.) are properly connected and initialized.
*                  - Ensure that all the required functions and macros are properly defined 
*                    in the project.
*                  - Make sure that the Seven_Segment_Send_One_Digit function updates the 
*                    seven segment with the correct digit.
*                  - The Admin_Panel function should be properly implemented to handle 
*                    admin actions based on the key pressed.
******************************************************************************************/
int main(void)
{   
    Application_VidSystem_Initialization();
    while(TRUE)
    {
        u8 Input_Flag=Keypad_Not_Pressed;
        /*Update Seven Segment*/
        Seven_Segment_Send_One_Digit(&Segment,(THREE-Garage_Clients));
        /* Input From Admin */
        HAL_LCD_Set_Courser(1,0);
        HAL_LCD_Send_String("(Enter Password)");
        Input_Flag=HAL_Keypad_Get_Key();
        /*If Any Key Pessed*/
        if(Input_Flag!=Keypad_Not_Pressed)Admin_Panel(Input_Flag);
    }   
}
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
void Admin_Panel(u8 Input_Key)
{
    /* Check if the entered password is correct */
    if(Password_Check(Input_Key))
    {
        /* Clear the LCD and prompt the admin to enter an ID */
        HAL_LCD_Clear();
        HAL_LCD_Set_Courser(2,0);
        HAL_LCD_Send_String("-Enter ID : ");
        /* Wait for the admin to enter an ID */
        Input_Key = HAL_Keypad_Wait_For_Input();
        /* Display the entered ID on the LCD */
        HAL_LCD_Send_Data(Input_Key);
        /* Move the cursor to the next line and save the entered ID in the DataBase */
        HAL_LCD_Set_Courser(3,0);
        DataBase[DataBase_Index++].Valid_ID = Input_Key;
        /* Display a success message on the LCD */
        HAL_LCD_Send_String("Done  ");
        /* Clear the LCD to get ready for the next input or operation */
        HAL_LCD_Clear();
    }
    else
    {
        /* If the entered password is incorrect, display an error message on the LCD */
        HAL_LCD_Clear();
        HAL_LCD_Set_Courser(2,0);
        HAL_LCD_Send_String("---xxxxxxxxxx---");
    }
}
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
u8 Password_Check(u8 First_Char)
{
    /*Check For Password*/
    u8 Password_Flag=ZERO;
    HAL_LCD_Set_Courser(3,6);
    HAL_LCD_Send_Data('*');
    if(First_Char==Admin_Passowrd[0])Password_Flag++;
    for(u8 Counter=ONE;Counter<FOUR;Counter++)
    {
        First_Char=HAL_Keypad_Wait_For_Input();HAL_LCD_Send_Data('*');
        if(Admin_Passowrd[Counter]==First_Char)Password_Flag++;
    }
    return Password_Flag==4?TRUE:FALSE;
}
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
void EXTI_Entrance_ISR(void)
{
    HAL_LCD_Clear();
    u16 Data='X';
    /*Enable Slave*/
    MCAL_GPIO_Write_Pin(SS_Port,Entrance_SS,LOW);
    /*Read Data*/
    SPI_Send_Receive_Data(&SPI,&Data);
    /*Inform Admin*/
    HAL_LCD_Clear();
    HAL_LCD_Send_String("----ENTRANCE----");
    HAL_LCD_Set_Courser(1,0);
    HAL_LCD_Send_String("Client ID : ");
    HAL_LCD_Send_Data(Data);
    /*Check Data*/
    u16 ID_Found_Flag='0',Counter;
    for(Counter=ZERO;Counter<DataBase_Index;Counter++)
    {
        if(DataBase[Counter].Valid_ID==Data)
        {
            Garage_Clients++;
            ID_Found_Flag=Garage_Clients<3?'1':'2';
            break;
        }
    }
    /*Inform Admin With State*/
    HAL_LCD_Set_Courser(3,0);
    HAL_LCD_Send_String(ID_Found_Flag=='1'?"Valid":"Not Valid !");
    /*Send Result*/
    SPI_Send_Receive_Data(&SPI,&ID_Found_Flag);
    /*Disable Slave*/
    MCAL_GPIO_Write_Pin(SS_Port,Entrance_SS,HI);
    /*Clear Screen*/
    HAL_LCD_Clear();
    HAL_LCD_Set_Courser(1,0);
}
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
void EXTI_Exit_ISR(void)
{
    HAL_LCD_Clear();
    u16 Data='X',ID_Found_Flag='0';
    /*Enable Slave*/
    MCAL_GPIO_Write_Pin(SS_Port,Exit_SS,LOW);
    /*Read Data*/
    SPI_Send_Receive_Data(&SPI,&Data);
    /*Inform Admin*/
    HAL_LCD_Clear();
    HAL_LCD_Send_String("------EXIT------");
    HAL_LCD_Set_Courser(1,0);
    HAL_LCD_Send_String("Client ID : ");
    HAL_LCD_Send_Data(Data);
    /*Check Data*/
    for(u8 Counter=ZERO;Counter<DataBase_Index;Counter++)
    {
        if(DataBase[Counter].Valid_ID==Data)
        {
            if(Garage_Clients>ZERO&&Garage_Clients<FOUR){ID_Found_Flag='1';Garage_Clients--;}
            else ID_Found_Flag='2';
            break;
        }
    }
    /*Inform Admin With State*/
    HAL_LCD_Set_Courser(3,0);
    HAL_LCD_Send_String(ID_Found_Flag=='1'?"Valid":(ID_Found_Flag=='2')?"Empty Garage":"Not Valid !");
    /*Send Result*/
    SPI_Send_Receive_Data(&SPI,&ID_Found_Flag);
    /*Disable Slave*/
    MCAL_GPIO_Write_Pin(SS_Port,Exit_SS,HI);
    /*Clear Screen*/
    HAL_LCD_Clear();
    HAL_LCD_Set_Courser(1,0);
}
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
void Application_VidSystem_Initialization(void)
{
    /*Initialize Keypad*/
    HAL_Keypad_Initialization();
    /*Initialize LCD*/
    HAL_LCD_Initialization();
    /*Initialize SS_Entrance*/
    MCAL_GPIO_Initialize(SS_Port,A0);
    MCAL_GPIO_Write_Pin(SS_Port,Entrance_SS,HI);
    /*Initialize SS_Exit*/
    MCAL_GPIO_Initialize(SS_Port,A1);
    MCAL_GPIO_Write_Pin(SS_Port,Exit_SS,HI);
    /*Initialize SPI*/
    SPI_Initialization(&SPI);
    /*Initialize External Interrupt*/
    EXTI_Initilization(EXTI_Entrance);
    EXTI_Initilization(EXTI_Exit);
    /*Initialize 7-Segment*/
    Seven_Segment_Initialization(&Segment);
}
/********************************************************************
 *  END OF FILE:  Application.c
********************************************************************/
