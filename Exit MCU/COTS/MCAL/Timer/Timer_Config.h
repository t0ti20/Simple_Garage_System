/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  Timer_Config.h
 *  Module:  MCAL/Timer
 *  Description:  Timer Module Configuration File
*******************************************************************/
#ifndef _TIMER_CONFIG_H_
#define _TIMER_CONFIG_H_
/*****************************************
--Application PreProcessor Configuration--
*****************************************/
/* Inverting (COCSOB) - Nun_Inverting (COBSOC) */
#define		PWM_Mode		COCSOB
/* CPU Frequency */
#define		CPU_Freq		8000000
/*WDT_16K - WDT_32K - WDT_64K - WDT_128K - WDT_256K - WDT_2048K */
#define		WDT_Cycles     WDT_2048K
#endif
/********************************************************************
 *  END OF FILE:  Timer_Config.h
********************************************************************/
