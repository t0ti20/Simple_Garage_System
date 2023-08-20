/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  LCD_Interface.h
 *  Module:  HAL->LCD
 *  Description:  LCD 16*2 Character Driver
*******************************************************************/
#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_
/*---------- Include Files -------------*/
#include "Macros.h"
#include "LCD_Config.h"
#include "LCD_Private.h"
#include "GPIO_Interface.h"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
void LCD_VidInitialization(void);																										/*Initialize LCD Basic Setting*/
void LCD_VidSend_Command(u8 Copy_u8Command);																							/*SEND COMMAND FOR LCD*/
void LCD_VidSend_Data(u8 Copy_u8Data);																									/*SEND DATA FOR LCD*/
void LCD_VidSet_Position(u8 Copy_u8y_location,u8 Copy_u8x_location);																	/*GO TO EXACT POSITION*/
void LCD_VidSend_String(u8 const *Copy_u8String);																						/*String Display*/
void LCD_VidSend_Special_Character(u8 *Copy_u8Pattern,u8 Copy_u8Pattern_Location,u8 Copy_u8x_location,u8 Copy_u8y_location); 			/*Configure Special Character*/
void LCD_VidClear(void);
#endif
/********************************************************************
 *  END OF FILE: LCD_Interface.h
********************************************************************/
