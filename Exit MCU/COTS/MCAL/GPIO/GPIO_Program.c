/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  GPIO_Program.c
 *  Module:  MCAL/GPIO
 *  Description:  General Input Output Driver Program File For ATMEGA32
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "GPIO_Interface.h"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
/********************************************************************
* Syntax          : GPIO_VidSet_Pin_Direction(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
* Description     : Set the direction (input or output) for a specific GPIO pin.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier "Port_A, Port_B, Port_C, Port_D")
*                   Copy_u8Pin (Pin number)
*                   Copy_u8Direction (Direction "INPUT or OUTPUT")
* Parameters (out): None
* Return value    : Void
********************************************************************/	
void GPIO_VidSet_Pin_Direction(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Direction)
{
	if(Copy_u8Direction==INPUT)
	{
		switch(Copy_u8Port)
		{
			case(Port_A):Clear_Bit(DDRA,Copy_u8Pin);break;
			case(Port_B):Clear_Bit(DDRB,Copy_u8Pin);break;
			case(Port_C):Clear_Bit(DDRC,Copy_u8Pin);break;
			case(Port_D):Clear_Bit(DDRD,Copy_u8Pin);break;
		}
	}
	else if(Copy_u8Direction==OUTPUT)
	{
		switch(Copy_u8Port)
		{
			case(Port_A):Set_Bit(DDRA,Copy_u8Pin);break;
			case(Port_B):Set_Bit(DDRB,Copy_u8Pin);break;
			case(Port_C):Set_Bit(DDRC,Copy_u8Pin);break;
			case(Port_D):Set_Bit(DDRD,Copy_u8Pin);break;
		}
	}
}
/********************************************************************
* Syntax          : GPIO_VidInternal_Pin_Bull_Up(u8 Copy_u8Port, u8 Copy_u8Pin)
* Description     : Set the internal pull-up for a specific GPIO pin.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Pin (Pin number)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidInternal_Pin_Bull_Up(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	switch(Copy_u8Port)//Set As Output
	{
		case(Port_A):Set_Bit(DDRA,Copy_u8Pin);break;
		case(Port_B):Set_Bit(DDRB,Copy_u8Pin);break;
		case(Port_C):Set_Bit(DDRC,Copy_u8Pin);break;
		case(Port_D):Set_Bit(DDRD,Copy_u8Pin);break;
	}
	switch(Copy_u8Port)//Activate Internal Bull Up
	{
		case(Port_A):Set_Bit(PORTA,Copy_u8Pin);break;
		case(Port_B):Set_Bit(PORTB,Copy_u8Pin);break;
		case(Port_C):Set_Bit(PORTC,Copy_u8Pin);break;
		case(Port_D):Set_Bit(PORTD,Copy_u8Pin);break;
	}
}
/********************************************************************
* Syntax          : GPIO_VidSet_Pin_Value(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
* Description     : Set the value (HIGH or LOW) for a specific GPIO pin.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Pin (Pin number), Copy_u8Value (Value to be set: HIGH/LOW)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidSet_Pin_Value(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value)
{
	if(Copy_u8Value==HI)
	{
		switch(Copy_u8Port)
		{
			case(Port_A):Set_Bit(PORTA,Copy_u8Pin);break;
			case(Port_B):Set_Bit(PORTB,Copy_u8Pin);break;
			case(Port_C):Set_Bit(PORTC,Copy_u8Pin);break;
			case(Port_D):Set_Bit(PORTD,Copy_u8Pin);break;
		}
	}
	else if(Copy_u8Value==LOW)
	{
		switch(Copy_u8Port)
		{
			case(Port_A):Clear_Bit(PORTA,Copy_u8Pin);break;
			case(Port_B):Clear_Bit(PORTB,Copy_u8Pin);break;
			case(Port_C):Clear_Bit(PORTC,Copy_u8Pin);break;
			case(Port_D):Clear_Bit(PORTD,Copy_u8Pin);break;
		}
	}
}
/********************************************************************
* Syntax          : GPIO_VidToggle_Pin_Value(u8 Copy_u8Port, u8 Copy_u8Pin)
* Description     : Toggle the value (HIGH to LOW or vice-versa) for a specific GPIO pin.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Pin (Pin number)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidToggle_Pin_Value(u8 Copy_u8Port,u8 Copy_u8Pin)	
{
	switch(Copy_u8Port)
	{
		case(Port_A):Toggle_Bit(PORTA,Copy_u8Pin);break;
		case(Port_B):Toggle_Bit(PORTB,Copy_u8Pin);break;
		case(Port_C):Toggle_Bit(PORTC,Copy_u8Pin);break;
		case(Port_D):Toggle_Bit(PORTD,Copy_u8Pin);break;
	}
}
/********************************************************************
* Syntax          : GPIO_VidGet_Pin_Value(u8 Copy_u8Port, u8 Copy_u8Pin, u8 *Copy_Pu8Pin_Value)
* Description     : Retrieve the value (HIGH or LOW) of a specific GPIO pin.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Pin (Pin number)
* Parameters (out): Copy_Pu8Pin_Value (Pointer to store the retrieved pin value)
* Return value    : Void
********************************************************************/
void GPIO_VidGet_Pin_Value(u8 Copy_u8Port,u8 Copy_u8Pin,u8 *Copy_Pu8Pin_Value)
{
	switch(Copy_u8Port)
	{
		case(Port_A):*Copy_Pu8Pin_Value = Get_Bit(PINA,Copy_u8Pin);break;
		case(Port_B):*Copy_Pu8Pin_Value = Get_Bit(PINB,Copy_u8Pin);break;
		case(Port_C):*Copy_Pu8Pin_Value = Get_Bit(PINC,Copy_u8Pin);break;
		case(Port_D):*Copy_Pu8Pin_Value = Get_Bit(PIND,Copy_u8Pin);break;
	}
}
/********************************************************************
* Syntax          : GPIO_VidSet_Whole_Port_Direction(u8 Copy_u8Port, u8 Copy_u8Direction)
* Description     : Set the direction (INPUT or OUTPUT) for an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Direction (Direction to be set: INPUT/OUTPUT)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidSet_Whole_Port_Direction(u8 Copy_u8Port,u8 Copy_u8Direction)
{
	if(Copy_u8Direction==INPUT)
	{
		switch(Copy_u8Port)
		{
			case(Port_A):DDRA&=0x00;break;
			case(Port_B):DDRB&=0x00;break;
			case(Port_C):DDRC&=0x00;break;
			case(Port_D):DDRD&=0x00;break;
		}
	}
	else if(Copy_u8Direction==OUTPUT)
	{
		switch(Copy_u8Port)
		{
			case(Port_A):DDRA|=0xff;break;
			case(Port_B):DDRB|=0xff;break;
			case(Port_C):DDRC|=0xff;break;
			case(Port_D):DDRD|=0xff;break;
		}
	}
}
/********************************************************************
* Syntax          : GPIO_VidSet_Port_Direction(u8 Copy_u8Port, u8 Copy_u8Value)
* Description     : Set the direction value for an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Value (Value to be set for the direction of the entire port)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidSet_Port_Direction(u8 Copy_u8Port,u8 Copy_u8Value)
{
	switch(Copy_u8Port)
	{
		case(Port_A):DDRA=Copy_u8Value;break;
		case(Port_B):DDRB=Copy_u8Value;break;
		case(Port_C):DDRC=Copy_u8Value;break;
		case(Port_D):DDRD=Copy_u8Value;break;
	}
}
/********************************************************************
* Syntax          : GPIO_VidInternal_Port_Bull_Up(u8 Copy_u8Port)
* Description     : Activate the internal pull-up for an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidInternal_Port_Bull_Up(u8 Copy_u8Port)
{
	switch(Copy_u8Port)
	{
		case(Port_A):DDRA|=0xff;break;
		case(Port_B):DDRB|=0xff;break;
		case(Port_C):DDRC|=0xff;break;
		case(Port_D):DDRD|=0xff;break;
	}
	switch(Copy_u8Port)
	{
		case(Port_A):PORTA=0xff;break;
		case(Port_B):PORTB=0xff;break;
		case(Port_C):PORTC=0xff;break;
		case(Port_D):PORTD=0xff;break;
	}
}
/********************************************************************
* Syntax          : GPIO_VidSet_Port_Value(u8 Copy_u8Port, u8 Copy_u8Value)
* Description     : Set the value for an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), Copy_u8Value (Value to be set for the entire port)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidSet_Port_Value(u8 Copy_u8Port,u8 Copy_u8Value)
{
		switch(Copy_u8Port)
		{
			case(Port_A):PORTA=Copy_u8Value;break;
			case(Port_B):PORTB=Copy_u8Value;break;
			case(Port_C):PORTC=Copy_u8Value;break;
			case(Port_D):PORTD=Copy_u8Value;break;
		}
}
/********************************************************************
* Syntax          : GPIO_VidEdit_Port_Value(u8 Copy_u8Port, u8 Copy_u8Pins, u8 Copy_u8Value)
* Description     : Edit specific segments (HIGH or LOW nibble) of the port's value without altering the other segment.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier), 
*                   Copy_u8Pins (Which segment to edit: HI/LOW nibble),
*                   Copy_u8Value (Value to be set for the selected segment)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidEdit_Port_Value(u8 Copy_u8Port,u8 Copy_u8Pins,u8 Copy_u8Value)
{
	if(Copy_u8Pins==HI)
	{
		switch(Copy_u8Port)
		{
			case(Port_A):PORTA&=0x0F;PORTA|=(Copy_u8Value&0xF0);break;
			case(Port_B):PORTB&=0x0F;PORTB|=(Copy_u8Value&0xF0);break;
			case(Port_C):PORTC&=0x0F;PORTC|=(Copy_u8Value&0xF0);break;
			case(Port_D):PORTD&=0x0F;PORTD|=(Copy_u8Value&0xF0);break;
		}
	}
	else if (Copy_u8Pins==LOW)
	{
		switch(Copy_u8Port)
		{
			case(Port_A):PORTA&=0xF0;PORTA|=Copy_u8Value&0X0F;break;
			case(Port_B):PORTB&=0xF0;PORTB|=Copy_u8Value&0X0F;break;
			case(Port_C):PORTC&=0xF0;PORTC|=Copy_u8Value&0X0F;break;
			case(Port_D):PORTD&=0xF0;PORTD|=Copy_u8Value&0X0F;break;
		}
	}
}
/********************************************************************
* Syntax          : GPIO_VidToggle_Port_Value(u8 Copy_u8Port)
* Description     : Toggle the values of an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier)
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidToggle_Port_Value(u8 Copy_u8Port)
{
	switch(Copy_u8Port)
	{
		case(Port_A):PORTA^=0xff;break;
		case(Port_B):PORTB^=0xff;break;
		case(Port_C):PORTC^=0xff;break;
		case(Port_D):PORTD^=0xff;break;
	}
}
/********************************************************************
* Syntax          : GPIO_VidGet_Port_Value(u8 Copy_u8Port, u8 *Copy_u8Port_Value)
* Description     : Retrieve the value of an entire GPIO port.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : Copy_u8Port (Port identifier)
* Parameters (out): Copy_u8Port_Value (Pointer to store the retrieved port value)
* Return value    : Void
********************************************************************/
void GPIO_VidGet_Port_Value(u8 Copy_u8Port,u8 *Copy_u8Port_Value)
{
	switch(Copy_u8Port)
	{
		case(Port_A):*Copy_u8Port_Value = PINA;break;
		case(Port_B):*Copy_u8Port_Value = PINB;break;
		case(Port_C):*Copy_u8Port_Value = PINC;break;
		case(Port_D):*Copy_u8Port_Value = PIND;break;
	}
}
/********************************************************************
* Syntax          : GPIO_VidGlobal_Interrupt_Enable(void)
* Description     : Enable the global interrupts.
* Sync-Async      : *
* Reentrancy      : *
* Parameters (in) : None
* Parameters (out): None
* Return value    : Void
********************************************************************/
void GPIO_VidGlobal_Interrupt_Enable(void)
{
	Set_Bit(SREG,SREG_I);
}
/********************************************************************
 *  END OF FILE:  GPIO_Program.c
********************************************************************/