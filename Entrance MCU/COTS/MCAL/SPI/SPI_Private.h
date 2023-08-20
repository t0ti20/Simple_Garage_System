/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  SPI_Private.h
 *  Module:  MCAL/SPI
 *  Description:  Serial Peripheral Interface Private File
*******************************************************************/
#ifndef _SPI_PRIVATE_H_
#define _SPI_PRIVATE_H_
/********************************************************************/
/*****************************************
--------    Type  Definitions    ---------
*****************************************/
typedef enum SPI_Mode_t
{
     SPI_Master                         =(0),
     SPI_Slave                          =(1),
     SPI_Interrupt_Enable               =(2),
     SPI_Interrupt_Disable              =(3)
}SPI_Mode_t;
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
/*------------- Registers --------------*/
/* Control Register */
#define SPCR                            (*((volatile u8*)0x2D))
/* Status Register */
#define SPSR                            (*((volatile u8*)0x2E))
/* SPI Data */
#define SPDR                            (*((volatile u8*)0x2F))
/*------------- SPCR_Bits --------------*/  
#define SPCR_SPIE                       (7)  /* SPI Interrupt Enable */
#define SPCR_SPE                        (6)  /* SPI Enable */
#define SPCR_DORD                       (5)  /* Data Order (0-Lift)(1-LSBF) */
#define SPCR_MSTR                       (4)  /* Master/Slave Select (0-Slave)(1-Master) */
#define SPCR_CPOL                       (3)  /* Clock Polarity (0-Rising)(1-Falling) */
#define SPCR_CPHA                       (2)  /* Clock Phase (Sample-0)(Setup-1)*/
#define SPCR_SPR1                       (1)  /* Clock Rate Select */
#define SPCR_SPR0                       (0)  /* Clock Rate Select */
/*------------- SPSR_Bits --------------*/  
#define SPSR_SPIF                       (7)  /* SPI Interrupt Flag */
#define SPSR_WCOL                       (6)  /* Write Collision Flag */
#define SPSR_SPI2X                      (0)  /* Double SPI Speed Bit */
/*****************************************
---------    Configure Macros    ---------
*****************************************/
#define Pre_Scalar_2				(2)
#define Pre_Scalar_4				(4)
#define Pre_Scalar_8				(8)
#define LSBF				          (9)
#define Idle_Low	                    (8)
#define Idle_Hi	                    (7)
#define Second_Edge		               (6)
#define First_Edge	                    (5)
#define Pre_Scalar_16				(16)
#define Pre_Scalar_32				(32)
#define Pre_Scalar_64				(64)
#define MSBF				          (10)
#endif 
/********************************************************************
 *  END OF FILE:  SPI_Private.h
 ********************************************************************/