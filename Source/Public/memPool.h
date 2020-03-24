#ifndef		__DATA_BRIDGE__
#define		__DATA_BRIDGE__

#include "stm32f10x.h"

#define     FreeListID      0
#define     USART1_TX_ID    1
#define     USART1_RX_ID    2
#define     USART2_TX_ID    3
#define     USART2_RX_ID    4
#define     USART3_TX_ID    5
#define     USART3_RX_ID    6


#define     POOL_BUFF_SIZE      64


#ifndef			NULL
#define			NULL	((void *)0)
#endif

typedef	struct	DataBridge
{
	unsigned char Buff[POOL_BUFF_SIZE];
	unsigned int isFull;	
	struct	DataBridge *pNext;
}MemPackage_ST;


void	MemPool_Init(void);
u8	    MemPool_ReadBytes(u8 id,u8 *pRbuff,u8 len);
void	MemPool_WriteBytes(u8 id,u8 *pbuff,u8 len);

#endif


