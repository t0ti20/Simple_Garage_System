/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  UART_Program.c
 *  Module:  MCAL/USART
 *  Description:  Universal Asynchronous Receive Transmit Driver Program File For ATmega32
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "UART_Interface.h"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
static u8 *Global_Buffer=NULL;
static void(*UART_VidCallBack_Global)(u8 *Received_Data)=NULL;
/********************************************************************
* Syntax          : UART_VidInitialization(u8 Copy_u8Mode, u8 Copy_u8Rx_Interrupt, u8 Copy_u8Tx_Interrupt)
* Description     : Initialize the UART module with specific configurations for mode, Rx interrupt, and Tx interrupt.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Mode (UART mode: Transmit, Receive or both),
*                   Copy_u8Rx_Interrupt (Enable or disable Rx interrupt),
*                   Copy_u8Tx_Interrupt (Enable or disable Tx interrupt)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void UART_VidInitialization (u8 Copy_u8Mode,u8 Copy_u8Rx_Interrupt,u8 Copy_u8Tx_Interrupt)
{
/*----------------------- Select Baud Rate & Speed -----------------------*/
#if (Baud_Rate == S_9600) && (Speed == Normal_Speed)
	UBRRL= 51;
	Clear_Bit(UCSRA,UCSRA_U2X);
#else
#warning (" Wrong Configuration !!")
#endif
/*----------------------- Trans-Rec -----------------------*/
	switch(Copy_u8Mode)
	{
		case(Transmit_Recive):Set_Bit(UCSRB,UCSRB_RXEN);Set_Bit(UCSRB,UCSRB_TXEN);break;
		case(Transmit):Clear_Bit(UCSRB,UCSRB_RXEN);Set_Bit(UCSRB,UCSRB_TXEN);break;
		case(Recive):Set_Bit(UCSRB,UCSRB_RXEN);Clear_Bit(UCSRB,UCSRB_TXEN);break;
		default:Clear_Bit(UCSRB,UCSRB_RXEN);Clear_Bit(UCSRB,UCSRB_TXEN);break;
	}
/*----------------------- Enable Interrupts -----------------------*/
	/*(Rx)Interrupt*/
	switch(Copy_u8Rx_Interrupt)
	{
		case (Rx_Enable):Set_Bit(UCSRB,UCSRB_RXCIE);Set_Bit(SREG,SREG_I);break;
		case (Rx_Disable):Clear_Bit(UCSRB,UCSRB_RXCIE);break;
		default:Clear_Bit(UCSRB,UCSRB_RXCIE);break;
	}
	/*(Tx)Interrupt*/
	switch(Copy_u8Tx_Interrupt)
	{
		case (Tx_Enable):Set_Bit(UCSRB,UCSRB_TXCIE);Set_Bit(SREG,SREG_I);break;
		case (Tx_Disable):Clear_Bit(UCSRB,UCSRB_TXCIE);break;
		default:Clear_Bit(UCSRB,UCSRB_TXCIE);break;
	}
/*----------------------- Frame Formate -----------------------*/
	/*Parity Mode*/
	Set_Bit(UBRRH,UBRRH_URSEL);
#if	Parity_Mode == Even
	Set_Bit(UCSRC,UCSRC_UPM1);
	Clear_Bit(UCSRC,UCSRC_UPM0);
#elif Parity_Mode == Odd
	Set_Bit(UCSRC,UCSRC_UPM1);
	Set_Bit(UCSRC,UCSRC_UPM0);
#elif Parity_Mode == Disabled
	Clear_Bit(UCSRC,UCSRC_UPM1);
	Clear_Bit(UCSRC,UCSRC_UPM0);
#else
#warning (" Wrong Configuration !!")
#endif
	/*Character Size*/
#if	Character_Size == _8_Bits
	Clear_Bit(UCSRB,UCSRB_UCSZ2);
	Set_Bit(UCSRC,UCSRC_UCSZ1);
	Set_Bit(UCSRC,UCSRC_UCSZ0);
#else
#warning (" Wrong Configuration !!")
#endif
	/*Stop Bits*/
#if	Stop_Bits == Two_StopBits
	Set_Bit(UCSRC,UCSRC_USBS);
#elif Stop_Bits == One_StopBit
	Clear_Bit(UCSRC,UCSRC_USBS);
#else
#warning (" Wrong Configuration !!")
#endif
	/*Clock Polarity*/
