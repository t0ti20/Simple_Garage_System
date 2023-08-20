/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  SPI_Program.c
 *  Module:  MCAL/SPI
 *  Description:  Serial Peripheral Interface Program File
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "SPI_Interface.h"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
static void (*SPI_Inturrept_Function)(void)=NULL;
/********************************************************************
* Syntax          : void SPI_VidInitialization(u8 Copy_u8Master_Slave,u8 Copy_u8Interrupt)
* Description     : Initializes the SPI (Serial Peripheral Interface) module.
				This function allows the user to set the device as a master or slave
				Enable or disable interrupts, and configure the other necessary SPI settings.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : Copy_u8Master_Slave (Master or Slave mode selector), 
*                   Copy_u8Interrupt (Interrupt enable or disable flag)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void SPI_VidInitialization(u8 Copy_u8Master_Slave,u8 Copy_u8Interrupt)
{
	/* Master Slave Select */
	switch(Copy_u8Master_Slave)
	{
		case(SPI_Master):
			GPIO_VidSet_Pin_Direction(Data_Port,MOSI_Pin,OUTPUT);
			GPIO_VidSet_Pin_Direction(Data_Port,MISO_Pin,INPUT);
			GPIO_VidSet_Pin_Direction(Data_Port,SPI_SCK,OUTPUT);
			Set_Bit(SPCR,SPCR_MSTR);break;
		case(SPI_Slave):
			GPIO_VidSet_Pin_Direction(Data_Port,MOSI_Pin,INPUT);
			GPIO_VidSet_Pin_Direction(Data_Port,MISO_Pin,OUTPUT);
			GPIO_VidSet_Pin_Direction(Data_Port,SPI_SCK,INPUT);
			Clear_Bit(SPCR,SPCR_MSTR);break;
	}
	/* Interrupt Setup */
	if(Copy_u8Interrupt==SPI_Interrupt_Enable)Set_Bit(SPCR,SPCR_SPIE);
	else Clear_Bit(SPCR,SPCR_SPIE);
	/* Data Order */
#if Data_Order == MSBF
	Clear_Bit(SPCR,SPCR_DORD);
#elif Data_Order == LSBF
	Set_Bit(SPCR,SPCR_DORD);
#else
#warning (" Wrong Configuration !!")
#endif
	/* Clock Polarity */
#if SPI_Clock_Polarity == Idle_Low
	Clear_Bit(SPCR,SPCR_CPOL);
#elif SPI_Clock_Polarity == Idle_Hi
	Set_Bit(SPCR,SPCR_CPOL);
#else
#warning (" Wrong Configuration !!")
#endif
	/* Clock Phase */
#if Clock_Phase == First_Edge
	Clear_Bit(SPCR,SPCR_CPHA);
#elif Clock_Phase == Second_Edge
	Set_Bit(SPCR,SPCR_CPHA);
#else
#warning (" Wrong Configuration !!")
#endif
#if (Clock_Rate == Pre_Scalar_2)
	Clear_Bit(SPCR,SPCR_SPR0);
	Clear_Bit(SPCR,SPCR_SPR1);
	Set_Bit(SPSR,SPSR_SPI2X);
#elif(Clock_Rate == Pre_Scalar_4)
	Clear_Bit(SPCR,SPCR_SPR0);
	Clear_Bit(SPCR,SPCR_SPR1);
	Clear_Bit(SPSR,SPSR_SPI2X);
#elif(Clock_Rate == Pre_Scalar_8)
	Set_Bit(SPCR,SPCR_SPR0);
	Clear_Bit(SPCR,SPCR_SPR1);
	Set_Bit(SPSR,SPSR_SPI2X);
#elif(Clock_Rate == Pre_Scalar_16)
	Set_Bit(SPCR,SPCR_SPR0);
	Clear_Bit(SPCR,SPCR_SPR1);
	Clear_Bit(SPSR,SPSR_SPI2X);
#elif(Clock_Rate == Pre_Scalar_32)
	Clear_Bit(SPCR,SPCR_SPR0);
	Set_Bit(SPCR,SPCR_SPR1);
	Set_Bit(SPSR,SPSR_SPI2X);
#elif(Clock_Rate == Pre_Scalar_64)
	Clear_Bit(SPCR,SPCR_SPR1);
	Set_Bit(SPCR,SPCR_SPR0);
	Clear_Bit(SPSR,SPSR_SPI2X);
#elif(Clock_Rate == Pre_Scalar_128)
	Set_Bit(SPCR,SPCR_SPR1);
	Set_Bit(SPCR,SPCR_SPR0);
	Clear_Bit(SPSR,SPSR_SPI2X);
#else
	#warning (" Wrong Configuration !!")
#endif
	/* SPI Enable */
	Set_Bit(SPCR,SPCR_SPE);
}
/********************************************************************
* Syntax          : void SPI_VidSend_Receive(u8 Copy_u8Mode,u8 *Copy_u8Data)
* Description     : Sends or receives data using the SPI (Serial Peripheral Interface) module.
				The function allows for sending data, receiving data, or flushing the SPI buffer.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant
* Parameters (in) : Copy_u8Mode (Mode selector, either to send or receive), 
*                   Copy_u8Data (Pointer to the data byte to send or store received data)
* Parameters (out): Copy_u8Data (Pointer updates with received data if in Receive mode)
* Return value    : Void
********************************************************************/
void SPI_VidSend_Receive(u8 *Copy_u8Data)
{
	SPDR=*Copy_u8Data;
	while(!Get_Bit(SPSR,SPSR_SPIF));
	(*Copy_u8Data)=SPDR;
}
/********************************************************************
* Syntax          : void SPI_VidInturrept(void(*Copy_VidInturrept)(void))
* Description     : Sets the callback function for the SPI interrupt. 
*                   The provided function will be executed when the SPI interrupt occurs.
* Sync-Async      : Synchronous
* Reentrancy      : Non-Reentrant (due to shared resources)
* Parameters (in) : Copy_VidInturrept (Pointer to the callback function to be set for the SPI interrupt)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void SPI_VidInturrept(void(*Copy_VidInturrept)(void))
{
	if(Copy_VidInturrept!=NULL)
	{
		SPI_Inturrept_Function = Copy_VidInturrept;
	}
}
void __vector_12(void) __attribute__((signal));
void __vector_12(void)
{
	if(SPI_Inturrept_Function!=NULL)
	{
		SPI_Inturrept_Function();
	}
}
/********************************************************************
 *  END OF FILE:  SPI_Program.c
 ********************************************************************/