/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  GPIO_Private.h
 *  Module:  MCAL/GPIO
 *  Description:  General Input Output Driver Private File For ATMEGA32
*******************************************************************/
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_
/*****************************************
--------    Type  Definitions    ---------
*****************************************/
/*----------- GPIO Variables -----------*/
typedef enum Constants_GPIO_Variables_t
{
     INPUT          =(0),
     OUTPUT         =(1),
     Port_A         =(0),
     Port_B         =(1),
     Port_C         =(2),
     Port_D         =(3),
     LOW            =(0),
     HI             =(1),
     Pin_0          =(0),
     Pin_1          =(1),
     Pin_2          =(2),
     Pin_3          =(3),
     Pin_4          =(4),
     Pin_5          =(5),
     Pin_6          =(6),
     Pin_7          =(7)
}Constants_GPIO_Variables_t;
/*****************************************
-----------   Global Macros    -----------
*****************************************/
/*-------------  FOR PORT A  -------------*/
#define PORTA                (*((volatile u8*)0X3B))
#define DDRA                 (*((volatile u8*)0X3A))
#define PINA                 (*((volatile u8*)0X39))
/*-------------  FOR PORT B  -------------*/
#define PORTB                (*((volatile u8*)0X38))
#define DDRB                 (*((volatile u8*)0X37))
#define PINB                 (*((volatile u8*)0X36))
/*-------------  FOR PORT C  -------------*/
#define PORTC                (*((volatile u8*)0X35))
#define DDRC                 (*((volatile u8*)0X34))
#define PINC                 (*((volatile u8*)0X33))
/*-------------  FOR PORT D  -------------*/
#define PORTD                (*((volatile u8*)0X32))
#define DDRD                 (*((volatile u8*)0X31))
#define PIND                 (*((volatile u8*)0X30))
/*----------------  Global ---------------*/
#ifndef SREG
#define SREG                 (*((volatile u8*)0x5F))
#define SREG_I               (7)
#endif
#endif
/********************************************************************
 *  END OF FILE:  GPIO_Private.h
********************************************************************/