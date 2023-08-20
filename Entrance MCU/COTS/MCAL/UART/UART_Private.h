/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Owner:  Khaled El-Sayed @t0ti20
 *  File:  USART_Private.h
 *  Module:  MCAL/USART
 *  Description:  Universal Synchronous Asynchronous Receive Transmit Driver Private File
*******************************************************************/
#ifndef _UART_PRIVATE_H_
#define _UART_PRIVATE_H_
/*****************************************
--------    Type  Definitions    ---------
*****************************************/
/*------------- USART Mode -------------*/
typedef enum UART_Mode_t
{
     Transmit_Recive               =(0),
     Transmit                      =(1),
     Recive                        =(2),
     Stop                          =(3),
     Tx_Enable                     =(4),
     Tx_Disable                    =(5),
     Rx_Enable                     =(6),
     Rx_Disable                    =(7)
}UART_Mode_t;
/*---------- USART BaudRate -----------*/
typedef enum UART_BaudRate_t
{
     S_9600                        =(0),
}UART_BaudRate_t;
/*-------- USART Configuration --------*/
typedef enum UART_Configure_t 
{
     Normal_Speed                  =(0),
     Double_Speed                  =(1),
     Send                          =(2),
     Receive                       =(3)
}UART_Configure_t;
/*****************************************
---------    Configure Macros    ---------
*****************************************/
#define S_9600UBRR			     (0x33)
#define Even				     (0)
#define Odd					(1)
#define Disabled			     (2)
#define _8_Bits				(8)
#define One_StopBit			     (1)
#define Two_StopBits		     (1)
#define Tx_Rising			     (1)
#define Tx_Falling			     (1)
/*****************************************
-----------   Global Macros    -----------
*****************************************/
/* Data (Send-Recieve) Register */
#define UDR	                    (*((volatile u8 *)0x2C))
/* Control and Status Register */
#define UCSRA		               (*((volatile u8 *)0x2B))
/* Control and Status Register */
#define UCSRB		               (*((volatile u8 *)0x2A))
/* Baud Rate Registers */
#define UBRRL		               (*((volatile u8 *)0x29))
/* Control and Status Register */
#define UCSRC		               (*((volatile u8 *)0x40))
/* Baud Rate Registers */
#define UBRRH		               (*((volatile u8 *)0x40))
/*-------------  UCSRA Bits  -------------*/
#define UCSRA_RXC		          (7)  /* Flag Receive Complete */
#define UCSRA_TXC		          (6)  /* Flag Transmit Complete */
#define UCSRA_UDRE		          (5)  /* Flag Data Register Empty */
#define UCSRA_FE		          (4)  /* Flag Frame Error */
#define UCSRA_DOR		          (3)  /* Flag Data OverRun */
#define UCSRA_PE		          (2)  /* Flag Parity Error */
#define UCSRA_U2X		          (1)  /* Double Speed*/
#define UCSRA_MPCM		          (0)  /* Multi-processor Communication  */
/*-------------  UCSRB Bits  -------------*/
#define UCSRB_RXCIE		          (7)  /* RX Complete Interrupt Enable */
#define UCSRB_TXCIE		          (6)  /* TX Complete Interrupt Enable */
#define UCSRB_UDRIE		          (5)  /* Data Register Empty Interrupt Enable */
#define UCSRB_RXEN		          (4)  /* Receiver Enable */
#define UCSRB_TXEN		          (3)  /* Transmitter Enable */
#define UCSRB_UCSZ2		          (2)  /* Character Size */
#define UCSRB_RXB8		          (1)  /* Receive Data Bit 8 */
#define UCSRB_TXB8		          (0)  /* Transmit Data Bit 8 */
/*-------------  UCSRC Bits  -------------*/
#define UCSRC_URSEL		          (7)  /* Register Select */
#define UCSRC_UMSEL		          (6)  /* Mode Select */
#define UCSRC_UPM1		          (5)  /* Parity Mode */
#define UCSRC_UPM0		          (4)  /* Parity Mode */
#define UCSRC_USBS		          (3)  /* Stop Bit Select */
#define UCSRC_UCSZ1		          (2)  /* Character Size */
#define UCSRC_UCSZ0		          (1)  /* Character Size*/
#define UCSRC_UCPOL		          (0)  /* Clock Polarity */
/*-------------  UBRRH Bits  -------------*/
#define UBRRH_URSEL		          (7)  /* Register Select (UCSRC-UBRRH) */
/*----------------  Global ---------------*/
#ifndef SREG
#define SREG                       (*((volatile u8*)0x5F))
#define SREG_I                     (7)
#endif
#endif
/********************************************************************
 *  END OF FILE:  USART_Private.h
********************************************************************/