#if	Clock_Polarity == Tx_Rising
	Clear_Bit(UCSRC,UCSRC_UCPOL);
#elif Clock_Polarity == Tx_Falling
	Set_Bit(UCSRC,UCSRC_UCPOL);
#else
#warning (" Wrong Configuration !!")
#endif
}
/********************************************************************
* Syntax          : UART_VidSend_Receive(u8 Copy_u8Mode, u8 *Copy_u8Data)
* Description     : Based on the provided mode, either sends data using UART or receives data through UART.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Mode (UART mode: Send or Receive),
*                   Copy_u8Data (Pointer to the data to send or to store received data)
* Parameters (out): None for Send mode. For Receive mode, data is stored in the address pointed by Copy_u8Data.
* Return value    : Void
********************************************************************/
void UART_VidSend_Receive (u8 Copy_u8Mode,u8 *Copy_u8Data)
{
	if(Copy_u8Mode==Receive)
	{
		/* Wait for empty transmit buffer */
		while(!Get_Bit(UCSRA,UCSRA_RXC));
		/*Write Data Into Data Register*/
		*Copy_u8Data=UDR;
	}
	else if(Copy_u8Mode==Send)
	{
		/* Wait for empty transmit buffer */
		while(!Get_Bit(UCSRA,UCSRA_UDRE));
		/*Write Data Into Data Register*/
		UDR=*Copy_u8Data;
	}
}
/********************************************************************
* Syntax          : UART_VidSend_String(u8 *Copy_u8Data)
* Description     : Sends a null-terminated string using UART, followed by a carriage return.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Data (Pointer to the null-terminated string to be sent)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void UART_VidSend_String (u8 *Copy_u8Data)
{
	do 
	{
		UART_VidSend_Receive(Send,(u8 *)Copy_u8Data++);
	}while(Copy_u8Data[0]);
}
/********************************************************************
* Syntax          : static void UART_VidReceive_String_Local(u8 *Copy_u8Data)
* Description     : Receives data through UART and stores it into a global buffer until a termination character is received. Once the termination character is received, the data in the buffer is sent back through UART and the buffer is reset.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Data (Pointer to the received data)
* Parameters (out): None
* Return value    : Void
********************************************************************/
static void UART_VidReceive_String_Local(u8 *Copy_u8Data)
{
	static u8 Counter=ZERO;
	if(*Copy_u8Data==End_String)
	{
		Global_Buffer[Counter]=ZERO;
		Counter=ZERO;UART_VidSend_String(Global_Buffer);
	}
	else
	{
		Global_Buffer[Counter]=*Copy_u8Data;Counter++;
	}
}
/********************************************************************
* Syntax          : void UART_VidReceive_String(u8 *Copy_u8Data)
* Description     : Receives a string through UART until a termination character is encountered. 
				If the UART interrupt is enabled, the function uses interrupt-driven reception.
				Otherwise, it uses polling.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : None
* Parameters (out): Copy_u8Data (Pointer to store the received null-terminated string)
* Return value    : Void
********************************************************************/
void UART_VidReceive_String (u8 *Copy_u8Data)
{
	/*If Interrupt Enable Use It With Interrupt*/
	if(Get_Bit(UCSRB,UCSRB_RXCIE))
	{
		UART_VidReceive_Function(UART_VidReceive_String_Local);
		Global_Buffer=Copy_u8Data;
	}
	/*If Interrupt Disable Use Polling*/
	else
	{
		do
		{
			UART_VidSend_Receive(Receive,(u8 *)Copy_u8Data++);
		}while(*(Copy_u8Data-1)!=End_String);
		*(Copy_u8Data-1)=ZERO;
	}
}
/********************************************************************
* Syntax          : void UART_VidReceive_Function(void(*UART_VidCallBack)(u8 *Received_Data))
* Description     : Sets the callback function that will be executed upon UART data reception via an interrupt.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : UART_VidCallBack (Pointer to callback function)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void UART_VidReceive_Function(void(*UART_VidCallBack)(u8 *Received_Data))
{
	UART_VidCallBack_Global=UART_VidCallBack;
}
void __vector_13(void) __attribute__((signal, used));
void __vector_13(void)
{
	/*Prepare Receving Buffer*/
	u8 Received_Data;
	Received_Data=UDR;
	/*Check For Null Pionter*/
	if(UART_VidCallBack_Global)UART_VidCallBack_Global(&Received_Data);
}
/********************************************************************
 *  END OF FILE:  USART_Program.c
********************************************************************/
