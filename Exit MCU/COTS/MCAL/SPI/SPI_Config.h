/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  SPI_Config.h
 *  Module:  MCAL/SPI
 *  Description:  Serial Peripheral Interface Config File
*******************************************************************/
#ifndef _SPI_CONFIG_H_
#define _SPI_CONFIG_H_
/*****************************************
--Application PreProcessor Configuration--
*****************************************/
/* Pre_Scalar_2(4,8,16,32,64,128) */
#define Clock_Rate			          (Pre_Scalar_16)		 
/* MSBF - LSBF */
#define Data_Order			          (MSBF)
/* Idle_Low - Idle_Hi */
#define SPI_Clock_Polarity              (Idle_Hi)		 
/* Second_Edge - First_Edge */
#define Clock_Phase		               (Second_Edge)		 
/* MOSI HW PIN */
#define MOSI_Pin			          (Pin_5)
/* MISO HW PIN */
#define MISO_Pin			          (Pin_6) 
/* SPI Clock Pin */
#define SPI_SCK			          (Pin_7)
/* MISO MISO Port */
#define Data_Port			          (Port_B)
#endif
/********************************************************************
 *  END OF FILE:  USART_Config.h
********************************************************************/

