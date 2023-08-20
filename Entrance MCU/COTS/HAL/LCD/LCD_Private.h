/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  LCD_Private.h
 *  Module:  HAL/LCD
 *  Description:  LCD Charachter Driver Private File
*******************************************************************/
#ifndef _LCD_PRIVATE_H_
#define _LCD_PRIVATE_H_
/*****************************************
-------   Configuration Macros   ---------
*****************************************/
#define Mode_4       	          (2)
#define Mode_8       	          (1)
#define Clear_Screen               (0x01)
#define LCD_FIRST_LINE			(0x80)
#define LCD_SECOND_LINE	          (0xC0)
#define LCD_THIRD_LINE	          (0x90)
#define LCD_FOURTH_LINE	          (0xD0)
#define Heart		 	          {0,10,31,31,14,4,0,0}
#define Bell		 	          {4,14,14,14,31,0,4,0}
#define Alien		 	          {31,21,31,31,14,10,27,0}
#define Check		 	          {0,1,3,22,28,8,0,0}
#define Skull		 	          {0,14,21,27,14,14,0,0}
#define Lock		 	          {14,17,17,31,27,27,31,0}
#define Speaker		          {1,3,15,15,15,3,1,0}
#endif
/********************************************************************
 *  END OF FILE: LCD_Private.h
********************************************************************/
